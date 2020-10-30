/**
 * Created by rayfalling on 2020/8/30.
 * */

#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma once

#ifndef VISREAL_WINDOWS_PLATFORM_MATH_H
#define VISREAL_WINDOWS_PLATFORM_MATH_H

#include <intrin.h>
#include "Platform/GenericPlatformMath.h"
#include "Marco/MSVCPlatform.h"

namespace Engine::Core::Math {
    /**
    * Windows implementation of the Math OS functions
    **/
    struct FWindowsPlatformMath : public FGenericPlatformMath {
#if PLATFORM_ENABLE_VECTORINTRINSICS
        static FORCEINLINE int32 TruncToInt(float F) {
            return _mm_cvtt_ss2si(_mm_set_ss(F));
        }

        static FORCEINLINE float TruncToFloat(float F) {
            return (float) TruncToInt(F); // same as generic implementation, but this will call the faster trunc
        }

        static FORCEINLINE int32 RoundToInt(float F) {
            // Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
            return _mm_cvt_ss2si(_mm_set_ss(F + F + 0.5f)) >> 1;
        }

        static FORCEINLINE float RoundToFloat(float F) {
            return (float) RoundToInt(F);
        }

        static FORCEINLINE int32 FloorToInt(float F) {
            return _mm_cvt_ss2si(_mm_set_ss(F + F - 0.5f)) >> 1;
        }

        static FORCEINLINE float FloorToFloat(float F) {
            return (float) FloorToInt(F);
        }

        static FORCEINLINE int32 CeilToInt(float F) {
            // Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
            return -(_mm_cvt_ss2si(_mm_set_ss(-0.5f - (F + F))) >> 1);
        }

        static FORCEINLINE float CeilToFloat(float F) {
            // Note: the x2 is to workaround the rounding-to-nearest-even-number issue when the fraction is .5
            return (float) CeilToInt(F);
        }

        static FORCEINLINE bool IsNaN(float A) { return _isnan(A) != 0; }

        static FORCEINLINE bool IsFinite(float A) { return _finite(A) != 0; }

#pragma intrinsic( _BitScanReverse )

        static FORCEINLINE uint32 FloorLog2(uint32 Value) {
            // Use BSR to return the log2 of the integer
            unsigned long Log2;
            if (_BitScanReverse(&Log2, Value) != 0) {
                return Log2;
            }

            return 0;
        }

        static FORCEINLINE uint32 CountLeadingZeros(uint32 Value) {
            // Use BSR to return the log2 of the integer
            unsigned long Log2;
            if (_BitScanReverse(&Log2, Value) != 0) {
                return 31 - Log2;
            }

            return 32;
        }

        static FORCEINLINE uint32 CountTrailingZeros(uint32 Value) {
            if (Value == 0) {
                return 32;
            }
            unsigned long BitIndex;    // 0-based, where the LSB is 0 and MSB is 31
            _BitScanForward(&BitIndex, Value);    // Scans from LSB to MSB
            return BitIndex;
        }

        static FORCEINLINE uint32 CeilLogTwo(uint32 Arg) {
            int32 Bitmask = ((int32) (CountLeadingZeros(Arg) << 26)) >> 31;
            return (32 - CountLeadingZeros(Arg - 1)) & (~Bitmask);
        }

        static FORCEINLINE uint32 RoundUpToPowerOfTwo(uint32 Arg) {
            return 1u << CeilLogTwo(Arg);
        }

        static FORCEINLINE uint64 RoundUpToPowerOfTwo64(uint64 Arg) {
            return uint64(1) << CeilLogTwo64(Arg);
        }

#if PLATFORM_64BITS
        static FORCEINLINE uint64 CeilLogTwo64(uint64 Arg) {
            int64 Bitmask = ((int64) (CountLeadingZeros64(Arg) << 57)) >> 63;
            return (64 - CountLeadingZeros64(Arg - 1)) & (~Bitmask);
        }

        static FORCEINLINE uint64 CountLeadingZeros64(uint64 Value) {
            // Use BSR to return the log2 of the integer
            unsigned long Log2;
            if (_BitScanReverse64(&Log2, Value) != 0) {
                return 63 - Log2;
            }

            return 64;
        }

        static FORCEINLINE uint64 CountTrailingZeros64(uint64 Value) {
            if (Value == 0) {
                return 64;
            }
            unsigned long BitIndex;    // 0-based, where the LSB is 0 and MSB is 31
            _BitScanForward64(&BitIndex, Value);    // Scans from LSB to MSB
            return BitIndex;
        }
#endif

#endif
    };

    typedef FWindowsPlatformMath FPlatformMath;
}
#endif //VISREAL_WINDOWS_PLATFORM_MATH_H

#pragma clang diagnostic pop
#pragma clang diagnostic pop