/**
 * Created by rayfalling on 2020/11/18.
 *
 * Custom Array class, like std::vector
 * */

#pragma once

#ifndef VISREAL_T_ARRAY_IMPL_H
#define VISREAL_T_ARRAY_IMPL_H


#include <memory>

#include "Platform/PlatformTypes.h"

namespace Engine::Core::Types {
	/**
	 * Custom Array Class
	 * */
	template <typename T, bool ThreadSafe = false>
	class TArrayImpl {
		friend class TArrayImpl<T, ThreadSafe>;

		public:
			/* define index type */
			#ifdef PLATFORM_64BITS
			typedef uint64 IndexType;
			typedef int64 ReturnIndexType;
			#else
			typedef uint32 IndexType;
			typedef int32 ReturnIndexType;
			#endif

		protected:
			/* element count */
			IndexType _size{};
			/* max element size */
			IndexType _capacity = 0;
			/* element array */
			std::shared_ptr<T[]> _data;
			/* default capacity */
			const static IndexType DefaultArraySize;
			/* max array element size */
			const static IndexType MaxArraySize = INTPTR_MAX;

		public:
			FORCEINLINE TArrayImpl();
	};

	template <typename T, bool ThreadSafe>
	FORCEINLINE TArrayImpl<T, ThreadSafe>::TArrayImpl()
		: _capacity(this->DefaultArraySize), _data(std::shared_ptr<T[]>(new T[this->_capacity](), std::default_delete<T[]>())) {
	}

	template <typename T, bool ThreadSafe>
	const typename TArrayImpl<T, ThreadSafe>::IndexType TArrayImpl<T, ThreadSafe>::DefaultArraySize = 8;
}

#endif
