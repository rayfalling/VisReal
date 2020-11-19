/**
 * Created by rayfalling on 2020/11/19.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#include <initializer_list>
#include <memory>
#include <mutex>
#include "Container/TSafeArray.h"

#include "Logger/CoreLog.h"
#include "Marco/Constant.h"
#include "Math/VisRealMath.h"
#include "Memory/MemoryUtils.h"
#include "Platform/PlatformTypes.h"


template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>::TSafeArray() {
	this->_size = 0;
	this->_capacity = this->DefaultArraySize;
	this->_data = std::shared_ptr<T[]>(new T[this->_capacity](), std::default_delete<T[]>());
}

template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>::TSafeArray(const IndexType capacity) {
	this->_size = 0;
	this->_capacity = capacity;
	this->_data = std::shared_ptr<T[]>(new T[this->_capacity](), std::default_delete<T[]>());
}

template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>::TSafeArray(std::initializer_list<T> initList) {
	this->_size = initList.size();
	this->_capacity = initList.size();
	this->_data = std::shared_ptr<T[]>(new T[this->_capacity](), std::default_delete<T[]>());
	Core::CopyAssignItems<T, IndexType>(GetData(), initList.begin(), initList.size());
}

template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>& Engine::Core::Types::TSafeArray<T>::operator=(const TSafeArray<T>& array) {
	if (this != &array) {
		this->_size = array._size;
		this->_capacity = array._capacity;
		this->_data = array._data;
	}
	return *this;
}

template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>& Engine::Core::Types::TSafeArray<T>::operator=(TSafeArray<T>&& array) noexcept {
	if (this != &array) {
		this->_size = array->_size;
		this->_capacity = array._capacity;
		std::atomic_exchange_explicit(&this->_data, array._data);
		this->_data.swap(array._data);
	}
	return *this;
}

template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>::TSafeArray(const TSafeArray<T>& array) {
	this->_size = array._size;
	this->_capacity = array._capacity;
	this->_data = std::shared_ptr<T[]>(new T[this->_capacity](), std::default_delete<T[]>());
	Core::CopyAssignItems<T, IndexType>(GetData(), array.GetData(), array.GetCapacity());
}

template <typename T>
FORCEINLINE Engine::Core::Types::TSafeArray<T>::TSafeArray(TSafeArray<T>&& array) noexcept {
	this->_size = array._size;
	this->_capacity = array._capacity;
	this->_data.swap(array._data);
}

template <typename T>
Engine::Core::Types::TSafeArray<T>::~TSafeArray() = default;

template <typename T>
FORCEINLINE T& Engine::Core::Types::TSafeArray<T>::operator[](IndexType& index) const {
	CheckIndex(index);
	return this->_data[index];
}

template <typename T>
FORCEINLINE T& Engine::Core::Types::TSafeArray<T>::operator[](const IndexType& index) const {
	CheckIndex(index);
	return this->_data[index];
}

template <typename T>
FORCEINLINE T& Engine::Core::Types::TSafeArray<T>::operator[](IndexType&& index) const {
	CheckIndex(index);
	return this->_data[index];
}

template <typename T>
CONSTEXPR typename Engine::Core::Types::TSafeArray<T>::ReturnIndexType Engine::Core::Types::TSafeArray<T>::GetSize() const {
	return this->_size;
}

template <typename T>
CONSTEXPR typename Engine::Core::Types::TSafeArray<T>::ReturnIndexType Engine::Core::Types::TSafeArray<T>::Length() const {
	return this->_size;
}

template <typename T>
CONSTEXPR typename Engine::Core::Types::TSafeArray<T>::ReturnIndexType Engine::Core::Types::TSafeArray<T>::GetCapacity() const {
	return this->_capacity;
}

template <typename T>
CONSTEXPR T* Engine::Core::Types::TSafeArray<T>::GetData() const {
	return this->_data.get();
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Add(T& data) {
	std::lock_guard<std::mutex> lock(_mutex);
	++this->_size;
	CheckCapacity();
	GetData()[this->_size - 1] = data;
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Add(T&& data) {
	std::lock_guard<std::mutex> lock(_mutex);
	++this->_size;
	CheckCapacity();
	GetData()[this->_size - 1] = std::move(data);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::AddRange(std::initializer_list<T>& initList) {
	std::lock_guard<std::mutex> lock(_mutex);
	auto oldSize = this->_size;
	this->_size += initList.size();
	CheckCapacity();
	Core::CopyAssignItems<T, IndexType>(GetData() + oldSize, initList.begin(), initList.size());

}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::AddRange(std::initializer_list<T>&& initList) {
	std::lock_guard<std::mutex> lock(_mutex);
	auto oldSize = this->_size;
	this->_size += initList.size();
	CheckCapacity();
	Core::MoveAssignItems<T, IndexType>(GetData() + oldSize, initList.begin(), initList.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::AddRange(TSafeArray<T>& array) {
	std::lock_guard<std::mutex> lock(_mutex);
	auto oldSize = this->_size;
	this->_size += array.GetSize();
	CheckCapacity();
	Core::CopyAssignItems<T, IndexType>(GetData() + oldSize, array.GetData(), array.GetSize());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::AddRange(TSafeArray<T>&& array) {
	std::lock_guard<std::mutex> lock(_mutex);
	auto oldSize = this->_size;
	this->_size += array.GetSize();
	CheckCapacity();
	Core::MoveAssignItems<T, IndexType>(GetData() + oldSize, array.GetData(), array.GetSize());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::AddRange(std::vector<T>& vector) {
	std::lock_guard<std::mutex> lock(_mutex);
	auto oldSize = this->_size;
	this->_size += vector.size();
	CheckCapacity();
	Core::CopyAssignItems<T, IndexType>(GetData() + oldSize, vector.data(), vector.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::AddRange(std::vector<T>&& vector) {
	std::lock_guard<std::mutex> lock(_mutex);
	auto oldSize = this->_size;
	this->_size += vector.size();
	CheckCapacity();
	Core::MoveAssignItems<T, IndexType>(GetData() + oldSize, vector.data(), vector.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Assign(std::initializer_list<T>& initList) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = initList.size();
	CheckCapacity();
	Core::CopyAssignItems<T, IndexType>(GetData(), initList.begin(), initList.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Assign(std::initializer_list<T>&& initList) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = initList.size();
	CheckCapacity();
	Core::MoveAssignItems<T, IndexType>(GetData(), initList.begin(), initList.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Assign(TSafeArray<T>& array) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = array.GetSize();
	CheckCapacity();
	Core::CopyAssignItems<T, IndexType>(GetData(), array.GetData(), array.GetSize());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Assign(TSafeArray<T>&& array) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = array.GetSize();
	CheckCapacity();
	Core::MoveAssignItems(GetData(), array.GetData(), array.GetSize());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Assign(std::vector<T>& vector) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = vector.size();
	CheckCapacity();
	Core::CopyAssignItems<T, IndexType>(GetData(), vector.data(), vector.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Assign(std::vector<T>&& vector) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = vector.size();
	CheckCapacity();
	Core::MoveAssignItems<T, IndexType>(GetData(), vector.data(), vector.size());
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Clear() {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_size = 0;
	this->_capacity = this->DefaultArraySize;
	this->_data.swap(std::shared_ptr<T[]>(new T[this->_capacity](), std::default_delete<T[]>()));
}

template <typename T>
template <typename ComparisonType>
bool Engine::Core::Types::TSafeArray<T>::Contains(const ComparisonType& item) {
	for (T *data = GetData(), *dataEnd = data + this->_size; data != dataEnd; ++data) {
		if (*data == item) {
			return true;
		}
	}
	return false;
}

template <typename T>
template <typename ComparisonType>
bool Engine::Core::Types::TSafeArray<T>::Contains(const ComparisonType& item) const {
	for (T *data = GetData(), *dataEnd = data + this->_size; data != dataEnd; ++data) {
		if (*data == item) {
			return true;
		}
	}
	return false;
}

template <typename T>
template <typename Predicate>
bool Engine::Core::Types::TSafeArray<T>::ContainsByPredicate(Predicate predicate) {
	return Find(predicate) != nullptr;
}

template <typename T>
template <typename Predicate>
T* Engine::Core::Types::TSafeArray<T>::Find(Predicate predicate) {
	for (T *data = GetData(), *dataEnd = data + this->_size; data != dataEnd; ++data) {
		if (predicate(*data)) {
			return data;
		}
	}
	return nullptr;
}

template <typename T>
template <typename Predicate>
const T* Engine::Core::Types::TSafeArray<T>::Find(Predicate predicate) const {
	return const_cast<TSafeArray*>(this)->Find(predicate);
}

template <typename T>
template <typename Predicate>
T* Engine::Core::Types::TSafeArray<T>::FindLast(Predicate predicate) {
	for (T *start = GetData(), *data = start + this->_size; data != start;) {
		--data;
		if (predicate(*data)) {
			return data;
		}
	}
	return nullptr;
}

template <typename T>
template <typename Predicate>
const T* Engine::Core::Types::TSafeArray<T>::FindLast(Predicate predicate) const {
	return const_cast<TSafeArray*>(this)->FindLast(predicate);
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexOf(T& element) {
	const T* start = GetData();
	for (const T *data = start, *dataEnd = start + this->_size; data != dataEnd; ++data) {
		if (*data == element) {
			return static_cast<int32>(data - start);
		}
	}
	return INDEX_NONE;
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexOf(T&& element) {
	const T* start = GetData();
	for (const T *data = start, *dataEnd = start + this->_size; data != dataEnd; ++data) {
		if (*data == element) {
			return static_cast<int32>(data - start);
		}
	}
	return INDEX_NONE;
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexOf(T& element) const {
	return const_cast<TSafeArray*>(this)->IndexOf(element);
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexOf(T&& element) const {
	return const_cast<TSafeArray*>(this)->IndexOf(element);
}

template <typename T>
int32 Engine::Core::Types::TSafeArray<T>::IndexLast(T& element) {
	for (T *start = GetData(), *data = start + this->_size; data != start;) {
		--data;
		if (*data == element) {
			return static_cast<int32>(data - start);
		}
	}
	return INDEX_NONE;
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexLast(T&& element) {
	for (T *start = GetData(), *data = start + this->_size; data != start;) {
		--data;
		if (*data == element) {
			return static_cast<int32>(data - start);
		}
	}
	return INDEX_NONE;
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexLast(T& element) const {
	return const_cast<TSafeArray*>(this)->IndexLast(element);
}

template <typename T>
typename Engine::Core::Types::TSafeArray<T>::IndexType Engine::Core::Types::TSafeArray<T>::IndexLast(T&& element) const {
	return const_cast<TSafeArray*>(this)->IndexLast(element);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Insert(IndexType index, const T& element) {
	std::lock_guard<std::mutex> lock(_mutex);
	CheckIndex(this->_size + 1);
	++this->_size;
	CheckCapacity();
	MoveAssignItems(GetData() + index + 1, GetData() + index, this->_size - 1 - index);
	GetData()[index] = element;
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Insert(IndexType index, T&& element) {
	std::lock_guard<std::mutex> lock(_mutex);
	CheckIndex(this->_size + 1);
	++this->_size;
	CheckCapacity();
	MoveAssignItems(GetData() + index + 1, GetData() + index, this->_size - 1 - index);
	GetData()[index] = std::move(element);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveAt(const IndexType index) {
	std::lock_guard<std::mutex> lock(_mutex);
	CheckIndex(index);
	RemoveAtImpl(index, 1);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveAtSwap(const IndexType index) {
	CoreLog::GetInstance().LogWarning(TARRAY_REMOVE_AT_SWAP_WARNING);
	std::lock_guard<std::mutex> lock(_mutex);
	CheckIndex(index);
	RemoveAtSwapImpl(index, 1);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveFirst() {
	std::lock_guard<std::mutex> lock(_mutex);
	RemoveAtImpl(0, 1);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveLast() {
	std::lock_guard<std::mutex> lock(_mutex);
	RemoveAtImpl(this->_size - 1, 1);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveAtRange(const IndexType index, const IndexType count) {
	std::lock_guard<std::mutex> lock(_mutex);
	if (count > 0) {
		CheckIndex(index);
		CheckIndex(index + count);
		RemoveAtImpl(index, count);
	}
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveRange(const IndexType startIndex, const IndexType endIndex) {
	std::lock_guard<std::mutex> lock(_mutex);
	CheckIndex(startIndex);
	CheckIndex(endIndex);
	RemoveAtImpl(startIndex, endIndex - startIndex + 1);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Reserve() const {
	IndexType start = 0, end = this->_size - 1;
	while (start < end) {
		std::swap(*(GetData() + start), *(GetData() + end));
		start++;
		--end;
	}
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Resize(const IndexType size, const bool allowShrink) {
	std::lock_guard<std::mutex> lock(_mutex);
	if (size < this->_capacity) {
		ResizeShrink(size, allowShrink);
	} else if (size > this->_capacity) {
		ResizeGrow(size);
	}
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::Swap(TSafeArray<T>& array) {
	std::lock_guard<std::mutex> lock(_mutex);
	this->_data.swap(array._data);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::ResizeShrink(const IndexType size, const bool allowShrinking) {
	if (allowShrinking) {
		this->_capacity = size;
		T* newPtr = new T[this->_capacity];
		Core::CopyAssignItems<T, IndexType>(newPtr, GetData(), size);
		this->_data.reset(newPtr);
		this->_size = size;
	} else {
		this->_capacity = this->_size;
		T* newPtr = new T[this->_capacity];
		Core::CopyAssignItems<T, IndexType>(newPtr, GetData(), this->_size);
		this->_data.reset(newPtr);
	}
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::ResizeGrow(const IndexType size) {
	this->_capacity = size;
	if (this->_capacity > this->MaxArraySize) {
		CoreLog::GetInstance().LogWarning(TARRAY_MAX_SIZE);
		this->_capacity = this->MaxArraySize;
	}
	T* newPtr = new T[this->_capacity];
	Core::CopyAssignItems<T, IndexType>(newPtr, GetData(), this->_size);
	this->_data.reset(newPtr);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::GrowArrayCapacity() {
	if (this->_size == this->_capacity)return;
	auto newCapacity = this->_capacity + this->_capacity / 2;
	if (newCapacity < this->_size) newCapacity = this->_size;
	ResizeGrow(newCapacity);
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveAtImpl(IndexType index, const IndexType count,
                                                      const bool allowShrinking) {
	if (count) {
		/* Do destruct for removed element to avoid ptr in element */
		Core::DestructItems<T, IndexType>(GetData() + index, count);
		/* move elements */
		Core::MoveAssignItems<T, IndexType>(GetData() + index, GetData() + (index + count), count);
		/* shrink array size */
		this->_size -= count;

		if (allowShrinking) {
			ResizeShrink(this->_size, allowShrinking);
		}
	}
}

template <typename T>
void Engine::Core::Types::TSafeArray<T>::RemoveAtSwapImpl(IndexType index, IndexType count,
                                                          const bool allowShrinking) {
	if (count) {
		Core::DestructItems(GetData() + index, count);
		// Replace the elements in the hole created by the removal with elements from the end of the array, so the range of indices used by the array is contiguous.
		const auto numElementsInHole = count;
		const auto numElementsAfterHole = this->_size - (index + count);
		const auto numElementsToMoveIntoHole = Math::FMath::Min(numElementsInHole, numElementsAfterHole);
		if (numElementsToMoveIntoHole) {
			Core::CopyAssignItems(
					GetData() + index,
					GetData() + this->_size - numElementsToMoveIntoHole,
					numElementsToMoveIntoHole
					);
		}
		this->_size -= count;

		if (allowShrinking) {
			ResizeShrink(this->_size, allowShrinking);
		}
	}
}

template <typename T>
CONSTEXPR void Engine::Core::Types::TSafeArray<T>::CheckIndex(const IndexType index) const {
	if (index > this->_size - 1 || this->_size == 0) {
		CoreLog::GetInstance().LogError(TARRAY_OUT_OF_INDEX_ERROR);
		PLATFORM_BREAK();
	}
}

template <typename T>
CONSTEXPR void Engine::Core::Types::TSafeArray<T>::CheckCapacity() {
	if (this->_size > this->_capacity)
		GrowArrayCapacity();
}
