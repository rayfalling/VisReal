/**
 * Created by rayfalling on 2020/10/18.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#ifndef VISREAL_TARRAY_H
#define VISREAL_TARRAY_H

#include <initializer_list>
#include <cstring>
#include <memory>

#include "Marco/Constant.h"
#include "Logger/CoreLog.h"
#include "Memory/MemoryUtils.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Types {
    template<typename T>
    class TArray {
    public:
        TArray() {
            _size = 0;
            _capacity = _defaultArraySize;
            _data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
        }

        explicit TArray(int32 capacity) {
            _size = 0;
            _capacity = static_cast<SIZE_T>(capacity);
            _data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
        }

        explicit TArray(uint32 capacity) {
            _size = 0;
            _capacity = capacity;
            _data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
        }

        TArray(std::initializer_list<T> initList) {
            _size = initList.size();
            _capacity = initList.size();
            _data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
            Engine::Core::CopyAssignItems<T, SIZE_T>(_data.get(), initList.begin(), initList.size());
        };

        /* copy construct */
        TArray &operator=(const TArray &array) {
            _data.reset();
            if (_capacity < array._size) {
                _size = array._size;
                _capacity = array._capacity;
                GrowArrayCapacity();
            }

            return *this;
        }

        ~TArray() = default;

    private:
        /* use count */
        SIZE_T _size;
        /* max item size */
        SIZE_T _capacity = 0;
        /* item array */
        std::shared_ptr<T[]> _data;
        /* thread mutex */
        std::mutex _mutex;
        /* default capacity */
        const static uint32 _defaultArraySize;

    public:
        /* operator[] if index out of bound will return T()*/
        T &operator[](int index) {
            if (index > _size - 1) {
                CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
                return *new T();
            }
            return _data.get()[index];
        }

        /* return size */
        SIZE_T GetSize() {
            return _size;
        }

        /* return size */
        SIZE_T Length() {
            return _size;
        }

        /* return capacity */
        SIZE_T GetCapacity() {
            return _capacity;
        }

        T *GetData() const {
            return _data.get();
        }

        /* Add new Element */
        T &Add(T data) {
            _mutex.lock();
            _size++;
            if (_size >= _capacity)
                GrowArrayCapacity();
            _data.get()[_size - 1] = data;
            _mutex.unlock();
            return _data.get()[_size - 1];
        }

        /* Add new Element */
        T &Add(T &data) {
            _mutex.lock();
            _size++;
            if (_size >= _capacity)
                GrowArrayCapacity();
            _data.get()[_size - 1] = data;
            _mutex.unlock();
            return _data.get()[_size - 1];
        }

        /* Add new Elements */
        void AddRange(std::initializer_list<T> initList) {
            auto old_size = _size;
            _size += initList.size();
            if (_size > _capacity)
                GrowArrayCapacity();
            Engine::Core::CopyAssignItems<T, SIZE_T>(_data.get() + old_size, initList.begin(), initList.size());
        }

        /* Add new Elements */
        void AddRange(TArray<T> array) {
            auto old_size = _size;
            _size += array.GetSize();
            if (_size > _capacity)
                GrowArrayCapacity();
            Engine::Core::CopyAssignItems<T, SIZE_T>(_data.get() + old_size, array.GetData(), array.GetSize());
        }

        /* Add new Elements */
        void AddRange(std::vector<T> vector) {
            auto old_size = _size;
            _size += vector.size();
            if (_size > _capacity)
                GrowArrayCapacity();
            Engine::Core::CopyAssignItems<T, SIZE_T>(_data.get() + old_size, vector.data(), vector.size());
        }

        /* Remove array element at index */
        void RemoveAt(SIZE_T index) {
            if (index > _size - 1)
                CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
            else
                RemoveAtImpl(index, 1);
        }

        /* Remove first array element */
        void RemoveFirst() {
            RemoveAtImpl(0, 1);
        }

        /* Remove last array element */
        void RemoveLast() {
            RemoveAtImpl(_size - 1, 1);
        }

        /* Remove array elements at index */
        void RemoveRange(SIZE_T index, SIZE_T count) {
            if (count > 0 && index > 0)
                if (index + count > _size - 1)
                    CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
                else
                    RemoveAtImpl(index, count);
        }

        /* Clear all Element in Array */
        void Clear() {
            _mutex.lock();
            _data.reset();
            _mutex.unlock();
        }

        void Resize(SIZE_T size, bool allowShrink = true) {
            if (size < _capacity) {
                ResizeShrink(size, allowShrink);
            } else if (size == _capacity) {
                return;
            } else {
                ResizeGrow(size);
            }
        }

    protected:
        /* shrink array capacity to match it size */
        void ResizeShrink(SIZE_T size, bool allowShrink = false) {
            _capacity = size;
            std::shared_ptr<T[]> new_space = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
            Engine::Core::CopyAssignItems<T, SIZE_T>(new_space.get(), _data.get(), size);
            _size = size;
            _data.reset();
            _data.swap(new_space);
        }

        /* grow array capacity to given size */
        void ResizeGrow(SIZE_T size) {
            _capacity = size;
            std::shared_ptr<T[]> new_space = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
            Engine::Core::CopyAssignItems<T, SIZE_T>(new_space.get(), _data.get(), _size);
            _data.reset();
            _data.swap(new_space);
        }

        /* auto grow array capacity policy */
        void GrowArrayCapacity() {
            SIZE_T new_capacity = _capacity + _capacity / 2;
            if (new_capacity < _size) new_capacity = _size;
            ResizeGrow(new_capacity);
        }

        /* remove implementation */
        void RemoveAtImpl(SIZE_T index, SIZE_T count, bool allowShrink = true) {
            if (count > 0) {
                /* Do destruct for removed element to avoid ptr in element */
                Engine::Core::DestructItems<T, SIZE_T>(_data.get() + index, count);
                /* move elements */
                Engine::Core::MoveAssignItems<T, SIZE_T>(_data.get() + index, _data.get() + (index + count), count);
                /* shrink array size */
                ResizeShrink(_size - count, allowShrink);
            }
        }
    };
}

#endif //VISREAL_TARRAY_H
