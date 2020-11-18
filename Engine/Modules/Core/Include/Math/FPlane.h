/**
 * Created by rayfalling on 2020/11/9.
 * */

#pragma once

#ifndef VISREAL_F_PLANE_H
#define VISREAL_F_PLANE_H

#include "FVector.h"
#include "Marco/PlatformMarcos.h"

namespace Engine::Core::Math {
	class FMatrix;
	
	/**
	 * Structure for three dimensional planes.
	 *
	 * Stores the coeffecients as Xx+Yy+Zz=W.
	 * Note that this is different from many other Plane classes that use Xx+Yy+Zz+W=0.
	 */
	MS_ALIGN(16) class FPlane : public FVector3 {
		public:

			/** The w-component. */
			float W;

		public:

			/** Default constructor (no initialization). */
			FORCEINLINE FPlane();

			/**
			 * Constructor.
			 *
			 * @param V 4D vector to set up plane.
			 */
			// FORCEINLINE FPlane(const FVector4& V);

			/**
			 * Constructor.
			 *
			 * @param InX X-coefficient.
			 * @param InY Y-coefficient.
			 * @param InZ Z-coefficient.
			 * @param InW W-coefficient.
			 */
			FORCEINLINE FPlane(float InX, float InY, float InZ, float InW);

			/**
			 * Constructor.
			 *
			 * @param InNormal Plane Normal Vector.
			 * @param InW Plane W-coefficient.
			 */
			FORCEINLINE FPlane(FVector3 InNormal, float InW);

			/**
			 * Constructor.
			 *
			 * @param InBase Base point in plane.
			 * @param InNormal Plane Normal Vector.
			 */
			FORCEINLINE FPlane(FVector3 InBase, const FVector3& InNormal);

			/**
			 * Constructor.
			 *
			 * @param A First point in the plane.
			 * @param B Second point in the plane.
			 * @param C Third point in the plane.
			 */
			FPlane(FVector3 A, FVector3 B, FVector3 C);

			// Functions.

			/**
			 * Calculates distance between plane and a point.
			 *
			 * @param P The other point.
			 * @return The distance from the plane to the point. 0: Point is on the plane. >0: Point is in front of the plane. <0: Point is behind the plane.
			 */
			FORCEINLINE float PlaneDot(const FVector3& P) const;

			/**
			 * Normalize this plane in-place if it is larger than a given tolerance. Leaves it unchanged if not.
			 *
			 * @param Tolerance Minimum squared length of vector for normalization.
			 * @return true if the plane was normalized correctly, false otherwise.
			 */
			bool Normalize(float Tolerance = SMALL_NUMBER);

			/**
			 * Get a flipped version of the plane.
			 *
			 * @return A flipped version of the plane.
			 */
			[[nodiscard]] FPlane Flip() const;

			/**
			 * Get the result of transforming the plane by a Matrix.
			 *
			 * @param M The matrix to transform plane with.
			 * @return The result of transform.
			 */
			[[nodiscard]] FPlane TransformBy(const FMatrix& M) const;

			/**
			 * You can optionally pass in the matrices transpose-adjoint, which save it recalculating it.
			 * MSM: If we are going to save the transpose-adjoint we should also save the more expensive
			 * determinant.
			 *
			 * @param M The Matrix to transform plane with.
			 * @param DetM Determinant of Matrix.
			 * @param TA Transpose-adjoint of Matrix.
			 * @return The result of transform.
			 */
			[[nodiscard]] FPlane TransformByUsingAdjointT(const FMatrix& M, float DetM, const FMatrix& TA) const;

			/**
			 * Check if two planes are identical.
			 *
			 * @param V The other plane.
			 * @return true if planes are identical, otherwise false.
			 */
			bool operator==(const FPlane& V) const;

			/**
			 * Check if two planes are different.
			 *
			 * @param V The other plane.
			 * @return true if planes are different, otherwise false.
			 */
			bool operator!=(const FPlane& V) const;

			/**
			 * Checks whether two planes are equal within specified tolerance.
			 *
			 * @param V The other plane.
			 * @param Tolerance Error Tolerance.
			 * @return true if the two planes are equal within specified tolerance, otherwise false.
			 */
			[[nodiscard]] bool Equals(const FPlane& V, float Tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Calculates dot product of two planes.
			 *
			 * @param V The other plane.
			 * @return The dot product.
			 */
			FORCEINLINE float operator|(const FPlane& V) const;

			/**
			 * Gets result of adding a plane to this.
			 *
			 * @param V The other plane.
			 * @return The result of adding a plane to this.
			 */
			FPlane operator+(const FPlane& V) const;

			/**
			 * Gets result of subtracting a plane from this.
			 *
			 * @param V The other plane.
			 * @return The result of subtracting a plane from this.
			 */
			FPlane operator-(const FPlane& V) const;

			/**
			 * Gets result of dividing a plane.
			 *
			 * @param Scale What to divide by.
			 * @return The result of division.
			 */
			FPlane operator/(float Scale) const;

			/**
			 * Gets result of scaling a plane.
			 *
			 * @param Scale The scaling factor.
			 * @return The result of scaling.
			 */
			FPlane operator*(float Scale) const;

			/**
			 * Gets result of multiplying a plane with this.
			 *
			 * @param V The other plane.
			 * @return The result of multiplying a plane with this.
			 */
			FPlane operator*(const FPlane& V);

			/**
			 * Add another plane to this.
			 *
			 * @param V The other plane.
			 * @return Copy of plane after addition.
			 */
			FPlane operator+=(const FPlane& V);

			/**
			 * Subtract another plane from this.
			 *
			 * @param V The other plane.
			 * @return Copy of plane after subtraction.
			 */
			FPlane operator-=(const FPlane& V);

			/**
			 * Scale this plane.
			 *
			 * @param Scale The scaling factor.
			 * @return Copy of plane after scaling.
			 */
			FPlane operator*=(float Scale);

			/**
			 * Multiply another plane with this.
			 *
			 * @param V The other plane.
			 * @return Copy of plane after multiplication.
			 */
			FPlane operator*=(const FPlane& V);

			/**
			 * Divide this plane.
			 *
			 * @param V What to divide by.
			 * @return Copy of plane after division.
			 */
			FPlane operator/=(float V);
	} GCC_ALIGN(16);
}

#endif //VISREAL_F_PLANE_H
