/**
 * Created by rayfalling on 2020/11/10.
 * */

#include "Math/FPlane.h"

using namespace Engine::Core::Math;

/* FPlane inline functions
 *****************************************************************************/

FORCEINLINE FPlane::FPlane() = default;

//
// FORCEINLINE FPlane::FPlane(const FVector4& V)
// 	: FVector3(V)
// 	  , W(V.W) {
// }


FORCEINLINE FPlane::FPlane(float InX, float InY, float InZ, float InW)
	: FVector3(InX, InY, InZ)
	  , W(InW) {
}


FORCEINLINE FPlane::FPlane(FVector3 InNormal, float InW)
	: FVector3(InNormal), W(InW) {
}


FORCEINLINE FPlane::FPlane(FVector3 InBase, const FVector3& InNormal)
	: FVector3(InNormal)
	  , W(InBase | InNormal) {
}


FORCEINLINE FPlane::FPlane(FVector3 A, FVector3 B, FVector3 C)
	: FVector3(((B - A) ^ (C - A)).GetSafeNormal()) {
	W = A | (FVector3)(*this);
}


FORCEINLINE float FPlane::PlaneDot(const FVector3& P) const {
	return X * P.X + Y * P.Y + Z * P.Z - W;
}

FORCEINLINE bool FPlane::Normalize(float Tolerance) {
	const float SquareSum = X * X + Y * Y + Z * Z;
	if (SquareSum > Tolerance) {
		const float Scale = FMath::InvSqrt(SquareSum);
		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;
		return true;
	}
	return false;
}

FORCEINLINE FPlane FPlane::Flip() const {
	return FPlane(-X, -Y, -Z, -W);
}

FORCEINLINE bool FPlane::operator==(const FPlane& V) const {
	return (X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W);
}


FORCEINLINE bool FPlane::operator!=(const FPlane& V) const {
	return (X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W);
}


FORCEINLINE bool FPlane::Equals(const FPlane& V, float Tolerance) const {
	return (FMath::Abs(X - V.X) < Tolerance) && (FMath::Abs(Y - V.Y) < Tolerance) && (FMath::Abs(Z - V.Z) < Tolerance) && (
		FMath::Abs(W - V.W) < Tolerance);
}


FORCEINLINE float FPlane::operator|(const FPlane& V) const {
	return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
}


FORCEINLINE FPlane FPlane::operator+(const FPlane& V) const {
	return FPlane(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}


FORCEINLINE FPlane FPlane::operator-(const FPlane& V) const {
	return FPlane(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}


FORCEINLINE FPlane FPlane::operator/(float Scale) const {
	const float RScale = 1.f / Scale;
	return FPlane(X * RScale, Y * RScale, Z * RScale, W * RScale);
}


FORCEINLINE FPlane FPlane::operator*(float Scale) const {
	return FPlane(X * Scale, Y * Scale, Z * Scale, W * Scale);
}


FORCEINLINE FPlane FPlane::operator*(const FPlane& V) {
	return FPlane(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
}


FORCEINLINE FPlane FPlane::operator+=(const FPlane& V) {
	X += V.X;
	Y += V.Y;
	Z += V.Z;
	W += V.W;
	return *this;
}


FORCEINLINE FPlane FPlane::operator-=(const FPlane& V) {
	X -= V.X;
	Y -= V.Y;
	Z -= V.Z;
	W -= V.W;
	return *this;
}


FORCEINLINE FPlane FPlane::operator*=(float Scale) {
	X *= Scale;
	Y *= Scale;
	Z *= Scale;
	W *= Scale;
	return *this;
}


FORCEINLINE FPlane FPlane::operator*=(const FPlane& V) {
	X *= V.X;
	Y *= V.Y;
	Z *= V.Z;
	W *= V.W;
	return *this;
}


FORCEINLINE FPlane FPlane::operator/=(float V) {
	const float RV = 1.f / V;
	X *= RV;
	Y *= RV;
	Z *= RV;
	W *= RV;
	return *this;
}
