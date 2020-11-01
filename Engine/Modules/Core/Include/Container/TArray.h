/**
 * Created by rayfalling on 2020/10/18.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#ifndef VISREAL_T_ARRAY_H
#define VISREAL_T_ARRAY_H

#include <initializer_list>
#include <cstring>
#include <memory>
#include <mutex>

#include "Marco/Constant.h"
#include "Logger/CoreLog.h"
#include "Memory/MemoryUtils.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Types {
	template <typename T>
	class TArray {
		template <typename Other>
		friend class TArray;

		public:
			TArray() {
				_size = 0;
				_capacity = defaultArraySize;
				_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
			}

			explicit TArray(const SIZE_T capacity) {
				_size = 0;
				_capacity = capacity;
				_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
			}

			TArray(std::initializer_list<T> initList) {
				_size = initList.size();
				_capacity = initList.size();
				_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), initList.begin(), initList.size());
			}

			/* copy assignment operator */
			TArray<T>& operator=(const TArray<T>& array) {
				if (this != &array) {
					_data.reset();
					_size = array._size;
					_capacity = array._capacity;
					_data = array._data;
				}
				return *this;
			}

			/* move assignment operator */
			TArray<T>& operator=(TArray<T>&& array) noexcept {
				if (this != &array) {
					_data.reset();
					_size = array._size;
					_capacity = array._capacity;
					_data.swap(array._data);
				}
				return *this;
			}

			/* Copy Construct, copy deep data to new Instance */
			TArray(const TArray<T>& array) {
				_size = array._size;
				_capacity = array._capacity;
				_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), array.GetData(), array._capacity);
			}

			/* Move Construct, copy deep data to new Instance */
			TArray(const TArray<T>&& array) noexcept {
				_data.reset();
				_size = array._size;
				_capacity = array._capacity;
				_data.swap(array._data);
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
			const static uint32 defaultArraySize;

		public:
			/* operator[] if index out of bound will return T()*/
			T& operator[](int index) {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
					return *new T();
				}
				return _data.get()[index];
			}

			/* operator[] if index out of bound will return T()*/
			T& operator[](int& index) {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
					return *new T();
				}
				return _data.get()[index];
			}

			/* return size */
			[[nodiscard]] SIZE_T GetSize() const {
				return _size;
			}

			/* return size */
			[[nodiscard]] SIZE_T Length() const {
				return _size;
			}

			/* return capacity */
			[[nodiscard]] SIZE_T GetCapacity() const {
				return _capacity;
			}

		protected:
			T* GetData() const {
				return _data.get();
			}

		public:
			/* Add new Element */
			T& Add(T& data) {
				_mutex.lock();
				_size++;
				if (_size >= _capacity)
					GrowArrayCapacity();
				_data.get()[_size - 1] = data;
				_mutex.unlock();
				return _data.get()[_size - 1];
			}

			/* Add new Element */
			T& Add(T&& data) {
				_mutex.lock();
				_size++;
				if (_size >= _capacity)
					GrowArrayCapacity();
				_data.get()[_size - 1] = data;
				_mutex.unlock();
				return _data.get()[_size - 1];
			}

			/* Add new Elements */
			void AddRange(std::initializer_list<T>& initList) {
				_mutex.lock();
				auto oldSize = _size;
				_size += initList.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, initList.begin(), initList.size());
				_mutex.unlock();
			}

			/* Add new Elements */
			void AddRange(std::initializer_list<T>&& initList) {
				_mutex.lock();
				auto oldSize = _size;
				_size += initList.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, initList.begin(), initList.size());
				_mutex.unlock();
			}
		

			/* Add new Elements */
			void AddRange(TArray<T>& array) {
				_mutex.lock();
				auto oldSize = _size;
				_size += array.GetSize();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, array.GetData(), array.GetSize());
				_mutex.unlock();
			}

			/* Add new Elements */
			void AddRange(TArray<T>&& array) {
				_mutex.lock();
				auto oldSize = _size;
				_size += array.GetSize();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, array.GetData(), array.GetSize());
				_mutex.unlock();
			}

			/* Add new Elements */
			void AddRange(std::vector<T>& vector) {
				_mutex.lock();
				auto oldSize = _size;
				_size += vector.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, vector.data(), vector.size());
				_mutex.unlock();
			}

			/* Add new Elements */
			void AddRange(std::vector<T>&& vector) {
				_mutex.lock();
				auto oldSize = _size;
				_size += vector.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, vector.data(), vector.size());
				_mutex.unlock();
			}

			/* Set new Elements */
			void Assign(std::initializer_list<T>& initList) {
				_mutex.lock();
				_size = initList.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), initList.begin(), initList.size());
				_mutex.unlock();
			}

			/* Set new Elements */
			void Assign(std::initializer_list<T>&& initList) {
				_mutex.lock();
				_size = initList.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), initList.begin(), initList.size());
				_mutex.unlock();
			}

			/* Set new Elements */
			void Assign(TArray<T>& array) {
				_mutex.lock();
				_size = array.GetSize();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), array.GetData(), array.GetSize());
				_mutex.unlock();
			}

			/* Set new Elements */
			void Assign(TArray<T>&& array) {
				_mutex.lock();
				_size = array.GetSize();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), array.GetData(), array.GetSize());
				_mutex.unlock();
			}

			/* Set new Elements */
			void Assign(std::vector<T>& vector) {
				_mutex.lock();
				_size = vector.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), vector.data(), vector.size());
				_mutex.unlock();
			}

			/* Set new Elements */
			void Assign(std::vector<T>&& vector) {
				_mutex.lock();
				_size = vector.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), vector.data(), vector.size());
				_mutex.unlock();
			}

			/* Clear all Element in Array */
			void Clear() {
				_mutex.lock();
				_data.reset();
				_mutex.unlock();
			}

			/**
			 * Checks if this array contains the element.
			 *
			 * @returns	True if found. False otherwise.
			 */
			template <typename ComparisonType>
			bool Contains(const ComparisonType& item) {
				for (T *data = GetData(), *dataEnd = data + _size; data != dataEnd; ++data) {
					if (*data == item) {
						return true;
					}
				}
				return false;
			}

			/**
			 * Checks if this array contains the element.
			 *
			 * @returns	True if found. False otherwise.
			 */
			template <typename ComparisonType>
			bool Contains(const ComparisonType& item) const {
				for (T *data = GetData(), *dataEnd = data + _size; data != dataEnd; ++data) {
					if (*data == item) {
						return true;
					}
				}
				return false;
			}

			/**
			 * Checks if this array contains element for which the predicate is true.
			 *
			 * @param predicate to use
			 * @returns	True if found. False otherwise.
			 */
			template <typename Predicate>
			bool ContainsByPredicate(Predicate predicate) {
				return Find(predicate) != nullptr;
			}

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			T* Find(Predicate predicate) {
				for (T *data = GetData(), *dataEnd = data + _size; data != dataEnd; ++data) {
					if (predicate(*data)) {
						return data;
					}
				}
				return nullptr;
			}

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			const T* Find(Predicate predicate) const {
				return const_cast<TArray*>(this)->Find(predicate);
			}

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			T* FindLast(Predicate predicate) {
				for (T *start = GetData(), *data = start + _size; data != start;) {
					--data;
					if (predicate(*data)) {
						return data;
					}
				}
				return nullptr;
			}

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			const T* FindLast(Predicate predicate) const {
				return const_cast<TArray*>(this)->FindLast(predicate);
			}

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			int32 IndexOf(T& element) {
				const T* start = GetData();
				for (const T *data = start, *dataEnd = start + _size; data != dataEnd; ++data) {
					if (*data == element) {
						return static_cast<int32>(data - start);
					}
				}
				return INDEX_NONE;
			}

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			int32 IndexOf(T&& element) {
				const T* start = GetData();
				for (const T *data = start, *dataEnd = start + _size; data != dataEnd; ++data) {
					if (*data == element) {
						return static_cast<int32>(data - start);
					}
				}
				return INDEX_NONE;
			}

			/**
				 * get the index of given element
				 *
				 * @return index in the array or -1 not found
				 * */
			int32 IndexOf(T& element) const {
				return const_cast<TArray*>(this)->IndexOf(element);
			}

			/**
				 * get the index of given element
				 *
				 * @return index in the array or -1 not found
				 * */
			int32 IndexOf(T&& element) const {
				return const_cast<TArray*>(this)->IndexOf(element);
			}

			/* Finds an element which matches a predicate functor. */
			int32 IndexLast(T& element) {
				for (T *start = GetData(), *data = start + _size; data != start;) {
					--data;
					if (*data == element) {
						return static_cast<int32>(data - start);
					}
				}
				return INDEX_NONE;
			}

			/* Finds an element which matches a predicate functor. */
			int32 IndexLast(T&& element) {
				for (T *start = GetData(), *data = start + _size; data != start;) {
					--data;
					if (*data == element) {
						return static_cast<int32>(data - start);
					}
				}
				return INDEX_NONE;
			}

			/* Finds an element which matches a predicate functor. */
			int32 IndexLast(T& element) const {
				return const_cast<TArray*>(this)->IndexLast(element);
			}

			/* Finds an element which matches a predicate functor. */
			int32 IndexLast(T&& element) const {
				return const_cast<TArray*>(this)->IndexLast(element);
			}

			/* Remove array element at index */
			void RemoveAt(const SIZE_T index) {
				_mutex.lock();
				if (index > _size - 1)
					CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
				else
					RemoveAtImpl(index, 1);
				_mutex.unlock();
			}

			/* Remove first array element */
			void RemoveFirst() {
				_mutex.lock();
				RemoveAtImpl(0, 1);
				_mutex.unlock();
			}

			/* Remove last array element */
			void RemoveLast() {
				_mutex.lock();
				RemoveAtImpl(_size - 1, 1);
				_mutex.unlock();
			}

			/* Remove array elements at index with count */
			void RemoveAtRange(const SIZE_T index, const SIZE_T count) {
				_mutex.lock();
				if (count > 0 && index >= 0)
					if (index + count > _size - 1)
						CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
					else
						RemoveAtImpl(index, count);
				_mutex.unlock();
			}

			/* Remove array elements from start to end */
			void RemoveRange(const SIZE_T startIndex, const SIZE_T endIndex) {
				_mutex.lock();
				if (endIndex > 0 && startIndex >= 0)
					if (endIndex > _size - 1)
						CoreLog::GetInstance().LogError(OUT_OF_ARRAY_INDEX);
					else
						RemoveAtImpl(startIndex, endIndex - startIndex + 1);
				_mutex.unlock();
			}

			/* resize the array */
			void Resize(const SIZE_T size, const bool allowShrink = true) {
				_mutex.lock();
				if (size < _capacity) {
					ResizeShrink(size, allowShrink);
				} else if (size == _capacity) {
					return;
				} else {
					ResizeGrow(size);
				}
				_mutex.unlock();
			}

			/* Swap two array data */
			void Swap(TArray<T>& array) {
				_mutex.lock();
				_data.swap(array._data);
				_mutex.unlock();
			}

		protected:
			/**
			 * shrink array capacity to match it size
			 *
			 * @param size
			 * @param allowShrink true will match to given size, false will resize to current size
			 * */
			void ResizeShrink(SIZE_T size, bool allowShrink = false) {
				if (allowShrink) {
					_capacity = size;
					std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(
							new T[_capacity](), std::default_delete<T[]>());
					Core::CopyAssignItems<T, SIZE_T>(newSpace.get(), _data.get(), size);
					_size = size;
					_data.reset();
					_data.swap(newSpace);
				} else {
					_capacity = _size;
					std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(
							new T[_capacity](), std::default_delete<T[]>());
					Core::CopyAssignItems<T, SIZE_T>(newSpace.get(), _data.get(), _size);
					_data.reset();
					_data.swap(newSpace);
				}
			}

			/* grow array capacity to given size */
			void ResizeGrow(SIZE_T size) {
				_capacity = size;
				std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
				Core::CopyAssignItems<T, SIZE_T>(newSpace.get(), _data.get(), _size);
				_data.reset();
				_data.swap(newSpace);
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
					Core::DestructItems<T, SIZE_T>(_data.get() + index, count);
					/* move elements */
					Core::MoveAssignItems<T, SIZE_T>(_data.get() + index, _data.get() + (index + count), count);
					/* shrink array size */
					ResizeShrink(_size - count, allowShrink);
				}
			}
	};
}

#endif //VISREAL_T_ARRAY_H
