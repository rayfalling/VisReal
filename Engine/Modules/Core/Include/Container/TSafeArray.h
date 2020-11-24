/**
 * Created by rayfalling on 2020/11/18.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#ifndef VISREAL_T_SAFE_ARRAY_H
#define VISREAL_T_SAFE_ARRAY_H

#include <initializer_list>
#include <mutex>

#include "TArrayImpl.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Types {
	template <typename T>
	class TSafeArray : public TArrayImpl<T, true> {
		template <typename Other>
		friend class TSafeArray;

		/* define index type */
		#ifdef PLATFORM_64BITS
		typedef uint64 IndexType;
		typedef int64 ReturnIndexType;
		#else
		typedef uint32 IndexType;
		typedef int32 ReturnIndexType;
		#endif

		public:
			TSafeArray();

			explicit TSafeArray(IndexType capacity);

			TSafeArray(std::initializer_list<T> initList);

			/* copy assignment operator */
			TSafeArray<T>& operator=(const TSafeArray& array);

			/* move assignment operator */
			TSafeArray<T>& operator=(TSafeArray&& array) noexcept;

			/* Copy Construct, copy deep data to new Instance */
			TSafeArray(const TSafeArray<T>& array);

			/* Move Construct, copy deep data to new Instance */
			TSafeArray(TSafeArray<T>&& array) noexcept;

			~TSafeArray();

		private:
			/* thread mutex */
			std::mutex _mutex;

		public:
			/* return element index */
			T& operator[](IndexType& index) const;

			/* return element index */
			T& operator[](const IndexType& index) const;

			/* return element index */
			T& operator[](IndexType&& index) const;

			/* return size */
			[[nodiscard]] CONSTEXPR ReturnIndexType GetSize() const;

			/* return size */
			[[nodiscard]] CONSTEXPR ReturnIndexType Length() const;

			/* return capacity */
			[[nodiscard]] CONSTEXPR ReturnIndexType GetCapacity() const;

		protected:
			[[nodiscard]] CONSTEXPR T* GetData() const;

		public:
			/* Add new Element */
			void Add(T& data);

			/* Add new Element */
			void Add(T&& data);

			/* Add new Elements */
			void AddRange(std::initializer_list<T>& initList);

			/* Add new Elements */
			void AddRange(std::initializer_list<T>&& initList);

			/* Add new Elements */
			void AddRange(TSafeArray<T>& array);

			/* Add new Elements */
			void AddRange(TSafeArray<T>&& array);

			/* Add new Elements */
			void AddRange(std::vector<T>& vector);

			/* Add new Elements */
			void AddRange(std::vector<T>&& vector);

			/* Set new Elements */
			void Assign(std::initializer_list<T>& initList);

			/* Set new Elements */
			void Assign(std::initializer_list<T>&& initList);

			/* Set new Elements */
			void Assign(TSafeArray<T>& array);

			/* Set new Elements */
			void Assign(TSafeArray<T>&& array);

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
			/* Check is the array is empty */
			[[nodiscard]] bool Empty() const;

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			const T* Find(Predicate predicate) const;

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			const T* FindLast(Predicate predicate) const;

			/**
			 * get the index of given element, equal by predicate function
			 *
			 * @return index in the array or -1 not found
			 * */
			template <typename Predicate = std::function<bool(T, T)>>
			ReturnIndexType IndexOf(T& element, Predicate predicate) const;

			/**
			 * get the index of given element, equal by predicate function
			 *
			 * @return index in the array or -1 not found
			 * */
			template <typename Predicate = std::function<bool(T, T)>>
			ReturnIndexType IndexOf(T&& element, Predicate predicate) const;

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			ReturnIndexType IndexOf(T& element) const;

			/**
			 * get the index of given element
			 *
			 * @return index in the array or -1 not found
			 * */
			ReturnIndexType IndexOf(T&& element) const;

			/* Finds an element which matches a predicate functor. */
			ReturnIndexType IndexLast(T& element) const;

			/* Finds an element which matches a predicate functor. */
			ReturnIndexType IndexLast(T&& element) const;

			/* Insert to index */
			void Insert(IndexType index, const T& element);

			/* Insert to index */
			void Insert(IndexType index, T&& element);

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
			void Reserve() const;

			/* resize the array */
			void Resize(IndexType size, bool allowShrink = true);

			/* Swap two array data */
			void Swap(TSafeArray<T>& array);

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
			void RemoveAtSwapImpl(IndexType index, IndexType count = 1,
			                      bool allowShrinking = true);

			/* check if the index is out of array size */
			CONSTEXPR void CheckIndex(IndexType index) const;

			/* check if should grow array capacity */
			CONSTEXPR void CheckCapacity();
	};
}

#include "Container/TSafeArray.inl"
#endif
