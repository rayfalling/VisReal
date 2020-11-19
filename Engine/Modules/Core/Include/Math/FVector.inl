/**
 * Created by rayfalling on 2020/11/19.
 *
 * Custom Array class, like std::vector
 * */

// ReSharper disable CppClangTidyMiscRedundantExpression
#pragma once

#include "Math/FVector.h"
#include "Math/VisRealMathUtility.h"

FORCEINLINE Engine::Core::Math::FVector3::FVector3(const float value) : X(value), Y(value), Z(value) {
	DiagnosticCheckNaN();
}

FORCEINLINE Engine::Core::Math::FVector3::FVector3(const float x, const float y, const float z) : X(x), Y(y), Z(z) {
	DiagnosticCheckNaN();
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator^(const FVector3& vec) const {
	return FVector3(
			Y * vec.Z - Z * vec.Y,
			Z * vec.X - X * vec.Z,
			X * vec.Y - Y * vec.X
			);

}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::CrossProduct(const FVector3& first, const FVector3& second) {
	return first ^ second;
}

FORCEINLINE float Engine::Core::Math::FVector3::operator|(const FVector3& vec) const {
	return X * vec.X + Y * vec.Y + Z * vec.Z;
}

FORCEINLINE float Engine::Core::Math::FVector3::DotProduct(const FVector3& first, const FVector3& second) {
	return first | second;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator+(const FVector3& vec) const {
	return FVector3(X + vec.X, Y + vec.Y, Z + vec.Z);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator-(const FVector3& vec) const {
	return FVector3(X - vec.X, Y - vec.Y, Z - vec.Z);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator-(const float bias) const {
	return FVector3(X - bias, Y - bias, Z - bias);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator+(const float bias) const {
	return FVector3(X + bias, Y + bias, Z + bias);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator*(const float scale) const {
	return FVector3(X * scale, Y * scale, Z * scale);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator/(const float scale) const {
	const auto rScale = 1.f / scale;
	return FVector3(X * rScale, Y * rScale, Z * rScale);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator*(const FVector3& vec) const {
	return FVector3(X * vec.X, Y * vec.Y, Z * vec.Z);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator/(const FVector3& vec) const {
	return FVector3(X / vec.X, Y / vec.Y, Z / vec.Z);
}

FORCEINLINE bool Engine::Core::Math::FVector3::operator==(const FVector3& vec) const {
	return X == vec.X && Y == vec.Y && Z == vec.Z; // NOLINT(clang-diagnostic-float-equal)
}

FORCEINLINE bool Engine::Core::Math::FVector3::operator!=(const FVector3& vec) const {
	return X != vec.X || Y != vec.Y || Z != vec.Z; // NOLINT(clang-diagnostic-float-equal)
}

FORCEINLINE bool Engine::Core::Math::FVector3::Equals(const FVector3& vec, const float tolerance) const {
	return FMath::Abs(X - vec.X) <= tolerance && FMath::Abs(Y - vec.Y) <= tolerance && FMath::Abs(Z - vec.Z) <= tolerance;
}

FORCEINLINE bool Engine::Core::Math::FVector3::AllComponentsEqual(const float tolerance) const {
	return FMath::Abs(X - Y) <= tolerance && FMath::Abs(X - Z) <= tolerance && FMath::Abs(Y - Z) <= tolerance;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator-() const {
	return FVector3(-X, -Y, -Z);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator+=(const FVector3& vec) {
	X += vec.X;
	Y += vec.Y;
	Z += vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator-=(const FVector3& vec) {
	X -= vec.X;
	Y -= vec.Y;
	Z -= vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator*=(const float scale) {
	X *= scale;
	Y *= scale;
	Z *= scale;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator/=(const float scale) {
	const auto rv = 1.f / scale;
	X *= rv;
	Y *= rv;
	Z *= rv;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator*=(const FVector3& vec) {
	X *= vec.X;
	Y *= vec.Y;
	Z *= vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::operator/=(const FVector3& vec) {
	X /= vec.X;
	Y /= vec.Y;
	Z /= vec.Z;
	DiagnosticCheckNaN();
	return *this;
}

FORCEINLINE float& Engine::Core::Math::FVector3::operator[](const int32 index) {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE float Engine::Core::Math::FVector3::operator[](const int32 index) const {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE float& Engine::Core::Math::FVector3::Component(const int32 index) {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE float Engine::Core::Math::FVector3::Component(const int32 index) const {
	CheckIndex(index);
	return (&X)[index];
}

FORCEINLINE void Engine::Core::Math::FVector3::Set(const float x, const float y, const float z) {
	X = x;
	Y = y;
	Z = z;
	DiagnosticCheckNaN();
}

FORCEINLINE float Engine::Core::Math::FVector3::GetMax() const {
	return FMath::Max(FMath::Max(X, Y), Z);
}

FORCEINLINE float Engine::Core::Math::FVector3::GetAbsMax() const {
	return FMath::Max(FMath::Max(FMath::Abs(X), FMath::Abs(Y)), FMath::Abs(Z));
}

FORCEINLINE float Engine::Core::Math::FVector3::GetMin() const {
	return FMath::Min(FMath::Min(X, Y), Z);
}

FORCEINLINE float Engine::Core::Math::FVector3::GetAbsMin() const {
	return FMath::Min(FMath::Min(FMath::Abs(X), FMath::Abs(Y)), FMath::Abs(Z));
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::ComponentMin(const FVector3& other) const {
	return FVector3(FMath::Min(X, other.X), FMath::Min(Y, other.Y), FMath::Min(Z, other.Z));
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::ComponentMax(const FVector3& other) const {
	return FVector3(FMath::Min(X, other.X), FMath::Min(Y, other.Y), FMath::Min(Z, other.Z));
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetAbs() const {
	return FVector3(FMath::Abs(X), FMath::Abs(Y), FMath::Abs(Z));
}

FORCEINLINE float Engine::Core::Math::FVector3::Size() const {
	return FMath::Sqrt(X * X + Y * Y + Z * Z);
}

FORCEINLINE float Engine::Core::Math::FVector3::SizeSquared() const {
	return X * X + Y * Y + Z * Z;
}

FORCEINLINE float Engine::Core::Math::FVector3::Size2D() const {
	return FMath::Sqrt(X * X + Y * Y);
}

FORCEINLINE float Engine::Core::Math::FVector3::SizeSquared2D() const {
	return X * X + Y * Y;
}

FORCEINLINE bool Engine::Core::Math::FVector3::IsNearlyZero(const float tolerance) const {
	return FMath::Abs(X) <= tolerance
			&& FMath::Abs(Y) <= tolerance
			&& FMath::Abs(Z) <= tolerance;
}

FORCEINLINE bool Engine::Core::Math::FVector3::IsZero() const {
	return X == 0.f && Y == 0.f && Z == 0.f;
}

FORCEINLINE bool Engine::Core::Math::FVector3::IsUnit(const float lengthSquaredTolerance) const {
	return FMath::Abs(1.0f - SizeSquared()) < lengthSquaredTolerance;
}

FORCEINLINE bool Engine::Core::Math::FVector3::IsNormalized() const {
	return (FMath::Abs(1.f - SizeSquared()) < THRESH_VECTOR_NORMALIZED);
}

FORCEINLINE bool Engine::Core::Math::FVector3::Normalize(const float tolerance) {
	const auto squareSum = X * X + Y * Y + Z * Z;
	if (squareSum > tolerance) {
		const auto scale = FMath::InvSqrt(squareSum);
		X *= scale;
		Y *= scale;
		Z *= scale;
		return true;
	}
	return false;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetUnsafeNormal() const {
	const auto scale = FMath::InvSqrt(X * X + Y * Y + Z * Z);
	return FVector3(X * scale, Y * scale, Z * scale);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetSafeNormal(const float tolerance) const {
	const auto squareSum = X * X + Y * Y + Z * Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (squareSum == 1.f) {
		return *this;
	}
	if (squareSum < tolerance) {
		return ZeroVector;
	}
	const auto scale = FMath::InvSqrt(squareSum);
	return FVector3(X * scale, Y * scale, Z * scale);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetSafeNormal2D(const float tolerance) const {
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

	const auto scale = FMath::InvSqrt(squareSum);
	return FVector3(X * scale, Y * scale, 0.f);
}

FORCEINLINE void Engine::Core::Math::FVector3::ToDirectionAndLength(FVector3& outDir, float& outLength) const {
	outLength = Size();
	if (outLength > SMALL_NUMBER) {
		const auto oneOverLength = 1.0f / outLength;
		outDir = FVector3(X * oneOverLength, Y * oneOverLength, Z * oneOverLength);
	} else {
		outDir = ZeroVector;
	}
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetSignVector() const {
	return FVector3(
			FMath::FloatSelect(X, 1.f, -1.f),
			FMath::FloatSelect(Y, 1.f, -1.f),
			FMath::FloatSelect(Z, 1.f, -1.f)
			);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::Projection() const {
	const auto rz = 1.f / Z;
	return FVector3(X * rz, Y * rz, 1);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetUnsafeNormal2D() const {
	const auto scale = FMath::InvSqrt(X * X + Y * Y);
	return FVector3(X * scale, Y * scale, 0);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GridSnap(const float& gridSize) const {
	return FVector3(FMath::GridSnap(X, gridSize), FMath::GridSnap(Y, gridSize), FMath::GridSnap(Z, gridSize));
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::BoundToCube(const float radius) const {
	return FVector3(
			FMath::Clamp(X, -radius, radius),
			FMath::Clamp(Y, -radius, radius),
			FMath::Clamp(Z, -radius, radius)
			);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::BoundToBox(const FVector3& min, const FVector3& max) const {
	return FVector3(
			FMath::Clamp(X, min.X, max.X),
			FMath::Clamp(Y, min.Y, max.Y),
			FMath::Clamp(Z, min.Z, max.Z)
			);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetClampedToSize(const float min, const float max) const {
	auto vecSize = Size();
	const auto vecDir = (vecSize > SMALL_NUMBER) ? (*this / vecSize) : ZeroVector;
	vecSize = FMath::Clamp(vecSize, min, max);
	return vecSize * vecDir;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetClampedToSize2D(const float min, const float max) const {
	auto vecSize2D = Size2D();
	const auto vecDir = (vecSize2D > SMALL_NUMBER) ? (*this / vecSize2D) : ZeroVector;
	vecSize2D = FMath::Clamp(vecSize2D, min, max);
	return FVector3(vecSize2D * vecDir.X, vecSize2D * vecDir.Y, Z);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetClampedToMaxSize(const float maxSize) const {
	if (maxSize < KINDA_SMALL_NUMBER) {
		return ZeroVector;
	}

	const auto vSq = SizeSquared();
	if (vSq > FMath::Square(maxSize)) {
		const auto scale = maxSize * FMath::InvSqrt(vSq);
		return FVector3(X * scale, Y * scale, Z * scale);
	}
	return *this;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::GetClampedToMaxSize2D(const float maxSize) const {
	if (maxSize < KINDA_SMALL_NUMBER) {
		return FVector3(0.f, 0.f, Z);
	}

	const auto vSq2D = SizeSquared2D();
	if (vSq2D > FMath::Square(maxSize)) {
		const auto scale = maxSize * FMath::InvSqrt(vSq2D);
		return FVector3(X * scale, Y * scale, Z);
	}
	return *this;
}

FORCEINLINE void Engine::Core::Math::FVector3::AddBounded(const FVector3& v, const float radius) {
	*this = (*this + v).BoundToCube(radius);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::Reciprocal() const {
	FVector3 recVector;
	if (X != 0.f) {
		recVector.X = 1.f / X;
	} else {
		recVector.X = BIG_NUMBER;
	}
	if (Y != 0.f) {
		recVector.Y = 1.f / Y;
	} else {
		recVector.Y = BIG_NUMBER;
	}
	if (Z != 0.f) {
		recVector.Z = 1.f / Z;
	} else {
		recVector.Z = BIG_NUMBER;
	}

	return recVector;
}

FORCEINLINE bool Engine::Core::Math::FVector3::IsUniform(const float tolerance) const {
	return AllComponentsEqual(tolerance);
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::RotateAngleAxis(const float angleDeg, const FVector3& axis) const {
	float sin, cos;
	FMath::SinCos(&sin, &cos, FMath::DegreesToRadians(angleDeg));

	const auto xx = axis.X * axis.X;
	const auto yy = axis.Y * axis.Y;
	const auto zz = axis.Z * axis.Z;

	const auto xy = axis.X * axis.Y;
	const auto yz = axis.Y * axis.Z;
	const auto zx = axis.Z * axis.X;

	const auto xs = axis.X * sin;
	const auto ys = axis.Y * sin;
	const auto zs = axis.Z * sin;

	const auto omc = 1.f - cos;

	return FVector3(
			(omc * xx + cos) * X + (omc * xy - zs) * Y + (omc * zx + ys) * Z,
			(omc * xy + zs) * X + (omc * yy + cos) * Y + (omc * yz - xs) * Z,
			(omc * zx - ys) * X + (omc * yz + xs) * Y + (omc * zz + cos) * Z
			);
}

FORCEINLINE float Engine::Core::Math::FVector3::CosineAngle2D(FVector3 b) const {
	auto a(*this);
	a.Z = 0.0f;
	b.Z = 0.0f;
	a.Normalize();
	b.Normalize();
	return a | b;
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::ProjectOnTo(const FVector3& a) const {
	return (a * ((*this | a) / (a | a)));
}

FORCEINLINE Engine::Core::Math::FVector3 Engine::Core::Math::FVector3::ProjectOnToNormal(const FVector3& normal) const {
	return (normal * (*this | normal));
}

FORCEINLINE bool Engine::Core::Math::FVector3::ContainsNaN() const {
	return (!FMath::IsFinite(X) || !FMath::IsFinite(Y) || !FMath::IsFinite(Z));
}

FORCEINLINE Engine::Core::FString Engine::Core::Math::FVector3::ToString() const {
	return FString::Format("X={:.3f} Y={:.3f} Z={:.3f}", X, Y, Z);
}
