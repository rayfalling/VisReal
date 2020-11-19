/**
 * Created by rayfalling on 2020/11/9.
 * */

// ReSharper disable CppHidingFunction
#pragma once

#ifndef VISREAL_F_PLANE_H
#define VISREAL_F_PLANE_H

#include "FVector.h"
#include "Marco/PlatformMarcos.h"

// ReSharper disable CppClangTidyClangDiagnosticFloatEqual
namespace Engine::Core::Math {
	class FMatrix;

	/**
	 * Structure for three dimensional planes.
	 *
	 * Stores the coeffecients as Xx+Yy+Zz=W.
	 * Note that this is different from many other Plane classes that use Xx+Yy+Zz+W=0.
	 */
	MS_ALIGN(16) class FPlane final : public FVector3 {
		public:
			/** The w-component. */
			float W;

		public:
			/** Default constructor (no initialization). */
			FORCEINLINE FPlane();

			/**
			 * Constructor.
			 *
			 * @param v 4D vector to set up plane.
			 */
			FORCEINLINE FPlane(const FVector4& v);

			/**
			 * Constructor.
			 *
			 * @param inX X-coefficient.
			 * @param inY Y-coefficient.
			 * @param inZ Z-coefficient.
			 * @param inW W-coefficient.
			 */
			FORCEINLINE FPlane(float inX, float inY, float inZ, float inW);

			/**
			 * Constructor.
			 *
			 * @param inNormal Plane Normal Vector.
			 * @param inW Plane W-coefficient.
			 */
			FORCEINLINE FPlane(const FVector3& inNormal, float inW);

			/**
			 * Constructor.
			 *
			 * @param inBase Base point in plane.
			 * @param inNormal Plane Normal Vector.
			 */
			FORCEINLINE FPlane(const FVector3& inBase, const FVector3& inNormal);

			/**
			 * Constructor.
			 *
			 * @param a First point in the plane.
			 * @param b Second point in the plane.
			 * @param c Third point in the plane.
			 */
			FPlane(const FVector3& a, const FVector3& b, const FVector3& c);

			// Functions.

			/**
			 * Calculates distance between plane and a point.
			 *
			 * @param p The other point.
			 * @return The distance from the plane to the point. 0: Point is on the plane. >0: Point is in front of the plane. <0: Point is behind the plane.
			 */
			FORCEINLINE float PlaneDot(const FVector3& p) const;

			/**
			 * Normalize this plane in-place if it is larger than a given tolerance. Leaves it unchanged if not.
			 *
			 * @param tolerance Minimum squared length of vector for normalization.
			 * @return true if the plane was normalized correctly, false otherwise.
			 */
			bool Normalize(float tolerance = SMALL_NUMBER);

			/**
			 * Get a flipped version of the plane.
			 *
			 * @return A flipped version of the plane.
			 */
			[[nodiscard]] FPlane Flip() const;

			/**
			 * Get the result of transforming the plane by a Matrix.
			 *
			 * @param m The matrix to transform plane with.
			 * @return The result of transform.
			 */
			[[nodiscard]] FPlane TransformBy(const FMatrix& m) const;

			/**
			 * You can optionally pass in the matrices transpose-adjoint, which save it recalculating it.
			 * MSM: If we are going to save the transpose-adjoint we should also save the more expensive
			 * determinant.
			 *
			 * @param m The Matrix to transform plane with.
			 * @param detM Determinant of Matrix.
			 * @param ta Transpose-adjoint of Matrix.
			 * @return The result of transform.
			 */
			[[nodiscard]] FPlane TransformByUsingAdjointT(const FMatrix& m, float detM, const FMatrix& ta) const;

			/**
			 * Check if two planes are identical.
			 *
			 * @param value The other plane.
			 * @return true if planes are identical, otherwise false.
			 */
			bool operator==(const FPlane& value) const;

			/**
			 * Check if two planes are different.
			 *
			 * @param value The other plane.
			 * @return true if planes are different, otherwise false.
			 */
			bool operator!=(const FPlane& value) const;

			/**
			 * Checks whether two planes are equal within specified tolerance.
			 *
			 * @param v The other plane.
			 * @param tolerance Error Tolerance.
			 * @return true if the two planes are equal within specified tolerance, otherwise false.
			 */
			[[nodiscard]] bool Equals(const FPlane& v, float tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Calculates dot product of two planes.
			 *
			 * @param value The other plane.
			 * @return The dot product.
			 */
			FORCEINLINE float operator|(const FPlane& value) const;

			/**
			 * Gets result of adding a plane to this.
			 *
			 * @param value The other plane.
			 * @return The result of adding a plane to this.
			 */
			FPlane operator+(const FPlane& value) const;

			/**
			 * Gets result of subtracting a plane from this.
			 *
			 * @param value The other plane.
			 * @return The result of subtracting a plane from this.
			 */
			FPlane operator-(const FPlane& value) const;

			/**
			 * Gets result of dividing a plane.
			 *
			 * @param scale What to divide by.
			 * @return The result of division.
			 */
			FPlane operator/(float scale) const;

			/**
			 * Gets result of scaling a plane.
			 *
			 * @param scale The scaling factor.
			 * @return The result of scaling.
			 */
			FPlane operator*(float scale) const;

			/**
			 * Gets result of multiplying a plane with this.
			 *
			 * @param value The other plane.
			 * @return The result of multiplying a plane with this.
			 */
			FPlane operator*(const FPlane& value) const;

			/**
			 * Add another plane to this.
			 *
			 * @param value The other plane.
			 * @return Copy of plane after addition.
			 */
			FPlane operator+=(const FPlane& value);

			/**
			 * Subtract another plane from this.
			 *
			 * @param value The other plane.
			 * @return Copy of plane after subtraction.
			 */
			FPlane operator-=(const FPlane& value);

			/**
			 * Scale this plane.
			 *
			 * @param scale The scaling factor.
			 * @return Copy of plane after scaling.
			 */
			FPlane operator*=(float scale);

			/**
			 * Multiply another plane with this.
			 *
			 * @param value The other plane.
			 * @return Copy of plane after multiplication.
			 */
			FPlane operator*=(const FPlane& value);

			/**
			 * Divide this plane.
			 *
			 * @param value What to divide by.
			 * @return Copy of plane after division.
			 */
			FPlane operator/=(float value);
	} GCC_ALIGN(16);

	FORCEINLINE FPlane::FPlane()
		: FVector3(), W(0.f) {
	};

	// FORCEINLINE FPlane::FPlane(const FVector4& v)
	// 	: FVector3(v), W(v.W) {
	// }

	FORCEINLINE FPlane::FPlane(const float inX, const float inY, const float inZ, const float inW)
		: FVector3(inX, inY, inZ), W(inW) {
	}

	FORCEINLINE FPlane::FPlane(const FVector3& inNormal, const float inW)
		: FVector3(inNormal), W(inW) {
	}

	FORCEINLINE FPlane::FPlane(const FVector3& inBase, const FVector3& inNormal)
		: FVector3(inNormal), W(inBase | inNormal) {
	}

	FORCEINLINE FPlane::FPlane(const FVector3& a, const FVector3& b, const FVector3& c)
		: FVector3(((b - a) ^ (c - a)).GetSafeNormal()) {
		W = a | static_cast<FVector3>(*this); //
	}

	FORCEINLINE float FPlane::PlaneDot(const FVector3& p) const {
		return X * p.X + Y * p.Y + Z * p.Z - W;
	}

	FORCEINLINE bool FPlane::Normalize(const float tolerance) {
		const auto squareSum = X * X + Y * Y + Z * Z;
		if (squareSum > tolerance) {
			const auto scale = FMath::InvSqrt(squareSum);
			X *= scale;
			Y *= scale;
			Z *= scale;
			W *= scale;
			return true;
		}
		return false;
	}

	FORCEINLINE FPlane FPlane::Flip() const {
		return FPlane(-X, -Y, -Z, -W);
	}

	FORCEINLINE bool FPlane::operator==(const FPlane& value) const {
		return (X == value.X) && (Y == value.Y) && (Z == value.Z) && (W == value.W);
	}

	FORCEINLINE bool FPlane::operator!=(const FPlane& value) const {
		return (X != value.X) || (Y != value.Y) || (Z != value.Z) || (W != value.W);
	}

	FORCEINLINE bool FPlane::Equals(const FPlane& v, const float tolerance) const {
		return (FMath::Abs(X - v.X) < tolerance)
				&& (FMath::Abs(Y - v.Y) < tolerance)
				&& (FMath::Abs(Z - v.Z) < tolerance)
				&& (FMath::Abs(W - v.W) < tolerance);
	}

	FORCEINLINE float FPlane::operator|(const FPlane& value) const {
		return X * value.X + Y * value.Y + Z * value.Z + W * value.W;
	}

	FORCEINLINE FPlane FPlane::operator+(const FPlane& value) const {
		return FPlane(X + value.X, Y + value.Y, Z + value.Z, W + value.W);
	}

	FORCEINLINE FPlane FPlane::operator-(const FPlane& value) const {
		return FPlane(X - value.X, Y - value.Y, Z - value.Z, W - value.W);
	}

	FORCEINLINE FPlane FPlane::operator/(const float scale) const {
		const auto rScale = 1.f / scale;
		return FPlane(X * rScale, Y * rScale, Z * rScale, W * rScale);
	}

	FORCEINLINE FPlane FPlane::operator*(const float scale) const {
		return FPlane(X * scale, Y * scale, Z * scale, W * scale);
	}

	FORCEINLINE FPlane FPlane::operator*(const FPlane& value) const {
		return FPlane(X * value.X, Y * value.Y, Z * value.Z, W * value.W);
	}

	FORCEINLINE FPlane FPlane::operator+=(const FPlane& value) {
		X += value.X;
		Y += value.Y;
		Z += value.Z;
		W += value.W;
		return *this;
	}

	FORCEINLINE FPlane FPlane::operator-=(const FPlane& value) {
		X -= value.X;
		Y -= value.Y;
		Z -= value.Z;
		W -= value.W;
		return *this;
	}

	FORCEINLINE FPlane FPlane::operator*=(const float scale) {
		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
		return *this;
	}

	FORCEINLINE FPlane FPlane::operator*=(const FPlane& value) {
		X *= value.X;
		Y *= value.Y;
		Z *= value.Z;
		W *= value.W;
		return *this;
	}

	FORCEINLINE FPlane FPlane::operator/=(const float value) {
		const auto rv = 1.f / value;
		X *= rv;
		Y *= rv;
		Z *= rv;
		W *= rv;
		return *this;
	}
}

#endif //VISREAL_F_PLANE_H
