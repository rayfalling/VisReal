#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
/**
 * Created by rayfalling on 2020/10/18.
 * */

#ifndef VISREAL_VISREAL_MATH_H
#define VISREAL_VISREAL_MATH_H

#include <cmath>
#include "Types/PlatformTypes.h"

namespace Engine::Core::Math {
    /** Converts a float to an integer with truncation towards zero. */
    static int32 TruncToInt(float value) { return (int32) value; }

    /** Converts a float to an integer value with truncation towards zero. */
    static float TruncToFloat(float value) { return (float) TruncToInt(value); }

    /** Converts a float to a nearest less or equal integer. */
    static int32 FloorToInt(float value) { return TruncToInt(floorf(value)); }

    /** Converts a float to the nearest less or equal integer. */
    static float FloorToFloat(float value) { return floorf(value); }

    /** Converts a double to a less or equal integer. */
    static double FloorToDouble(double value) { return floor(value); }

    /** Converts a float to the nearest integer. Rounds up when the fraction is .5 */
    static int32 RoundToInt(float value) { return FloorToInt(value + 0.5f); }

    /** Converts a float to the nearest integer. Rounds up when the fraction is .5 */
    static float RoundToFloat(float value) { return FloorToFloat(value + 0.5f); }

    /** Converts a double to the nearest integer. Rounds up when the fraction is .5 */
    static double RoundToDouble(double value) { return FloorToDouble(value + 0.5); }

    /** Converts a float to the nearest greater or equal integer. */
    static int32 CeilToInt(float value) { return TruncToInt(ceilf(value)); }

    /* Converts a float to the nearest greater or equal integer. */
    static float CeilToFloat(float value) { return std::ceilf(value); }

    /* Converts a float to the nearest greater or equal integer. */
    static double CeilToDouble(double value) { return std::ceil(value); }

    /* Returns e^value */
    static float Exp(float value) { return std::expf(value); }

    /* Returns 2^value */
    static float Exp2(float value) { return std::powf(2.f, value); /*exp2f(value);*/ }

    static float Loge(float value) { return std::logf(value); }

    static float LogX(float Base, float value) { return Loge(value) / Loge(Base); }

    /* fast compute: 1.0 / Loge(2) = 1.4426950f */
    static float Log2(float value) { return Loge(value) * 1.4426950f; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

    /* Returns a random integer between 0 and RAND_MAX, inclusive */
    static int32 Rand() { return std::rand(); }

#pragma clang diagnostic pop

    /* Seeds global random number functions Rand() and FRand() */
    static void RandInit(uint32 seed) { std::srand(seed); }

    /* Returns a random float between 0 and 1, inclusive. */
    static float FRand() { return Rand() / (float) RAND_MAX; }

    /* Seeds future calls to SRand() */
    static void SRandInit(int32 Seed);

    /* Returns the current seed for SRand(). */
    static int32 GetRandSeed();

    /* Returns a seeded random float in the range [0,1), using the seed from SRandInit(). */
    static float SRand();

    /**
     * Computes the base 2 logarithm for an integer value that is greater than 0.
     * The result is rounded down to the nearest integer.
     */
    static uint32 FloorLog2(uint32 value) {
        uint32 pos = 0;
        if (value >= 1 << 16) {
            value >>= 16;
            pos += 16;
        }
        if (value >= 1 << 8) {
            value >>= 8;
            pos += 8;
        }
        if (value >= 1 << 4) {
            value >>= 4;
            pos += 4;
        }
        if (value >= 1 << 2) {
            value >>= 2;
            pos += 2;
        }
        if (value >= 1 << 1) { pos += 1; }
        return (value == 0) ? 0 : pos;
    }

    /**
     * Computes the base 2 logarithm for a 64-bit value that is greater than 0.
     * The result is rounded down to the nearest integer.
     */
    static uint64 FloorLog2_64(uint64 value) {
        uint64 pos = 0;
        if (value >= 1ull << 32) {
            value >>= 32;
            pos += 32;
        }
        if (value >= 1ull << 16) {
            value >>= 16;
            pos += 16;
        }
        if (value >= 1ull << 8) {
            value >>= 8;
            pos += 8;
        }
        if (value >= 1ull << 4) {
            value >>= 4;
            pos += 4;
        }
        if (value >= 1ull << 2) {
            value >>= 2;
            pos += 2;
        }
        if (value >= 1ull << 1) { pos += 1; }
        return (value == 0) ? 0 : pos;
    }

    /* Counts the number of leading zeros in the bit representation of the value */
    static uint32 CountLeadingZeros(uint32 value) {
        if (value == 0) return 32;
        return 31 - FloorLog2(value);
    }

    /* Counts the number of leading zeros in the bit representation of the 64-bit value */
    static uint64 CountLeadingZeros64(uint64 value) {
        if (value == 0) return 64;
        return 63 - FloorLog2_64(value);
    }

    /* Counts the number of trailing zeros in the bit representation of the value */
    static uint32 CountTrailingZeros(uint32 value) {
        if (value == 0) {
            return 32;
        }
        uint32 Result = 0;
        while ((value & 1) == 0) {
            value >>= 1;
            ++Result;
        }
        return Result;
    }

    /**
     * Counts the number of trailing zeros in the bit representation of the value
     */
    static uint64 CountTrailingZeros64(uint64 value) {
        if (value == 0) {
            return 64;
        }
        uint64 Result = 0;
        while ((value & 1) == 0) {
            value >>= 1;
            ++Result;
        }
        return Result;
    }

    /**
     * Returns smallest N such that (1<<N)>=value.
     * Note: CeilLogTwo(0)=0 because (1<<0)=1 >= 0.
     */
    static uint32 CeilLogTwo(uint32 value) {
        int32 Bitmask = ((int32) (CountLeadingZeros(value) << 26)) >> 31;
        return (32 - CountLeadingZeros(value - 1)) & (~Bitmask);
    }

    static uint64 CeilLogTwo64(uint64 value) {
        int64 Bitmask = ((int64) (CountLeadingZeros64(value) << 57)) >> 63;
        return (64 - CountLeadingZeros64(value - 1)) & (~Bitmask);
    }

    /* Rounds the given number up to the next highest power of two. */
    static uint32 RoundUpToPowerOfTwo(uint32 value) {
        return 1u << CeilLogTwo(value);
    }

    static uint64 RoundUpToPowerOfTwo64(uint64 V) {
        return uint64(1) << CeilLogTwo64(V);
    }

    static int32 UpperPowerOfTwo(float value) {
        return CeilToInt(Log2(value));
    }
}


#endif //VISREAL_VISREAL_MATH_H
#pragma clang diagnostic pop