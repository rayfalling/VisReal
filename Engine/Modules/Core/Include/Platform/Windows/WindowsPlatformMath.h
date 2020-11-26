/**
 * Created by rayfalling on 2020/8/30.
 * */

#pragma once
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#ifndef VISREAL_WINDOWS_PLATFORM_MATH_H
#define VISREAL_WINDOWS_PLATFORM_MATH_H

#include <intrin.h>
#include "Platform/Generic/GenericPlatformMath.h"

namespace Engine::Core::Math {
	/**
	* Windows implementation of the Math OS functions
	**/
	struct FWindowsPlatformMath : public FGenericPlatformMath {
		#if PLATFORM_ENABLE_VECTORINTRINSICS
		static FORCEINLINE int32 TruncToInt(const float f) {
			return _mm_cvtt_ss2si(_mm_set_ss(f));
		}

		static FORCEINLINE float TruncToFloat(const float f) {
			return static_cast<float>(TruncToInt(f));
			// same as generic implementation, but this will call the faster trunc
		}

		static FORCEINLINE int32 RoundToInt(const float f) {
			// Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
			return _mm_cvt_ss2si(_mm_set_ss(f + f + 0.5f)) >> 1;
		}

		static FORCEINLINE float RoundToFloat(const float f) {
			return static_cast<float>(RoundToInt(f));
		}

		static FORCEINLINE int32 FloorToInt(const float f) {
			return _mm_cvt_ss2si(_mm_set_ss(f + f - 0.5f)) >> 1;
		}

		static FORCEINLINE float FloorToFloat(const float f) {
			return static_cast<float>(FloorToInt(f));
		}

		static FORCEINLINE int32 CeilToInt(const float f) {
			// Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
			return -(_mm_cvt_ss2si(_mm_set_ss(-0.5f - (f + f))) >> 1);
		}

		static FORCEINLINE float CeilToFloat(const float f) {
			// Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
			return static_cast<float>(CeilToInt(f));
		}

		static FORCEINLINE bool IsNaN(const float a) { return _isnan(a) != 0; }

		static FORCEINLINE bool IsFinite(const float a) { return _finite(a) != 0; }

		#pragma intrinsic( _BitScanReverse )

		static FORCEINLINE uint32 FloorLog2(const uint32 value) {
			// Use BSR to return the log2 of the integer
			unsigned long log2;
			if (_BitScanReverse(&log2, value) != 0) {
				return log2;
			}

			return 0;
		}

		static FORCEINLINE uint32 CountLeadingZeros(const uint32 value) {
			// Use BSR to return the log2 of the integer
			unsigned long log2;
			if (_BitScanReverse(&log2, value) != 0) {
				return 31 - log2;
			}

			return 32;
		}

		static FORCEINLINE uint32 CountTrailingZeros(const uint32 value) {
			if (value == 0) {
				return 32;
			}
			unsigned long bitIndex;            // 0-based, where the LSB is 0 and MSB is 31
			_BitScanForward(&bitIndex, value); // Scans from LSB to MSB
			return bitIndex;
		}

		static FORCEINLINE uint32 CeilLogTwo(const uint32 arg) {
			const int32 bitmask = static_cast<int32>(CountLeadingZeros(arg) << 26) >> 31;
			return (32 - CountLeadingZeros(arg - 1)) & (~bitmask);
		}

		static FORCEINLINE uint32 RoundUpToPowerOfTwo(const uint32 arg) {
			return 1u << CeilLogTwo(arg);
		}

		static FORCEINLINE uint64 RoundUpToPowerOfTwo64(const uint64 arg) {
			return static_cast<uint64>(1) << CeilLogTwo64(arg);
		}

		#if PLATFORM_64BITS
		static FORCEINLINE uint64 CeilLogTwo64(const uint64 arg) {
			const int32 bitmask = static_cast<int64>(CountLeadingZeros64(arg) << 57) >> 63;
			return (64 - CountLeadingZeros64(arg - 1)) & (~bitmask);
		}

		static FORCEINLINE uint64 CountLeadingZeros64(const uint64 value) {
			// Use BSR to return the log2 of the integer
			unsigned long log2;
			if (_BitScanReverse64(&log2, value) != 0) {
				return 63 - log2;
			}

			return 64;
		}

		static FORCEINLINE uint64 CountTrailingZeros64(const uint64 value) {
			if (value == 0) {
				return 64;
			}
			unsigned long bitIndex;              // 0-based, where the LSB is 0 and MSB is 31
			_BitScanForward64(&bitIndex, value); // Scans from LSB to MSB
			return bitIndex;
		}
		#endif

		#endif
	};

	typedef FWindowsPlatformMath FPlatformMath;
}
#endif //VISREAL_WINDOWS_PLATFORM_MATH_H

#pragma clang diagnostic pop
#pragma clang diagnostic pop
