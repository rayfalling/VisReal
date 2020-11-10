/**
 * Created by rayfalling on 2020/10/30.
 * */

#include "Math/FVector.h"

using namespace Engine::Core::Math;

const FVector3 FVector3::ZeroVector = FVector3(0, 0, 0);
const FVector3 FVector3::OneVector = FVector3(1, 1, 1);
const FVector3 FVector3::UpVector = FVector3(0, 0, 1);
const FVector3 FVector3::DownVector = FVector3(0, 0, -1);
const FVector3 FVector3::ForwardVector = FVector3(1, 0, 0);
const FVector3 FVector3::BackwardVector = FVector3(-1, 0, 0);
const FVector3 FVector3::RightVector = FVector3(0, 1, 0);
const FVector3 FVector3::LeftVector = FVector3(0, -1, 0);

FVector3::FVector3(const float value): X(value), Y(value), Z(value) {
	DiagnosticCheckNaN();
}

FVector3::FVector3(const float x, const float y, const float z): X(x), Y(y), Z(z) {
	DiagnosticCheckNaN();
}

void FVector3::CheckIndex(const int index) {
	if (index < 0 || index >= 3) {
		CoreLog::GetInstance().LogError(FString("Try to access unavailable index in FVector3."));
		PLATFORM_BREAK();
	}
}

FORCEINLINE FVector3 FVector3::operator^(const FVector3& vec) const {
	return FVector3(
			Y * vec.Z - Z * vec.Y,
			Z * vec.X - X * vec.Z,
			X * vec.Y - Y * vec.X
			);

}

FORCEINLINE FVector3 FVector3::CrossProduct(const FVector3& first, const FVector3& second) {
	return first ^ second;
}

FORCEINLINE float FVector3::operator|(const FVector3& vec) const {
	return X * vec.X + Y * vec.Y + Z * vec.Z;
}

FORCEINLINE float FVector3::DotProduct(const FVector3& first, const FVector3& second) {
	return first | second;
}

FORCEINLINE FVector3 FVector3::operator+(const FVector3& vec) const {
	return FVector3(X + vec.X, Y + vec.Y, Z + vec.Z);
}

FORCEINLINE FVector3 FVector3::operator-(const FVector3& vec) const {
	return FVector3(X - vec.X, Y - vec.Y, Z - vec.Z);
}

FORCEINLINE FVector3 FVector3::operator-(const float bias) const {
	return FVector3(X - bias, Y - bias, Z - bias);
}

FORCEINLINE FVector3 FVector3::operator+(const float bias) const {
	return FVector3(X + bias, Y + bias, Z + bias);
}

FORCEINLINE FVector3 FVector3::operator*(const float scale) const {
	return FVector3(X * scale, Y * scale, Z * scale);
}

FORCEINLINE FVector3 FVector3::operator/(const float scale) const {
	const auto rScale = 1.f / scale;
	return FVector3(X * rScale, Y * rScale, Z * rScale);
}

FORCEINLINE FVector3 FVector3::operator*(const FVector3& vec) const {
	return FVector3(X * vec.X, Y * vec.Y, Z * vec.Z);
}

FORCEINLINE FVector3 FVector3::operator/(const FVector3& vec) const {
	return FVector3(X / vec.X, Y / vec.Y, Z / vec.Z);
}

FORCEINLINE bool FVector3::operator==(const FVector3& vec) const {
	return X == vec.X && Y == vec.Y && Z == vec.Z; // NOLINT(clang-diagnostic-float-equal)
}

FORCEINLINE bool FVector3::operator!=(const FVector3& vec) const {
	return X != vec.X || Y != vec.Y || Z != vec.Z; // NOLINT(clang-diagnostic-float-equal)
}

FORCEINLINE bool FVector3::Equals(const FVector3& vec, const float tolerance) const {
	return Math::FMath::Abs(X - vec.X) <= tolerance && Math::FMath::Abs(Y - vec.Y) <= tolerance && Math::FMath::Abs(Z - vec.Z) <= tolerance;
}

FORCEINLINE bool FVector3::AllComponentsEqual(const float tolerance) const {
	return Math::FMath::Abs(X - Y) <= tolerance && Math::FMath::Abs(X - Z) <= tolerance && Math::FMath::Abs(Y - Z) <= tolerance;
}

FORCEINLINE FVector3 FVector3::operator-() const {
	return FVector3(-X, -Y, -Z);
}

FORCEINLINE FVector3 FVector3::operator+=(const FVector3& vec) {
	X += vec.X;
	Y += vec.Y;
	Z += vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE FVector3 FVector3::operator-=(const FVector3& vec) {
	X -= vec.X;
	Y -= vec.Y;
	Z -= vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE FVector3 FVector3::operator*=(const float scale) {
	X *= scale;
	Y *= scale;
	Z *= scale;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE FVector3 FVector3::operator/=(const float scale) {
	const auto rv = 1.f / scale;
	X *= rv;
	Y *= rv;
	Z *= rv;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE FVector3 FVector3::operator*=(const FVector3& vec) {
	X *= vec.X;
	Y *= vec.Y;
	Z *= vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE FVector3 FVector3::operator/=(const FVector3& vec) {
	X /= vec.X;
	Y /= vec.Y;
	Z /= vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE float& FVector3::operator[](const int32 index) {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE float FVector3::operator[](const int32 index) const {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE float& FVector3::Component(const int32 index) {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE float FVector3::Component(const int32 index) const {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE void FVector3::Set(const float x, const float y, const float z) {
	X = x;
	Y = y;
	Z = z;
	DiagnosticCheckNaN();
}

FORCEINLINE float FVector3::GetMax() const {
	return Math::FMath::Max(Math::FMath::Max(X, Y), Z);
}

FORCEINLINE float FVector3::GetAbsMax() const {
	return Math::FMath::Max(Math::FMath::Max(Math::FMath::Abs(X), Math::FMath::Abs(Y)), Math::FMath::Abs(Z));
}

FORCEINLINE float FVector3::GetMin() const {
	return Math::FMath::Min(Math::FMath::Min(X, Y), Z);
}

FORCEINLINE float FVector3::GetAbsMin() const {
	return Math::FMath::Min(Math::FMath::Min(Math::FMath::Abs(X), Math::FMath::Abs(Y)), Math::FMath::Abs(Z));
}

FORCEINLINE FVector3 FVector3::ComponentMin(const FVector3& other) const {
	return FVector3(Math::FMath::Min(X, other.X), Math::FMath::Min(Y, other.Y), Math::FMath::Min(Z, other.Z));
}

FORCEINLINE FVector3 FVector3::ComponentMax(const FVector3& other) const {
	return FVector3(Math::FMath::Min(X, other.X), Math::FMath::Min(Y, other.Y), Math::FMath::Min(Z, other.Z));
}

FORCEINLINE FVector3 FVector3::GetAbs() const {
	return FVector3(Math::FMath::Abs(X), Math::FMath::Abs(Y), Math::FMath::Abs(Z));
}

FORCEINLINE float FVector3::Size() const {
	return Math::FMath::Sqrt(X * X + Y * Y + Z * Z);
}

FORCEINLINE float FVector3::SizeSquared() const {
	return X * X + Y * Y + Z * Z;
}

FORCEINLINE float FVector3::Size2D() const {
	return Math::FMath::Sqrt(X * X + Y * Y);
}

FORCEINLINE float FVector3::SizeSquared2D() const {
	return X * X + Y * Y;
}

FORCEINLINE bool FVector3::IsNearlyZero(const float tolerance) const {
	return Math::FMath::Abs(X) <= tolerance
			&& Math::FMath::Abs(Y) <= tolerance
			&& Math::FMath::Abs(Z) <= tolerance;
}

FORCEINLINE bool FVector3::IsZero() const {
	return X == 0.f && Y == 0.f && Z == 0.f;
}

FORCEINLINE bool FVector3::IsUnit(const float lengthSquaredTolerance) const {
	return Math::FMath::Abs(1.0f - SizeSquared()) < lengthSquaredTolerance;
}

FORCEINLINE bool FVector3::IsNormalized() const {
	return (Math::FMath::Abs(1.f - SizeSquared()) < THRESH_VECTOR_NORMALIZED);
}

FORCEINLINE bool FVector3::Normalize(const float tolerance) {
	const auto squareSum = X * X + Y * Y + Z * Z;
	if (squareSum > tolerance) {
		const auto scale = Math::FMath::InvSqrt(squareSum);
		X *= scale;
		Y *= scale;
		Z *= scale;
		return true;
	}
	return false;
}

FORCEINLINE FVector3 FVector3::GetUnsafeNormal() const {
	const auto scale = Math::FMath::InvSqrt(X * X + Y * Y + Z * Z);
	return FVector3(X * scale, Y * scale, Z * scale);
}

FORCEINLINE FVector3 FVector3::GetSafeNormal(const float tolerance) const {
	const auto squareSum = X * X + Y * Y + Z * Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (squareSum == 1.f) {
		return *this;
	}
	if (squareSum < tolerance) {
		return ZeroVector;
	}
	const auto scale = Math::FMath::InvSqrt(squareSum);
	return FVector3(X * scale, Y * scale, Z * scale);
}

FORCEINLINE FVector3 FVector3::GetSafeNormal2D(const float tolerance) const {
	const auto squareSum = X * X + Y * Y;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (squareSum == 1.f) {
		if (Z == 0.f) {
			return *this;
		}
		return FVector3(X, Y, 0.f);
	}
	if (squareSum < tolerance) {
		return ZeroVector;
	}

	const auto scale = Math::FMath::InvSqrt(squareSum);
	return FVector3(X * scale, Y * scale, 0.f);
}

FORCEINLINE bool FVector3::ContainsNaN() const {
	return (!Math::FMath::IsFinite(X) || !Math::FMath::IsFinite(Y) || !Math::FMath::IsFinite(Z));
}

FORCEINLINE FString FVector3::ToString() const {
	return FString::Format("X=%3.3f Y=%3.3f Z=%3.3f", X, Y, Z);
}
