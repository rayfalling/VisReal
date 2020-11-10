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

		/* define index type */
		#ifdef PLATFORM_64BITS
		typedef uint64 IndexType;
		typedef int64 ReturnIndexType;
		#else
		typedef uint32 IndexType;
		typedef int32 ReturnIndexType;
		#endif


		public:
			TArray();

			explicit TArray(IndexType capacity);

			TArray(std::initializer_list<T> initList);

			/* copy assignment operator */
			TArray<T>& operator=(const TArray<T>& array);

			/* move assignment operator */
			TArray<T>& operator=(TArray<T>&& array) noexcept;

			/* Copy Construct, copy deep data to new Instance */
			TArray(const TArray<T>& array);

			/* Move Construct, copy deep data to new Instance */
			TArray(TArray<T>&& array) noexcept;

			~TArray();

		private:
			/* element count */
			IndexType _size;
			/* max element size */
			IndexType _capacity = 0;
			/* element array */
			std::shared_ptr<T[]> _data;
			/* thread mutex */
			std::mutex _mutex;
			/* default capacity */
			const static IndexType DefaultArraySize;
			/* max array element size */
			const static IndexType MaxArraySize = INTPTR_MAX;

		public:
			/* return element index */
			T& operator[](IndexType& index) const;

			/* return element index */
			T& operator[](const IndexType& index) const;

			/* return element index */
			T& operator[](IndexType&& index) const;

			/* return size */
			[[nodiscard]] ReturnIndexType GetSize() const;

			/* return size */
			[[nodiscard]] ReturnIndexType Length() const;

			/* return capacity */
			[[nodiscard]] ReturnIndexType GetCapacity() const;

		protected:
			[[nodiscard]] T* GetData() const;

		public:
			/* Add new Element */
			IndexType Add(T& data);

			/* Add new Element */
			IndexType Add(T&& data);

			/* Add new Elements */
			void AddRange(std::initializer_list<T>& initList);

			/* Add new Elements */
			void AddRange(std::initializer_list<T>&& initList);

			/* Add new Elements */
			void AddRange(TArray<T>& array);

			/* Add new Elements */
			void AddRange(TArray<T>&& array);

			/* Add new Elements */
			void AddRange(std::vector<T>& vector);

			/* Add new Elements */
			void AddRange(std::vector<T>&& vector);

			/* Set new Elements */
			void Assign(std::initializer_list<T>& initList);

			/* Set new Elements */
			void Assign(std::initializer_list<T>&& initList);

			/* Set new Elements */
			void Assign(TArray<T>& array);

			/* Set new Elements */
			void Assign(TArray<T>&& array);

			/* Set new Elements */
			void Assign(std::vector<T>& vector);

			/* Set new Elements */
			void Assign(std::vector<T>&& vector);

			/* Clear all Element in Array */
			void Clear();

			/**
			 * Checks if this array contains the element.
			 *
			 * @returns	True if found. False otherwise.
			 */
			template <typename ComparisonType>
			bool Contains(const ComparisonType& item);

			/**
			 * Checks if this array contains the element.
			 *
			 * @returns	True if found. False otherwise.
			 */
			template <typename ComparisonType>
			bool Contains(const ComparisonType& item) const;

			/**
			 * Checks if this array contains element for which the predicate is true.
			 *
			 * @param predicate to use
			 * @returns	True if found. False otherwise.
			 */
			template <typename Predicate>
			bool ContainsByPredicate(Predicate predicate);

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			T* Find(Predicate predicate);

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			const T* Find(Predicate predicate) const;

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
			IndexType IndexOf(T& element);

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			IndexType IndexOf(T&& element);

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			IndexType IndexOf(T& element) const;

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			IndexType IndexOf(T&& element) const;

			/* Finds an element which matches a predicate functor. */
			int32 IndexLast(T& element);

			/* Finds an element which matches a predicate functor. */
			IndexType IndexLast(T&& element);

			/* Finds an element which matches a predicate functor. */
			IndexType IndexLast(T& element) const;

			/* Finds an element which matches a predicate functor. */
			IndexType IndexLast(T&& element) const;

			/* Remove array element at index */
			void RemoveAt(IndexType index);

			/**
			 * Removes an element (or elements) at given location optionally shrinking
			 * the array.
			 *
			 * This version is much more efficient than RemoveAt, but does not preserve the order.
			 * If you don't care the array order, you can use it.
			 * */
			void RemoveAtSwap(IndexType index);

			/* Remove first array element */
			void RemoveFirst();

			/* Remove last array element */
			void RemoveLast();

			/* Remove array elements at index with count */
			void RemoveAtRange(IndexType index, IndexType count = 1);

			/* Remove array elements from start to end */
			void RemoveRange(IndexType startIndex, IndexType endIndex);

			/* Reserve array elements */
			void Reserve();

			/* resize the array */
			void Resize(IndexType size, bool allowShrink = true);

			/* Swap two array data */
			void Swap(TArray<T>& array);

		protected:
			/**
			 * shrink array capacity to match it size
			 *
			 * @param size				the size after shrink
			 * @param allowShrinking	true will match to given size, false will resize to current size
			 * */
			void ResizeShrink(IndexType size, bool allowShrinking = false);

			/* grow array capacity to given size */
			void ResizeGrow(IndexType size);

			/* auto grow array capacity policy */
			void GrowArrayCapacity();

			/* remove implementation */
			void RemoveAtImpl(IndexType index, IndexType count, bool allowShrinking = true);

			/* remove element by swap from array memory bottom implementation */
			void RemoveAtSwapImpl(IndexType index, IndexType count = 1, bool allowShrinking = true);

			/* check if the index is out of array size */
			void CheckIndex(IndexType index) const;
	};

	template <typename T>
	TArray<T>::TArray() {
		_size = 0;
		_capacity = DefaultArraySize;
		_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
	}

	template <typename T>
	TArray<T>::TArray(const IndexType capacity) {
		_size = 0;
		_capacity = capacity;
		_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
	}

	template <typename T>
	TArray<T>::TArray(std::initializer_list<T> initList) {
		_size = initList.size();
		_capacity = initList.size();
		_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
		Core::CopyAssignItems<T, IndexType>(_data.get(), initList.begin(), initList.size());
	}

	template <typename T>
	TArray<T>& TArray<T>::operator=(const TArray<T>& array) {
		if (this != &array) {
			_data.reset();
			_size = array._size;
			_capacity = array._capacity;
			_data = array._data;
		}
		return *this;
	}

	template <typename T>
	TArray<T>& TArray<T>::operator=(TArray<T>&& array) noexcept {
		if (this != &array) {
			_data.reset();
			_size = array._size;
			_capacity = array._capacity;
			_data.swap(array._data);
		}
		return *this;
	}

	template <typename T>
	TArray<T>::TArray(const TArray<T>& array) {
		_size = array._size;
		_capacity = array._capacity;
		_data = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
		Core::CopyAssignItems<T, IndexType>(_data.get(), array.GetData(), array._capacity);
	}

	template <typename T>
	TArray<T>::TArray(TArray<T>&& array) noexcept {
		_data.reset();
		_size = array._size;
		_capacity = array._capacity;
		_data.swap(array._data);
	}

	template <typename T>
	TArray<T>::~TArray() = default;

	template <typename T>
	T& TArray<T>::operator[](IndexType& index) const {
		CheckIndex(index);
		return _data[index];
	}

	template <typename T>
	T& TArray<T>::operator[](const IndexType& index) const {
		CheckIndex(index);
		return _data[index];
	}

	template <typename T>
	T& TArray<T>::operator[](IndexType&& index) const {
		CheckIndex(index);
		return _data[index];
	}

	template <typename T>
	typename TArray<T>::ReturnIndexType TArray<T>::GetSize() const {
		return _size;
	}

	template <typename T>
	typename TArray<T>::ReturnIndexType TArray<T>::Length() const {
		return _size;
	}

	template <typename T>
	typename TArray<T>::ReturnIndexType TArray<T>::GetCapacity() const {
		return _capacity;
	}

	template <typename T>
	T* TArray<T>::GetData() const {
		return _data.get();
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::Add(T& data) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size++;
		if (_size >= _capacity)
			GrowArrayCapacity();
		_data.get()[_size - 1] = data;
		return _size;
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::Add(T&& data) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size++;
		if (_size >= _capacity)
			GrowArrayCapacity();
		_data.get()[_size - 1] = std::move(data);
		return _size;
	}

	template <typename T>
	void TArray<T>::AddRange(std::initializer_list<T>& initList) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto oldSize = _size;
		_size += initList.size();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::CopyAssignItems<T, IndexType>(_data.get() + oldSize, initList.begin(), initList.size());

	}

	template <typename T>
	void TArray<T>::AddRange(std::initializer_list<T>&& initList) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto oldSize = _size;
		_size += initList.size();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::MoveAssignItems<T, IndexType>(_data.get() + oldSize, initList.begin(), initList.size());
	}

	template <typename T>
	void TArray<T>::AddRange(TArray<T>& array) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto oldSize = _size;
		_size += array.GetSize();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::CopyAssignItems<T, IndexType>(_data.get() + oldSize, array.GetData(), array.GetSize());
	}

	template <typename T>
	void TArray<T>::AddRange(TArray<T>&& array) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto oldSize = _size;
		_size += array.GetSize();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::MoveAssignItems<T, IndexType>(_data.get() + oldSize, array.GetData(), array.GetSize());
	}

	template <typename T>
	void TArray<T>::AddRange(std::vector<T>& vector) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto oldSize = _size;
		_size += vector.size();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::CopyAssignItems<T, IndexType>(_data.get() + oldSize, vector.data(), vector.size());
	}

	template <typename T>
	void TArray<T>::AddRange(std::vector<T>&& vector) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto oldSize = _size;
		_size += vector.size();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::MoveAssignItems<T, IndexType>(_data.get() + oldSize, vector.data(), vector.size());
	}

	template <typename T>
	void TArray<T>::Assign(std::initializer_list<T>& initList) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size = initList.size();
		_data.reset();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::CopyAssignItems<T, IndexType>(_data.get(), initList.begin(), initList.size());
	}

	template <typename T>
	void TArray<T>::Assign(std::initializer_list<T>&& initList) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size = initList.size();
		_data.reset();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::MoveAssignItems<T, IndexType>(_data.get(), initList.begin(), initList.size());
	}

	template <typename T>
	void TArray<T>::Assign(TArray<T>& array) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size = array.GetSize();
		_data.reset();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::CopyAssignItems<T, IndexType>(_data.get(), array.GetData(), array.GetSize());
	}

	template <typename T>
	void TArray<T>::Assign(TArray<T>&& array) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size = array.GetSize();
		_data.reset();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::MoveAssignItems(_data.get(), array.GetData(), array.GetSize());
	}

	template <typename T>
	void TArray<T>::Assign(std::vector<T>& vector) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size = vector.size();
		_data.reset();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::CopyAssignItems<T, IndexType>(_data.get(), vector.data(), vector.size());
	}

	template <typename T>
	void TArray<T>::Assign(std::vector<T>&& vector) {
		std::lock_guard<std::mutex> lock(_mutex);
		_size = vector.size();
		_data.reset();
		if (_size > _capacity)
			GrowArrayCapacity();
		Core::MoveAssignItems<T, IndexType>(_data.get(), vector.data(), vector.size());
	}

	template <typename T>
	void TArray<T>::Clear() {
		std::lock_guard<std::mutex> lock(_mutex);
		_data.reset();
		_size = 0;
		_capacity = DefaultArraySize;
		_data.swap(std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>()));
	}

	template <typename T>
	template <typename ComparisonType>
	bool TArray<T>::Contains(const ComparisonType& item) {
		for (T *data = GetData(), *dataEnd = data + _size; data != dataEnd; ++data) {
			if (*data == item) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	template <typename ComparisonType>
	bool TArray<T>::Contains(const ComparisonType& item) const {
		for (T *data = GetData(), *dataEnd = data + _size; data != dataEnd; ++data) {
			if (*data == item) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	template <typename Predicate>
	bool TArray<T>::ContainsByPredicate(Predicate predicate) {
		return Find(predicate) != nullptr;
	}

	template <typename T>
	template <typename Predicate>
	T* TArray<T>::Find(Predicate predicate) {
		for (T *data = GetData(), *dataEnd = data + _size; data != dataEnd; ++data) {
			if (predicate(*data)) {
				return data;
			}
		}
		return nullptr;
	}

	template <typename T>
	template <typename Predicate>
	const T* TArray<T>::Find(Predicate predicate) const {
		return const_cast<TArray*>(this)->Find(predicate);
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexOf(T& element) {
		const T* start = GetData();
		for (const T *data = start, *dataEnd = start + _size; data != dataEnd; ++data) {
			if (*data == element) {
				return static_cast<int32>(data - start);
			}
		}
		return INDEX_NONE;
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexOf(T&& element) {
		const T* start = GetData();
		for (const T *data = start, *dataEnd = start + _size; data != dataEnd; ++data) {
			if (*data == element) {
				return static_cast<int32>(data - start);
			}
		}
		return INDEX_NONE;
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexOf(T& element) const {
		return const_cast<TArray*>(this)->IndexOf(element);
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexOf(T&& element) const {
		return const_cast<TArray*>(this)->IndexOf(element);
	}

	template <typename T>
	int32 TArray<T>::IndexLast(T& element) {
		for (T *start = GetData(), *data = start + _size; data != start;) {
			--data;
			if (*data == element) {
				return static_cast<int32>(data - start);
			}
		}
		return INDEX_NONE;
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexLast(T&& element) {
		for (T *start = GetData(), *data = start + _size; data != start;) {
			--data;
			if (*data == element) {
				return static_cast<int32>(data - start);
			}
		}
		return INDEX_NONE;
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexLast(T& element) const {
		return const_cast<TArray*>(this)->IndexLast(element);
	}

	template <typename T>
	typename TArray<T>::IndexType TArray<T>::IndexLast(T&& element) const {
		return const_cast<TArray*>(this)->IndexLast(element);
	}

	template <typename T>
	void TArray<T>::RemoveAt(const IndexType index) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (index > _size - 1)
			CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
		else
			RemoveAtImpl(index, 1);
	}

	template <typename T>
	void TArray<T>::RemoveAtSwap(const IndexType index) {
		CoreLog::GetInstance().LogWarning(TARRAY_REMOVE_AT_SWAP_WARNING);
		std::lock_guard<std::mutex> lock(_mutex);
		if (index > _size - 1)
			CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
		else
			RemoveAtSwapImpl(index, 1);
	}

	template <typename T>
	void TArray<T>::RemoveFirst() {
		std::lock_guard<std::mutex> lock(_mutex);
		RemoveAtImpl(0, 1);
	}

	template <typename T>
	void TArray<T>::RemoveLast() {
		std::lock_guard<std::mutex> lock(_mutex);
		RemoveAtImpl(_size - 1, 1);
	}

	template <typename T>
	void TArray<T>::RemoveAtRange(const IndexType index, const IndexType count) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (count > 0)
			if (index + count > _size - 1)
				CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
			else
				RemoveAtImpl(index, count);
	}

	template <typename T>
	void TArray<T>::RemoveRange(const IndexType startIndex, const IndexType endIndex) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (endIndex < startIndex || endIndex > _size - 1)
			CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
		else
			RemoveAtImpl(startIndex, endIndex - startIndex + 1);
	}

	template <typename T>
	void TArray<T>::Reserve() {
		IndexType start = 0, end = _size - 1;
		while (start < end) {
			std::swap(*(_data.get() + start), *(_data.get() + end));
			start++;
			end--;
		}
	}

	template <typename T>
	void TArray<T>::Resize(const IndexType size, const bool allowShrink) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (size < _capacity) {
			ResizeShrink(size, allowShrink);
		} else if (size > _capacity) {
			ResizeGrow(size);
		}
	}

	template <typename T>
	void TArray<T>::Swap(TArray<T>& array) {
		std::lock_guard<std::mutex> lock(_mutex);
		_data.swap(array._data);
	}

	template <typename T>
	void TArray<T>::ResizeShrink(const IndexType size, const bool allowShrinking) {
		if (allowShrinking) {
			_capacity = size;
			std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(
					new T[_capacity](), std::default_delete<T[]>());
			Core::CopyAssignItems<T, IndexType>(newSpace.get(), _data.get(), size);
			_size = size;
			_data.reset();
			_data.swap(newSpace);
		} else {
			_capacity = _size;
			std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(
					new T[_capacity](), std::default_delete<T[]>());
			Core::CopyAssignItems<T, IndexType>(newSpace.get(), _data.get(), _size);
			_data.reset();
			_data.swap(newSpace);
		}
	}

	template <typename T>
	void TArray<T>::ResizeGrow(const IndexType size) {
		_capacity = size;
		if (_capacity > MaxArraySize) {
			CoreLog::GetInstance().LogWarning(TARRAY_MAX_SIZE);
			_capacity = MaxArraySize;
		}
		std::shared_ptr<T[]> newSpace = std::shared_ptr<T[]>(new T[_capacity](), std::default_delete<T[]>());
		Core::CopyAssignItems<T, IndexType>(newSpace.get(), _data.get(), _size);
		_data.reset();
		_data.swap(newSpace);
	}

	template <typename T>
	void TArray<T>::GrowArrayCapacity() {
		auto newCapacity = _capacity + _capacity / 2;
		if (newCapacity < _size) newCapacity = _size;
		ResizeGrow(newCapacity);
	}

	template <typename T>
	void TArray<T>::RemoveAtImpl(IndexType index, const IndexType count, const bool allowShrinking) {
		if (count) {
			/* Do destruct for removed element to avoid ptr in element */
			Core::DestructItems<T, IndexType>(_data.get() + index, count);
			/* move elements */
			Core::MoveAssignItems<T, IndexType>(_data.get() + index, _data.get() + (index + count), count);
			/* shrink array size */
			_size -= count;

			if (allowShrinking) {
				ResizeShrink(_size, allowShrinking);
			}
		}
	}

	template <typename T>
	void TArray<T>::RemoveAtSwapImpl(IndexType index, IndexType count, const bool allowShrinking) {
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

	template <typename T>
	void TArray<T>::CheckIndex(const IndexType index) const {
		if (index > _size - 1 || _size == 0) {
			CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
			PLATFORM_BREAK();
		}
	}

	template <typename T>
	const typename TArray<T>::IndexType TArray<T>::DefaultArraySize = 8;
}

#endif //VISREAL_T_ARRAY_H
