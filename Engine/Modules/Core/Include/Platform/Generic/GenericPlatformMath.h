/**
 * Created by rayfalling on 2020/10/30.
 *
 * Generic implementation for most platforms
 * */

#pragma once
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#ifndef VISREAL_GENERIC_PLATFORM_MATH_H
#define VISREAL_GENERIC_PLATFORM_MATH_H

#include <cmath>
#include "Marco/Constant.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Math {
	struct FGenericPlatformMath {
		/**
		 * Converts a float to an integer with truncation towards zero.
		 * @param f		Floating point value to convert
		 * @return		Truncated integer.
		 */
		static CONSTEXPR FORCEINLINE int32 TruncToInt(const float f) {
			return static_cast<int32>(f);
		}

		/**
		 * Converts a float to an integer value with truncation towards zero.
		 * @param f		Floating point value to convert
		 * @return		Truncated integer value.
		 */
		static CONSTEXPR FORCEINLINE float TruncToFloat(const float f) {
			return static_cast<float>(TruncToInt(f));
		}

		/**
		 * Converts a float to a nearest less or equal integer.
		 * @param f		Floating point value to convert
		 * @return		An integer less or equal to 'F'.
		 */
		static FORCEINLINE int32 FloorToInt(const float f) {
			return TruncToInt(floorf(f));
		}

		/**
		* Converts a float to the nearest less or equal integer.
		* @param f		Floating point value to convert
		* @return		An integer less or equal to 'F'.
		*/
		static FORCEINLINE float FloorToFloat(const float f) {
			return floorf(f);
		}

		/**
		* Converts a double to a less or equal integer.
		* @param f		Floating point value to convert
		* @return		The nearest integer value to 'F'.
		*/
		static FORCEINLINE double FloorToDouble(const double f) {
			return floor(f);
		}

		/**
		 * Converts a float to the nearest integer. Rounds up when the fraction is .5
		 * @param f		Floating point value to convert
		 * @return		The nearest integer to 'F'.
		 */
		static FORCEINLINE int32 RoundToInt(const float f) {
			return FloorToInt(f + 0.5f);
		}

		/**
		* Converts a float to the nearest integer. Rounds up when the fraction is .5
		* @param f		Floating point value to convert
		* @return		The nearest integer to 'F'.
		*/
		static FORCEINLINE float RoundToFloat(const float f) {
			return FloorToFloat(f + 0.5f);
		}

		/**
		* Converts a double to the nearest integer. Rounds up when the fraction is .5
		* @param f		Floating point value to convert
		* @return		The nearest integer to 'F'.
		*/
		static FORCEINLINE double RoundToDouble(const double f) {
			return FloorToDouble(f + 0.5);
		}

		/**
		* Converts a float to the nearest greater or equal integer.
		* @param f		Floating point value to convert
		* @return		An integer greater or equal to 'F'.
		*/
		static FORCEINLINE int32 CeilToInt(const float f) {
			return TruncToInt(ceilf(f));
		}

		/**
		* Converts a float to the nearest greater or equal integer.
		* @param f		Floating point value to convert
		* @return		An integer greater or equal to 'F'.
		*/
		static FORCEINLINE float CeilToFloat(const float f) {
			return ceilf(f);
		}

		/**
		* Converts a double to the nearest greater or equal integer.
		* @param f		Floating point value to convert
		* @return		An integer greater or equal to 'F'.
		*/
		static FORCEINLINE double CeilToDouble(const double f) {
			return ceil(f);
		}

		/**
		* Returns signed fractional part of a float.
		* @param value	Floating point value to convert
		* @return		A float between >=0 and < 1 for nonnegative input. A float between >= -1 and < 0 for negative input.
		*/
		static FORCEINLINE float Fractional(const float value) {
			return value - TruncToFloat(value);
		}

		/**
		* Returns the fractional part of a float.
		* @param value	Floating point value to convert
		* @return		A float between >=0 and < 1.
		*/
		static FORCEINLINE float Frac(const float value) {
			return value - FloorToFloat(value);
		}

		/**
		* Breaks the given value into an integral and a fractional part.
		* @param invalue	Floating point value to convert
		* @param outIntPart Floating point value that receives the integral part of the number.
		* @return			The fractional part of the number.
		*/
		static FORCEINLINE float Modf(const float invalue, float* outIntPart) {
			return modff(invalue, outIntPart);
		}

		/**
		* Breaks the given value into an integral and a fractional part.
		* @param invalue	Floating point value to convert
		* @param outIntPart Floating point value that receives the integral part of the number.
		* @return			The fractional part of the number.
		*/
		static FORCEINLINE double Modf(const double invalue, double* outIntPart) {
			return modf(invalue, outIntPart);
		}

		// Returns e^value
		static FORCEINLINE float Exp(const float value) { return expf(value); }

		// Returns 2^value
		static FORCEINLINE float Exp2(const float value) {
			return powf(2.f, value); /*exp2f(value);*/
		}

		static FORCEINLINE float Loge(const float value) { return logf(value); }

		static FORCEINLINE float LogX(const float base, const float value) { return Loge(value) / Loge(base); }

		// 1.0 / Loge(2) = 1.4426950f
		static FORCEINLINE float Log2(const float value) { return Loge(value) * 1.4426950f; }

		/** 
		* Returns the floating-point remainder of X / Y
		* Warning: Always returns remainder toward 0, not toward the smaller multiple of Y.
		*			So for example Fmod(2.8f, 2) gives .8f as you would expect, however, Fmod(-2.8f, 2) gives -.8f, NOT 1.2f 
		* Use Floor instead when snapping positions that can be negative to a grid
		*
		* This is forced to *NOT* inline so that divisions by constant Y does not get optimized in to an inverse scalar multiply,
		* which is not consistent with the intent nor with the vectorized version.
		*/
		static FORCENOINLINE float Fmod(float x, float y);

		static FORCEINLINE float Sin(const float value) { return sinf(value); }

		static FORCEINLINE float Asin(const float value) {
			return asinf((value < -1.f) ? -1.f : ((value < 1.f) ? value : 1.f));
		}

		static FORCEINLINE float Sinh(const float value) { return sinhf(value); }

		static FORCEINLINE float Cos(const float value) { return cosf(value); }

		static FORCEINLINE float Acos(const float value) {
			return acosf((value < -1.f) ? -1.f : ((value < 1.f) ? value : 1.f));
		}

		static FORCEINLINE float Tan(const float value) { return tanf(value); }

		static FORCEINLINE float Atan(const float value) { return atanf(value); }

		static float Atan2(float y, float x);

		static FORCEINLINE float Sqrt(const float value) { return sqrtf(value); }

		static FORCEINLINE float Pow(const float a, const float b) { return powf(a, b); }

		/** Computes a fully accurate inverse square root */
		static FORCEINLINE float InvSqrt(const float f) {
			return 1.0f / sqrtf(f);
		}

		/** Computes a faster but less accurate inverse square root */
		static FORCEINLINE float InvSqrtEst(const float f) {
			return InvSqrt(f);
		}

		/** Return true if value is NaN (not a number). */
		static FORCEINLINE bool IsNaN(float a) {
			return ((*(uint32*)&a) & 0x7FFFFFFF) > 0x7F800000;
		}

		/** Return true if value is finite (not NaN and not Infinity). */
		static FORCEINLINE bool IsFinite(float a) {
			return ((*(uint32*)&a) & 0x7F800000) != 0x7F800000;
		}

		static FORCEINLINE bool IsNegativeFloat(const float& a) {
			return ((*(uint32*)&a) >= static_cast<uint32>(0x80000000)); // Detects sign bit.
		}

		static FORCEINLINE bool IsNegativeDouble(const double& a) {
			return ((*(uint64*)&a) >= static_cast<uint64>(0x8000000000000000)); // Detects sign bit.
		}

		#pragma clang diagnostic push
		#pragma ide diagnostic ignored "cert-msc50-cpp"
		/** Returns a random integer between 0 and RAND_MAX, inclusive */
		static FORCEINLINE int32 Rand() { return rand(); }
		#pragma clang diagnostic pop

		/** Seeds global random number functions Rand() and FRand() */
		static FORCEINLINE void RandInit(const int32 seed) { srand(static_cast<unsigned int>(seed)); }

		/** Returns a random float between 0 and 1, inclusive. */
		static FORCEINLINE float FRand() { return Rand() / static_cast<float>(RAND_MAX); }

		/** Seeds future calls to SRand() */
		static void SRandInit(int32 seed);

		/** Returns the current seed for SRand(). */
		static int32 GetRandSeed();

		/** Returns a seeded random float in the range [0,1), using the seed from SRandInit(). */
		static float SRand();

		/**
		 * Computes the base 2 logarithm for an integer value that is greater than 0.
		 * The result is rounded down to the nearest integer.
		 *
		 * @param value		The value to compute the log of
		 * @return			Log2 of value. 0 if value is 0.
		 */
		static FORCEINLINE uint32 FloorLog2(uint32 value) {
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
		 *
		 * @param value		The value to compute the log of
		 * @return			Log2 of value. 0 if value is 0.
		 */
		static FORCEINLINE uint64 FloorLog2_64(uint64 value) {
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

		/**
		 * Counts the number of leading zeros in the bit representation of the value
		 *
		 * @param value the value to determine the number of leading zeros for
		 *
		 * @return the number of zeros before the first "on" bit
		 */
		static FORCEINLINE uint32 CountLeadingZeros(const uint32 value) {
			if (value == 0) return 32;
			return 31 - FloorLog2(value);
		}

		/**
		 * Counts the number of leading zeros in the bit representation of the 64-bit value
		 *
		 * @param value the value to determine the number of leading zeros for
		 *
		 * @return the number of zeros before the first "on" bit
		 */
		static FORCEINLINE uint64 CountLeadingZeros64(const uint64 value) {
			if (value == 0) return 64;
			return 63 - FloorLog2_64(value);
		}

		/**
		 * Counts the number of trailing zeros in the bit representation of the value
		 *
		 * @param value the value to determine the number of trailing zeros for
		 *
		 * @return the number of zeros after the last "on" bit
		 */
		static FORCEINLINE uint32 CountTrailingZeros(uint32 value) {
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
		 *
		 * @param value the value to determine the number of trailing zeros for
		 *
		 * @return the number of zeros after the last "on" bit
		 */
		static FORCEINLINE uint64 CountTrailingZeros64(uint64 value) {
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
		 * Returns smallest N such that (1<<N)>=Arg.
		 * Note: CeilLogTwo(0)=0 because (1<<0)=1 >= 0.
		 */
		static FORCEINLINE uint32 CeilLogTwo(const uint32 arg) {
			const int32 bitmask = static_cast<int32>(CountLeadingZeros(arg) << 26) >> 31;
			return (32 - CountLeadingZeros(arg - 1)) & (~bitmask);
		}

		static FORCEINLINE uint64 CeilLogTwo64(const uint64 arg) {
			const int64 bitmask = static_cast<int64>(CountLeadingZeros64(arg) << 57) >> 63;
			return (64 - CountLeadingZeros64(arg - 1)) & (~bitmask);
		}

		/** @return Rounds the given number up to the next highest power of two. */
		static FORCEINLINE uint32 RoundUpToPowerOfTwo(const uint32 arg) {
			return 1u << CeilLogTwo(arg);
		}

		static FORCEINLINE uint64 RoundUpToPowerOfTwo64(const uint64 v) {
			return static_cast<uint64>(1) << CeilLogTwo64(v);
		}

		/** Spreads bits to every other. */
		static FORCEINLINE uint32 MortonCode2(uint32 x) {
			x &= 0x0000ffff;
			x = (x ^ (x << 8)) & 0x00ff00ff;
			x = (x ^ (x << 4)) & 0x0f0f0f0f;
			x = (x ^ (x << 2)) & 0x33333333;
			x = (x ^ (x << 1)) & 0x55555555;
			return x;
		}

		/** Reverses MortonCode2. Compacts every other bit to the right. */
		static FORCEINLINE uint32 ReverseMortonCode2(uint32 x) {
			x &= 0x55555555;
			x = (x ^ (x >> 1)) & 0x33333333;
			x = (x ^ (x >> 2)) & 0x0f0f0f0f;
			x = (x ^ (x >> 4)) & 0x00ff00ff;
			x = (x ^ (x >> 8)) & 0x0000ffff;
			return x;
		}

		/** Spreads bits to every 3rd. */
		static FORCEINLINE uint32 MortonCode3(uint32 x) {
			x &= 0x000003ff;
			x = (x ^ (x << 16)) & 0xff0000ff;
			x = (x ^ (x << 8)) & 0x0300f00f;
			x = (x ^ (x << 4)) & 0x030c30c3;
			x = (x ^ (x << 2)) & 0x09249249;
			return x;
		}

		/** Reverses MortonCode3. Compacts every 3rd bit to the right. */
		static FORCEINLINE uint32 ReverseMortonCode3(uint32 x) {
			x &= 0x09249249;
			x = (x ^ (x >> 2)) & 0x030c30c3;
			x = (x ^ (x >> 4)) & 0x0300f00f;
			x = (x ^ (x >> 8)) & 0xff0000ff;
			x = (x ^ (x >> 16)) & 0x000003ff;
			return x;
		}

		/**
		 * Returns value based on comparand. The main purpose of this function is to avoid
		 * branching based on floating point comparison which can be avoided via compiler
		 * intrinsics.
		 *
		 * Please note that we don't define what happens in the case of NaNs as there might
		 * be platform specific differences.
		 *
		 * @param	comparand		Comparand the results are based on
		 * @param	valueGeZero		Return value if Comparand >= 0
		 * @param	valueLtZero		Return value if Comparand < 0
		 *
		 * @return	valueGEZero if Comparand >= 0, valueLTZero otherwise
		 */
		static CONSTEXPR FORCEINLINE float FloatSelect(float comparand, float valueGeZero, float valueLtZero);

		/**
		 * Returns value based on comparand. The main purpose of this function is to avoid
		 * branching based on floating point comparison which can be avoided via compiler
		 * intrinsics.
		 *
		 * Please note that we don't define what happens in the case of NaNs as there might
		 * be platform specific differences.
		 *
		 * @param	comparand		Comparand the results are based on
		 * @param	valueGeZero		Return value if Comparand >= 0
		 * @param	valueLtZero		Return value if Comparand < 0
		 *
		 * @return	valueGEZero if Comparand >= 0, valueLTZero otherwise
		 */
		static CONSTEXPR FORCEINLINE double FloatSelect(const double comparand, double valueGeZero, double valueLtZero) {
			return comparand >= 0.0 ? valueGeZero : valueLtZero;
		}

		/** Computes absolute value in a generic way */
		template <class T>
		static CONSTEXPR FORCEINLINE T Abs(const T a) {
			return (a >= static_cast<T>(0)) ? a : -a;
		}

		/** Returns 1, 0, or -1 depending on relation of T to 0 */
		template <class T>
		static CONSTEXPR FORCEINLINE T Sign(const T a) {
			return (a > static_cast<T>(0))
				       ? static_cast<T>(1)
				       : ((a < static_cast<T>(0)) ? static_cast<T>(-1) : static_cast<T>(0));
		}

		/** Returns higher value in a generic way */
		template <class T>
		static CONSTEXPR FORCEINLINE T Max(const T a, const T b) {
			return (a >= b) ? a : b;
		}

		/** Returns lower value in a generic way */
		template <class T>
		static CONSTEXPR FORCEINLINE T Min(const T a, const T b) {
			return (a <= b) ? a : b;
		}

		static FORCEINLINE int32 CountBits(uint64 bits) {
			// https://en.wikipedia.org/wiki/Hamming_weight
			bits -= (bits >> 1) & 0x5555555555555555ull;
			bits = (bits & 0x3333333333333333ull) + ((bits >> 2) & 0x3333333333333333ull);
			bits = (bits + (bits >> 4)) & 0x0f0f0f0f0f0f0f0full;
			return static_cast<int32>((bits * 0x0101010101010101) >> 56);
		}

		private:
			/** Error reporting for Fmod. Not inlined to avoid compilation issues and avoid all the checks and error reporting at all callsites. */
			static void FmodReportError(float x, float y);
	};

	constexpr float FGenericPlatformMath::FloatSelect(const float comparand, float valueGeZero, float valueLtZero) {
		return comparand >= 0.f ? valueGeZero : valueLtZero;
	}

	/** Float specialization */
	template <>
	FORCEINLINE float FGenericPlatformMath::Abs(const float a) {
		return fabsf(a);
	}
}

#endif //VISREAL_GENERIC_PLATFORM_MATH_H

#pragma clang diagnostic pop
#pragma clang diagnostic pop
