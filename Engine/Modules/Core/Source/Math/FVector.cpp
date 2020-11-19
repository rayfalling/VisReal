/**
 * Created by rayfalling on 2020/10/30.
 * */

#include "Math/FVector.h"

#include "Math/FPlane.h"

using namespace Engine::Core::Math;

const FVector3 FVector3::ZeroVector = FVector3(0, 0, 0);
const FVector3 FVector3::OneVector = FVector3(1, 1, 1);
const FVector3 FVector3::UpVector = FVector3(0, 0, 1);
const FVector3 FVector3::DownVector = FVector3(0, 0, -1);
const FVector3 FVector3::ForwardVector = FVector3(1, 0, 0);
const FVector3 FVector3::BackwardVector = FVector3(-1, 0, 0);
const FVector3 FVector3::RightVector = FVector3(0, 1, 0);
const FVector3 FVector3::LeftVector = FVector3(0, -1, 0);

void FVector3::CheckIndex(const int index) {
	if (index < 0 || index >= 3) {
		CoreLog::GetInstance().LogError(FString("Try to access unavailable index in FVector3."));
		PLATFORM_BREAK();
	}
}

FVector3 FVector3::MirrorByVector(const FVector3& mirrorNormal) const {
	return *this - mirrorNormal * (2.f * (*this | mirrorNormal));
}

FVector3 FVector3::MirrorByPlane(const Math::FPlane& plane) const {
	return *this - plane * (2.f * plane.PlaneDot(*this));
}

void FVector3::FindBestAxisVectors(FVector3& axis1, FVector3& axis2) const {
	const auto nx = FMath::Abs(X);
	const auto ny = FMath::Abs(Y);
	const auto nz = FMath::Abs(Z);

	// Find best basis vectors.
	if (nz > nx && nz > ny) axis1 = FVector3(1, 0, 0);
	else axis1 = FVector3(0, 0, 1);

	axis1 = (axis1 - *this * (axis1 | *this)).GetSafeNormal();
	axis2 = axis1 ^ *this;
}

void FVector3::UnwindEuler() {
	X = FMath::UnwindDegrees(X);
	Y = FMath::UnwindDegrees(Y);
	Z = FMath::UnwindDegrees(Z);
}

inline FVector3 FMath::VRand() {
	FVector3 result;
	auto l = 0.f;

	do {
		// Check random vectors in the unit sphere so result is statistically uniform.
		result.X = FRand() * 2.f - 1.f;
		result.Y = FRand() * 2.f - 1.f;
		result.Z = FRand() * 2.f - 1.f;
		l = result.SizeSquared();
	} while (l > 1.0f || l < KINDA_SMALL_NUMBER);

	return result * (1.0f / Sqrt(l));
}

void FVector3::CreateOrthonormalBasis(FVector3& xAxis, FVector3& yAxis, FVector3& zAxis) {
	// Project the X and Y axes onto the plane perpendicular to the Z axis.
	xAxis -= (xAxis | zAxis) / (zAxis | zAxis) * zAxis;
	yAxis -= (yAxis | zAxis) / (zAxis | zAxis) * zAxis;

	// If the X axis was parallel to the Z axis, choose a vector which is orthogonal to the Y and Z axes.
	if (xAxis.SizeSquared() < DELTA * DELTA) {
		xAxis = yAxis ^ zAxis;
	}

	// If the Y axis was parallel to the Z axis, choose a vector which is orthogonal to the X and Z axes.
	if (yAxis.SizeSquared() < DELTA * DELTA) {
		yAxis = xAxis ^ zAxis;
	}

	// Normalize the basis vectors.
	xAxis.Normalize();
	yAxis.Normalize();
	zAxis.Normalize();
}

float Engine::Core::Math::ComputeSquaredDistanceFromBoxToPoint(const FVector3& min, const FVector3& max, const FVector3& point) {
	// Accumulates the distance as we iterate axis
	auto distSquared = 0.f;

	// Check each axis for min/max and add the distance accordingly
	// NOTE: Loop manually unrolled for > 2x speed up
	if (point.X < min.X) {
		distSquared += FMath::Square(point.X - min.X);
	} else if (point.X > max.X) {
		distSquared += FMath::Square(point.X - max.X);
	}

	if (point.Y < min.Y) {
		distSquared += FMath::Square(point.Y - min.Y);
	} else if (point.Y > max.Y) {
		distSquared += FMath::Square(point.Y - max.Y);
	}

	if (point.Z < min.Z) {
		distSquared += FMath::Square(point.Z - min.Z);
	} else if (point.Z > max.Z) {
		distSquared += FMath::Square(point.Z - max.Z);
	}

	return distSquared;
}
