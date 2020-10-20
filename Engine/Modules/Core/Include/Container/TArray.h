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
            std::memcpy(_data.get(), initList.begin(), sizeof(T) * _size);
        };

        /* copy construct */
        TArray &operator=(const TArray &array) {
            _data.reset();
            if (_capacity < array._size) {
                _size = array._size;
                _capacity = array._capacity;
                Grow();
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
                Grow();
            _data.get()[_size - 1] = data;
            _mutex.unlock();
            return _data.get()[_size - 1];
        }

        /* Add new Element */
        T &Add(T &data) {
            _mutex.lock();
            _size++;
            if (_size >= _capacity)
                Grow();
            _data.get()[_size - 1] = data;
            _mutex.unlock();
            return _data.get()[_size - 1];
        }

        /* Add new Elements */
        void AddRange(std::initializer_list<T> initList) {
            auto old_size = _size;
            _size += initList.size();
            if (_size > _capacity)
                Grow();
            std::memcpy(_data.get() + sizeof(T) * old_size, initList.begin(), sizeof(T) * initList.size());
        }

        /* Add new Elements */
        void AddRange(TArray<T> array) {
            auto old_size = _size;
            _size += array.GetSize();
            if (_size > _capacity)
                Grow();
            std::memcpy(_data.get() + sizeof(T) * old_size, array.GetData(), sizeof(T) * array.GetSize());
        }

        /* Add new Elements */
        void AddRange(std::vector<T> vector) {
            auto old_size = _size;
            _size += vector.size();
            if (_size > _capacity)
                Grow();
            std::memcpy(_data.get() + sizeof(T) * old_size, vector.data(), sizeof(T) * vector.size());
        }

        void RemoveFirst() {
            RemoveAtImpl(0, 1);
            _size--;
        }

        void RemoveLast() {
            RemoveAtImpl(_size - 1, 1);
            _size--;
        }

        /* Clear all Element in Array */
        void Clear() {
            _mutex.lock();
            _data.reset();
            _mutex.unlock();
        }

        void Resize(SIZE_T size, bool allowShrink = false) {
            if (size < _capacity) {
                ResizeShrink(size, allowShrink);
            } else if (size == _capacity) {
                return;
            } else {
                ResizeGrow(size);
            }
        }

    protected:
        void ResizeShrink(SIZE_T size, bool allowShrink = false) {
            _capacity = size;
            std::shared_ptr<T[]> new_space = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
            std::memcpy(new_space.get(), _data.get(), sizeof(T) * size);
            _size = size;
            _data.reset();
            _data.swap(new_space);
        }

        void ResizeGrow(SIZE_T size) {
            _capacity = size;
            std::shared_ptr<T[]> new_space = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
            std::memcpy(new_space.get(), _data.get(), sizeof(T) * _size);
            _data.reset();
            _data.swap(new_space);
        }

        void Grow() {
            SIZE_T new_capacity = _capacity + _capacity / 2;
            if (new_capacity < _size) new_capacity = _size;
            std::shared_ptr<T[]> new_space = std::shared_ptr<T[]>(new T[new_capacity](), std::default_delete<T[]>());
            std::memcpy(new_space.get(), _data.get(), sizeof(T) * _capacity);
            _data.reset();
            _data.swap(new_space);
        }

        void RemoveAtImpl(SIZE_T index, SIZE_T count, bool allowShrink = true) {
            if (count > 0) {
                /* Do destruct for removed element*/
                Engine::Core::DestructItems<T, SIZE_T>(_data.get(), count);
            }
        }
    };
}

#endif //VISREAL_TARRAY_H
