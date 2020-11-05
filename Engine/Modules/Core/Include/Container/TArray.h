/**
 * Created by rayfalling on 2020/10/18.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#ifndef VISREAL_T_ARRAY_H
#define VISREAL_T_ARRAY_H

#include <initializer_list>
#include <memory>
#include <mutex>

#include "Logger/CoreLog.h"
#include "Marco/Constant.h"
#include "Math/VisRealMath.h"
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
			TArray(TArray<T>&& array) noexcept {
				_data.reset();
				_size = array._size;
				_capacity = array._capacity;
				_data.swap(array._data);
			}

			~TArray() = default;

		private:
			/* element count */
			SIZE_T _size;
			/* max element size */
			SIZE_T _capacity = 0;
			/* element array */
			std::shared_ptr<T[]> _data;
			/* thread mutex */
			std::mutex _mutex;
			/* default capacity */
			const static uint32 defaultArraySize;
			#ifdef PLATFORM_64BITS
			/* max array element size */
			const static uint64 maxArraySize = INT64_MAX;
			#else
			/* max array element size */
			const static uint64 maxArraySize = INT32_MAX;
			#endif

		public:
			/* operator[] if index out of bound will return T()*/
			T& operator[](SIZE_T& index) {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
					return *new T();
				}
				return _data.get()[index];
			}

			/* operator[] if index out of bound will return T()*/
			const T& operator[](SIZE_T& index) const {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
					return *new T();
				}
				return _data.get()[index];
			}
		
			/* operator[] if index out of bound will return T()*/
			T& operator[](const SIZE_T& index) {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
					return *new T();
				}
				return _data.get()[index];
			}

			/* operator[] if index out of bound will return T()*/
			const T& operator[](const SIZE_T& index) const {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
					return *new T();
				}
				return _data.get()[index];
			}

			/* operator[] if index out of bound will return T()*/
			T& operator[](SIZE_T&& index) {
				if (index > _size - 1 || _size == 0) {
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
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
			[[nodiscard]] T* GetData() const {
				return _data.get();
			}

		public:
			/* Add new Element */
			SIZE_T Add(T& data) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size++;
				if (_size >= _capacity)
					GrowArrayCapacity();
				_data.get()[_size - 1] = data;
				return _size;
			}

			/* Add new Element */
			SIZE_T Add(T&& data) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size++;
				if (_size >= _capacity)
					GrowArrayCapacity();
				_data.get()[_size - 1] = data;
				return _size;
			}

			/* Add new Elements */
			void AddRange(std::initializer_list<T>& initList) {
				std::unique_lock<std::mutex> lock(_mutex);
				auto oldSize = _size;
				_size += initList.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, initList.begin(), initList.size());

			}

			/* Add new Elements */
			void AddRange(std::initializer_list<T>&& initList) {
				std::unique_lock<std::mutex> lock(_mutex);
				auto oldSize = _size;
				_size += initList.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, initList.begin(), initList.size());
			}


			/* Add new Elements */
			void AddRange(TArray<T>& array) {
				std::unique_lock<std::mutex> lock(_mutex);
				auto oldSize = _size;
				_size += array.GetSize();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, array.GetData(), array.GetSize());
			}

			/* Add new Elements */
			void AddRange(TArray<T>&& array) {
				std::unique_lock<std::mutex> lock(_mutex);
				auto oldSize = _size;
				_size += array.GetSize();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, array.GetData(), array.GetSize());
			}

			/* Add new Elements */
			void AddRange(std::vector<T>& vector) {
				std::unique_lock<std::mutex> lock(_mutex);
				auto oldSize = _size;
				_size += vector.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, vector.data(), vector.size());
			}

			/* Add new Elements */
			void AddRange(std::vector<T>&& vector) {
				std::unique_lock<std::mutex> lock(_mutex);
				auto oldSize = _size;
				_size += vector.size();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get() + oldSize, vector.data(), vector.size());
			}

			/* Set new Elements */
			void Assign(std::initializer_list<T>& initList) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size = initList.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), initList.begin(), initList.size());
			}

			/* Set new Elements */
			void Assign(std::initializer_list<T>&& initList) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size = initList.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), initList.begin(), initList.size());
			}

			/* Set new Elements */
			void Assign(TArray<T>& array) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size = array.GetSize();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), array.GetData(), array.GetSize());
			}

			/* Set new Elements */
			void Assign(TArray<T>&& array) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size = array.GetSize();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), array.GetData(), array.GetSize());
			}

			/* Set new Elements */
			void Assign(std::vector<T>& vector) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size = vector.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), vector.data(), vector.size());
			}

			/* Set new Elements */
			void Assign(std::vector<T>&& vector) {
				std::unique_lock<std::mutex> lock(_mutex);
				_size = vector.size();
				_data.reset();
				if (_size > _capacity)
					GrowArrayCapacity();
				Core::CopyAssignItems<T, SIZE_T>(_data.get(), vector.data(), vector.size());
			}

			/* Clear all Element in Array */
			void Clear() {
				std::unique_lock<std::mutex> lock(_mutex);
				_data.reset();
				_size = 0;
				_capacity = defaultArraySize;
				_data.swap(std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>()));
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
				std::unique_lock<std::mutex> lock(_mutex);
				if (index > _size - 1)
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
				else
					RemoveAtImpl(index, 1);
			}

			/**
			 * Removes an element (or elements) at given location optionally shrinking
			 * the array.
			 *
			 * This version is much more efficient than RemoveAt, but does not preserve the order.
			 * If you don't care the array order, you can use it.
			 * */
			void RemoveAtSwap(const SIZE_T index) {
				CoreLog::GetInstance().LogWarning(TARRAY_REMOVE_AT_SWAP_WARNING);
				std::unique_lock<std::mutex> lock(_mutex);
				if (index > _size - 1)
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
				else
					RemoveAtSwapImpl(index, 1);
			}

			/* Remove first array element */
			void RemoveFirst() {
				std::unique_lock<std::mutex> lock(_mutex);
				RemoveAtImpl(0, 1);
			}

			/* Remove last array element */
			void RemoveLast() {
				std::unique_lock<std::mutex> lock(_mutex);
				RemoveAtImpl(_size - 1, 1);
			}

			/* Remove array elements at index with count */
			void RemoveAtRange(const SIZE_T index, const SIZE_T count = 1) {
				std::unique_lock<std::mutex> lock(_mutex);
				if (count > 0)
					if (index + count > _size - 1)
						CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
					else
						RemoveAtImpl(index, count);
			}

			/* Remove array elements from start to end */
			void RemoveRange(const SIZE_T startIndex, const SIZE_T endIndex) {
				std::unique_lock<std::mutex> lock(_mutex);
				if (endIndex < startIndex || endIndex > _size - 1)
					CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
				else
					RemoveAtImpl(startIndex, endIndex - startIndex + 1);
			}

			/* Reserve array elements */
			void Reserve() {
				SIZE_T start = 0, end = _size - 1;
				while (start < end) {
					std::swap(*(_data.get() + start), *(_data.get() + end));
					start++;
					end--;
				}
			}

			/* resize the array */
			void Resize(const SIZE_T size, const bool allowShrink = true) {
				std::unique_lock<std::mutex> lock(_mutex);
				if (size < _capacity) {
					ResizeShrink(size, allowShrink);
				} else if (size > _capacity) {
					ResizeGrow(size);
				}
			}

			/* Swap two array data */
			void Swap(TArray<T>& array) {
				std::unique_lock<std::mutex> lock(_mutex);
				_data.swap(array._data);
			}

		protected:
			/**
			 * shrink array capacity to match it size
			 *
			 * @param size				the size after shrink
			 * @param allowShrinking	true will match to given size, false will resize to current size
			 * */
			void ResizeShrink(const SIZE_T size, const bool allowShrinking = false) {
				if (allowShrinking) {
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
			void ResizeGrow(const SIZE_T size) {
				_capacity = size;
				if (_capacity > maxArraySize) {
					CoreLog::GetInstance().LogError(TARRAY_MAX_SIZE);
					_capacity = maxArraySize;
				}
				std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
				Core::CopyAssignItems<T, SIZE_T>(newSpace.get(), _data.get(), _size);
				_data.reset();
				_data.swap(newSpace);
			}

			/* auto grow array capacity policy */
			void GrowArrayCapacity() {
				auto newCapacity = _capacity + _capacity / 2;
				if (newCapacity < _size) newCapacity = _size;
				ResizeGrow(newCapacity);
			}

			/* remove implementation */
			void RemoveAtImpl(SIZE_T index, const SIZE_T count, const bool allowShrinking = true) {
				if (count) {
					/* Do destruct for removed element to avoid ptr in element */
					Core::DestructItems<T, SIZE_T>(_data.get() + index, count);
					/* move elements */
					Core::MoveAssignItems<T, SIZE_T>(_data.get() + index, _data.get() + (index + count), count);
					/* shrink array size */
					_size -= count;

					if (allowShrinking) {
						ResizeShrink(_size, allowShrinking);
					}
				}
			}

			/* remove element by swap from array memory bottom implementation */
			void RemoveAtSwapImpl(SIZE_T index, SIZE_T count = 1, const bool allowShrinking = true) {
				if (count) {
					Core::DestructItems(GetData() + index, count);

					// Replace the elements in the hole created by the removal with elements from the end of the array, so the range of indices used by the array is contiguous.
					const auto numElementsInHole = count;
					const auto numElementsAfterHole = _size - (index + count);
					const auto numElementsToMoveIntoHole = Math::FMath::Min(numElementsInHole, numElementsAfterHole);
					if (numElementsToMoveIntoHole) {
						Core::CopyAssignItems(
								_data.get() + index,
								_data.get() + _size - numElementsToMoveIntoHole,
								numElementsToMoveIntoHole
								);
					}
					_size -= count;

					if (allowShrinking) {
						ResizeShrink(_size, allowShrinking);
					}
				}
			}
	};

	template <typename T>
	const uint32 TArray<T>::defaultArraySize = 8;
}

#endif //VISREAL_T_ARRAY_H
