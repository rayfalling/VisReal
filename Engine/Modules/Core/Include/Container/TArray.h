/**
 * Created by rayfalling on 2020/10/18.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#ifndef VISREAL_T_ARRAY_H
#define VISREAL_T_ARRAY_H

#include <initializer_list>

#include "TArrayImpl.h"
#include "Logger/CoreLog.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Types {
	template <typename T>
	class TArray : public TArrayImpl<T, false> {
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
			TArray<T>& operator=(const TArray& array);

			/* move assignment operator */
			TArray<T>& operator=(TArray&& array) noexcept;

			/* Copy Construct, copy deep data to new Instance */
			TArray(const TArray<T>& array);

			/* Move Construct, copy deep data to new Instance */
			TArray(TArray<T>&& array) noexcept;

			~TArray();

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
			T* FindLast(Predicate predicate);

			/* Finds an element which matches a predicate functor. */
			template <typename Predicate>
			const T* FindLast(Predicate predicate) const;

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
			CONSTEXPR void CheckIndex(IndexType index) const;

			/* check if should grow array capacity */
			CONSTEXPR void CheckCapacity();
	};
}

#include "Container/TArray.inl"
#endif //VISREAL_T_ARRAY_H
