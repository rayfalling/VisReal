/**
 * Created by rayfalling on 2020/10/30.
 * */

#pragma once
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include "Platform/Generic/GenericPlatformMath.h"
#include "Logger/CoreLog.h"
#include "Math/VisRealMathUtility.h"

using namespace Engine::Core::Math;

static int32 GsRandSeed;

void FGenericPlatformMath::SRandInit(int32 Seed) {
	GsRandSeed = Seed;
}

int32 FGenericPlatformMath::GetRandSeed() {
	return GsRandSeed;
}

float FGenericPlatformMath::SRand() {
	GsRandSeed = (GsRandSeed * 196314165) + 907633515;
	union {
		float F;
		int32 I;
	} result{};
	union {
		float F;
		int32 I;
	} temp{};
	const auto SRandTemp = 1.0f;
	temp.F = SRandTemp;
	result.I = (temp.I & 0xff800000) | (GsRandSeed & 0x007fffff);
	return Fractional(result.F);
}

float FGenericPlatformMath::Atan2(float Y, float X) {
	//return atan2f(Y,X);
	// atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
	// We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.
	// On PC this has been measured to be 2x faster than the std C version.

	const auto absX = Abs(X);
	const auto absY = Abs(Y);
	const auto yAbsBigger = (absY > absX);
	auto t0 = yAbsBigger ? absY : absX;       // Max(absY, absX)
	const auto t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

	if (t0 == 0.f)
		return 0.f;

	auto t3 = t1 / t0;
	const auto t4 = t3 * t3;

	static const float c[7] = {
		+7.2128853633444123e-03f,
		-3.5059680836411644e-02f,
		+8.1675882859940430e-02f,
		-1.3374657325451267e-01f,
		+1.9856563505717162e-01f,
		-3.3324998579202170e-01f,
		+1.0f
	};

	t0 = c[0];
	t0 = t0 * t4 + c[1];
	t0 = t0 * t4 + c[2];
	t0 = t0 * t4 + c[3];
	t0 = t0 * t4 + c[4];
	t0 = t0 * t4 + c[5];
	t0 = t0 * t4 + c[6];
	t3 = t0 * t3;

	t3 = yAbsBigger ? (0.5f * PI) - t3 : t3;
	t3 = (X < 0.0f) ? PI - t3 : t3;
	t3 = (Y < 0.0f) ? -t3 : t3;

	return t3;
}

float FGenericPlatformMath::Fmod(float X, float Y) {
	if (fabsf(Y) <= 1.e-8f) {
		FmodReportError(X, Y);
		return 0.f;
	}
	const auto div = (X / Y);
	// All floats where abs(f) >= 2^23 (8388608) are whole numbers so do not need truncation, and avoid overflow in TruncToFloat as they get even larger.
	const auto quotient = fabsf(div) < 8388608.f ? TruncToFloat(div) : div;
	auto intPortion = Y * quotient;

	// Rounding and imprecision could cause IntPortion to exceed X and cause the result to be outside the expected range.
	// For example Fmod(55.8, 9.3) would result in a very small negative value!
	if (fabsf(intPortion) > fabsf(X)) {
		intPortion = X;
	}

	const auto result = X - intPortion;
	return result;
}

void FGenericPlatformMath::FmodReportError(float X, float Y) {
	if (Y == 0) {
		CoreLog::GetInstance().LogWarning(
				Types::FString(
						"FMath::FMod(X=" + std::to_string(X) + ", Y=" + std::to_string(Y) +
						") : Y is zero, this is invalid and would result in NaN!")
				);
	}
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop
