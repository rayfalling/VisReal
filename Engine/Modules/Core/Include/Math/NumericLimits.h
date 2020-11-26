/**
 * Created by rayfalling on 2020/11/9.
 * */

#pragma once

#ifndef VISREAL_NUMERIC_LIMITS_H
#define VISREAL_NUMERIC_LIMITS_H

#include "Platform/PreCompile/PlatformTypes.h"

namespace Engine::Core::Math {

	/* Numeric constants
	 *****************************************************************************/

	#define MIN_UINT8		((uint8)	0x00)
	#define	MIN_UINT16		((uint16)	0x0000)
	#define	MIN_UINT32		((uint32)	0x00000000)
	#define MIN_UINT64		((uint64)	0x0000000000000000)
	#define MIN_INT8		((int8)		-128)
	#define MIN_INT16		((int16)	-32768)
	#define MIN_INT32		((int32)	0x80000000)
	#define MIN_INT64		((int64)	0x8000000000000000)

	#define MAX_UINT8		((uint8)	0xff)
	#define MAX_UINT16		((uint16)	0xffff)
	#define MAX_UINT32		((uint32)	0xffffffff)
	#define MAX_UINT64		((uint64)	0xffffffffffffffff)
	#define MAX_INT8		((int8)		0x7f)
	#define MAX_INT16		((int16)	0x7fff)
	#define MAX_INT32		((int32)	0x7fffffff)
	#define MAX_INT64		((int64)	0x7fffffffffffffff)

	#define MIN_FLT			(1.175494351e-38F)			/* min positive value */
	#define MAX_FLT			(3.402823466e+38F)
	#define MIN_DBL			(2.2250738585072014e-308)	/* min positive value */
	#define MAX_DBL			(1.7976931348623158e+308)


	/* Numeric type traits
	 *****************************************************************************/

	/**
	 * Helper class to map a numeric type to its limits
	 */
	template <typename NumericType>
	struct TNumericLimits;


	/**
	 * Numeric limits for const types
	 */
	template <typename NumericType>
	struct TNumericLimits<const NumericType>
			: public TNumericLimits<NumericType> {
	};


	/**
	 * Numeric limits for volatile types
	 */
	template <typename NumericType>
	struct TNumericLimits<volatile NumericType>
			: public TNumericLimits<NumericType> {
	};


	/**
	 * Numeric limits for const volatile types
	 */
	template <typename NumericType>
	struct TNumericLimits<const volatile NumericType>
			: public TNumericLimits<NumericType> {
	};


	template <>
	struct TNumericLimits<uint8> {
		typedef uint8 NumericType;

		static constexpr NumericType Min() {
			return MIN_UINT8;
		}

		static constexpr NumericType Max() {
			return MAX_UINT8;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<uint16> {
		typedef uint16 NumericType;

		static constexpr NumericType Min() {
			return MIN_UINT16;
		}

		static constexpr NumericType Max() {
			return MAX_UINT16;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<uint32> {
		typedef uint32 NumericType;

		static constexpr NumericType Min() {
			return MIN_UINT32;
		}

		static constexpr NumericType Max() {
			return MAX_UINT32;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<uint64> {
		typedef uint64 NumericType;

		static constexpr NumericType Min() {
			return MIN_UINT64;
		}

		static constexpr NumericType Max() {
			return MAX_UINT64;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<int8> {
		typedef int8 NumericType;

		static constexpr NumericType Min() {
			return MIN_INT8;
		}

		static constexpr NumericType Max() {
			return MAX_INT8;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<int16> {
		typedef int16 NumericType;

		static constexpr NumericType Min() {
			return MIN_INT16;
		}

		static constexpr NumericType Max() {
			return MAX_INT16;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<int32> {
		typedef int32 NumericType;

		static constexpr NumericType Min() {
			return MIN_INT32;
		}

		static constexpr NumericType Max() {
			return MAX_INT32;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<int64> {
		typedef int64 NumericType;

		static constexpr NumericType Min() {
			return MIN_INT64;
		}

		static constexpr NumericType Max() {
			return MAX_INT64;
		}

		static constexpr NumericType Lowest() {
			return Min();
		}
	};


	template <>
	struct TNumericLimits<float> {
		typedef float NumericType;

		static constexpr NumericType Min() {
			return MIN_FLT;
		}

		static constexpr NumericType Max() {
			return MAX_FLT;
		}

		static constexpr NumericType Lowest() {
			return -Max();
		}
	};


	template <>
	struct TNumericLimits<double> {
		typedef double NumericType;

		static constexpr NumericType Min() {
			return MIN_DBL;
		}

		static constexpr NumericType Max() {
			return MAX_DBL;
		}

		static constexpr NumericType Lowest() {
			return -Max();
		}
	};

}

#endif // VISREAL_NUMERIC_LIMITS_H
