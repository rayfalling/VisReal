/**
 * Created by rayfalling on 2020/10/30.
 * */

// ReSharper disable CppHiddenFunction
#pragma once

#ifndef VISREAL_F_VECTOR3_H
#define VISREAL_F_VECTOR3_H

#include "NumericLimits.h"
#include "VisRealMathUtility.h"
#include "fmt/CustomTypesFormatter.h"
#include "Marco/PlatformMarcos.h"
#include "Object/Object.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Math {
	class FPlane;

	class FVector3 : public Object {
		public:
			float X;
			float Y;
			float Z;

			FVector3() {
				this->X = 0.f;
				this->Y = 0.f;
				this->Z = 0.f;
			}

			explicit FVector3(float value);
			explicit FVector3(FVector4 value);
			explicit FVector3(float x, float y, float z);

		public:
			/** A zero vector (0,0,0) */
			static const FVector3 ZeroVector;

			/** One vector (1,1,1) */
			static const FVector3 OneVector;

			/** Up vector (0,0,1) */
			static const FVector3 UpVector;

			/** Down vector (0,0,-1) */
			static const FVector3 DownVector;

			/** Forward vector (1,0,0) */
			static const FVector3 ForwardVector;

			/** Backward vector (-1,0,0) */
			static const FVector3 BackwardVector;

			/** Right vector (0,1,0) */
			static const FVector3 RightVector;

			/** Left vector (0,-1,0) */
			static const FVector3 LeftVector;

		private:
			#if ENABLE_NAN_DIAGNOSTIC
			FORCEINLINE void DiagnosticCheckNaN() const {
				if (ContainsNaN()) {
					CoreLog::GetInstance().LogError(FString::Format("FVector3 contains NaN: {}", *this));
					*const_cast<FVector3*>(this) = ZeroVector;
				}
			}

			FORCEINLINE void DiagnosticCheckNaN(const TCHAR* message) const {
				if (ContainsNaN()) {
					CoreLog::GetInstance().LogError(FString::Format(TEXT("{}: FVector3 contains NaN: {}"), FString(message), *this));
					*const_cast<FVector3*>(this) = ZeroVector;
				}
			}
			#else
			// ReSharper disable once CppMemberFunctionMayBeStatic
			FORCEINLINE void DiagnosticCheckNaN() const {
			}

			// ReSharper disable once CppMemberFunctionMayBeStatic
			FORCEINLINE void DiagnosticCheckNaN(const TCHAR* Message) const {
			}
			#endif

			/* check if index in range */
			static void CheckIndex(int index);

		public:
			// operator methods

			/**
			 * Calculate cross product between this and another vector.
			 *
			 * @param vec The other vector.
			 * @return The cross product.
			 */
			FVector3 operator^(const FVector3& vec) const;

			/**
			 * Calculate the cross product of two vectors.
			 *
			 * @param first		The first vector.
			 * @param second	The second vector.
			 * @return			The cross product.
			 */
			static FVector3 CrossProduct(const FVector3& first, const FVector3& second);

			/**
			 * Calculate the dot product between this and another vector.
			 *
			 * @param vec The other vector.
			 * @return The dot product.
			 */
			float operator|(const FVector3& vec) const;

			/**
			 * Calculate the dot product of two vectors.
			 *
			 * @param first The first vector.
			 * @param second The second vector.
			 * @return The dot product.
			 */
			static float DotProduct(const FVector3& first, const FVector3& second);

			/**
			 * Gets the result of component-wise addition of this and another vector.
			 *
			 * @param vec The vector to add to this.
			 * @return The result of vector addition.
			 */
			FVector3 operator+(const FVector3& vec) const;

			/**
			 * Gets the result of component-wise subtraction of this by another vector.
			 *
			 * @param vec The vector to subtract from this.
			 * @return The result of vector subtraction.
			 */
			FVector3 operator-(const FVector3& vec) const;

			/**
			 * Gets the result of subtracting from each component of the vector.
			 *
			 * @param bias How much to subtract from each component.
			 * @return The result of subtraction.
			 */
			FVector3 operator-(float bias) const;

			/**
			 * Gets the result of adding to each component of the vector.
			 *
			 * @param bias How much to add to each component.
			 * @return The result of addition.
			 */
			FVector3 operator+(float bias) const;

			/**
			 * Gets the result of scaling the vector (multiplying each component by a value).
			 *
			 * @param scale What to multiply each component by.
			 * @return The result of multiplication.
			 */
			FVector3 operator*(float scale) const;

			/**
			 * Gets the result of dividing each component of the vector by a value.
			 *
			 * @param scale What to divide each component by.
			 * @return The result of division.
			 */
			FVector3 operator/(float scale) const;

			/**
			 * Gets the result of component-wise multiplication of this vector by another.
			 *
			 * @param vec The vector to multiply with.
			 * @return The result of multiplication.
			 */
			FVector3 operator*(const FVector3& vec) const;

			/**
			 * Gets the result of component-wise division of this vector by another.
			 *
			 * @param vec The vector to divide by.
			 * @return The result of division.
			 */
			FVector3 operator/(const FVector3& vec) const;

			// Binary comparison operators.

			/**
			 * Check against another vector for equality.
			 *
			 * @param vec The vector to check against.
			 * @return true if the vectors are equal, false otherwise.
			 */
			bool operator==(const FVector3& vec) const;

			/**
			 * Check against another vector for inequality.
			 *
			 * @param vec The vector to check against.
			 * @return true if the vectors are not equal, false otherwise.
			 */
			bool operator!=(const FVector3& vec) const;

			/**
			 * Check against another vector for equality, within specified error limits.
			 *
			 * @param vec The vector to check against.
			 * @param tolerance Error tolerance.
			 * @return true if the vectors are equal within tolerance limits, false otherwise.
			 */
			[[nodiscard]] bool Equals(const FVector3& vec, float tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Checks whether all components of this vector are the same, within a tolerance.
			 *
			 * @param tolerance Error tolerance.
			 * @return true if the vectors are equal within tolerance limits, false otherwise.
			 */
			[[nodiscard]] bool AllComponentsEqual(float tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Get a negated copy of the vector.
			 *
			 * @return A negated copy of the vector.
			 */
			FVector3 operator-() const;

			/**
			 * Adds another vector to this.
			 * Uses component-wise addition.
			 *
			 * @param vec vector to add to this.
			 * @return Copy of the vector after addition.
			 */
			FVector3 operator+=(const FVector3& vec);

			/**
			 * Subtracts another vector from this.
			 * Uses component-wise subtraction.
			 *
			 * @param vec vector to subtract from this.
			 * @return Copy of the vector after subtraction.
			 */
			FVector3 operator-=(const FVector3& vec);

			/**
			 * Scales the vector.
			 *
			 * @param scale Amount to scale this vector by.
			 * @return Copy of the vector after scaling.
			 */
			FVector3 operator*=(float scale);

			/**
			 * Divides the vector by a number.
			 *
			 * @param scale What to divide this vector by.
			 * @return Copy of the vector after division.
			 */
			FVector3 operator/=(float scale);

			/**
			 * Multiplies the vector with another vector, using component-wise multiplication.
			 *
			 * @param vec What to multiply this vector with.
			 * @return Copy of the vector after multiplication.
			 */
			FVector3 operator*=(const FVector3& vec);

			/**
			 * Divides the vector by another vector, using component-wise division.
			 *
			 * @param vec What to divide vector by.
			 * @return Copy of the vector after division.
			 */
			FVector3 operator/=(const FVector3& vec);

			/**
			 * Gets specific component of the vector.
			 *
			 * @param index the index of vector component
			 * @return reference to component.
			 */
			float& operator[](int32 index);

			/**
			 * Gets specific component of the vector.
			 *
			 * @param index the index of vector component
			 * @return Copy of the component.
			 */
			float operator[](int32 index) const;

			/**
			* Gets a specific component of the vector.
			*
			* @param index The index of the component required.
			*
			* @return Reference to the specified component.
			*/
			float& Component(int32 index);

			/**
			* Gets a specific component of the vector.
			*
			* @param index The index of the component required.
			* @return Copy of the specified component.
			*/
			[[nodiscard]] float Component(int32 index) const;

		public:
			// Simple functions.

			/**
			 * Set the values of the vector directly.
			 *
			 * @param x New X coordinate.
			 * @param y New Y coordinate.
			 * @param z New Z coordinate.
			 */
			void Set(float x, float y, float z);

			/**
			 * Get the maximum value of the vector's components.
			 *
			 * @return The maximum value of the vector's components.
			 */
			[[nodiscard]] float GetMax() const;

			/**
			 * Get the maximum absolute value of the vector's components.
			 *
			 * @return The maximum absolute value of the vector's components.
			 */
			[[nodiscard]] float GetAbsMax() const;

			/**
			 * Get the minimum value of the vector's components.
			 *
			 * @return The minimum value of the vector's components.
			 */
			[[nodiscard]] float GetMin() const;

			/**
			 * Get the minimum absolute value of the vector's components.
			 *
			 * @return The minimum absolute value of the vector's components.
			 */
			[[nodiscard]] float GetAbsMin() const;

			/** Gets the component-wise min of two vectors. */
			[[nodiscard]] FVector3 ComponentMin(const FVector3& other) const;

			/** Gets the component-wise max of two vectors. */
			[[nodiscard]] FVector3 ComponentMax(const FVector3& other) const;

			/**
			 * Get a copy of this vector with absolute value of each component.
			 *
			 * @return A copy of this vector with absolute value of each component.
			 */
			[[nodiscard]] FVector3 GetAbs() const;

			/**
			 * Get the length (magnitude) of this vector.
			 *
			 * @return The length of this vector.
			 */
			[[nodiscard]] float Size() const;

			/**
			 * Get the squared length of this vector.
			 *
			 * @return The squared length of this vector.
			 */
			[[nodiscard]] float SizeSquared() const;

			/**
			 * Get the length of the 2D components of this vector.
			 *
			 * @return The 2D length of this vector.
			 */
			[[nodiscard]] float Size2D() const;

			/**
			 * Get the squared length of the 2D components of this vector.
			 *
			 * @return The squared 2D length of this vector.
			 */
			[[nodiscard]] float SizeSquared2D() const;

			/**
			 * Checks whether vector is near to zero within a specified tolerance.
			 *
			 * @param tolerance Error tolerance.
			 * @return true if the vector is near to zero, false otherwise.
			 */
			[[nodiscard]] bool IsNearlyZero(float tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Checks whether all components of the vector are exactly zero.
			 *
			 * @return true if the vector is exactly zero, false otherwise.
			 */
			[[nodiscard]] bool IsZero() const;

			/**
			 * Check if the vector is of unit length, with specified tolerance.
			 *
			 * @param lengthSquaredTolerance Tolerance against squared length.
			 * @return true if the vector is a unit vector within the specified tolerance.
			 */
			[[nodiscard]] bool IsUnit(float lengthSquaredTolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Checks whether vector is normalized.
			 *
			 * @return true if normalized, false otherwise.
			 */
			[[nodiscard]] bool IsNormalized() const;

			/**
			 * Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.
			 *
			 * @param tolerance Minimum squared length of vector for normalization.
			 * @return true if the vector was normalized correctly, false otherwise.
			 */
			bool Normalize(float tolerance = SMALL_NUMBER);

			/**
			 * Calculates normalized version of vector without checking for zero length.
			 *
			 * @return Normalized version of vector.
			 * @see GetSafeNormal()
			 */
			[[nodiscard]] FVector3 GetUnsafeNormal() const;

			/**
			 * Gets a normalized copy of the vector, checking it is safe to do so based on the length.
			 * Returns zero vector if vector length is too small to safely normalize.
			 *
			 * @param tolerance Minimum squared vector length.
			 * @return A normalized copy if safe, (0,0,0) otherwise.
			 */
			[[nodiscard]] FVector3 GetSafeNormal(float tolerance = SMALL_NUMBER) const;

			/**
			 * Gets a normalized copy of the 2D components of the vector, checking it is safe to do so. Z is set to zero.
			 * Returns zero vector if vector length is too small to normalize.
			 *
			 * @param tolerance Minimum squared vector length.
			 * @return Normalized copy if safe, otherwise returns zero vector.
			 */
			[[nodiscard]] FVector3 GetSafeNormal2D(float tolerance = SMALL_NUMBER) const;

			/**
			 * Util to convert this vector into a unit direction vector and its original length.
			 *
			 * @param outDir Reference passed in to store unit direction vector.
			 * @param outLength Reference passed in to store length of the vector.
			 */
			void ToDirectionAndLength(FVector3& outDir, float& outLength) const;

			/**
			 * Get a copy of the vector as sign only.
			 * Each component is set to +1 or -1, with the sign of zero treated as +1.
			 */
			FORCEINLINE FVector3 GetSignVector() const;

			/**
			 * Projects 2D components of vector based on Z.
			 *
			 * @return Projected version of vector based on Z.
			 */
			[[nodiscard]] FVector3 Projection() const;

			/**
			* Calculates normalized 2D version of vector without checking for zero length.
			*
			* @return Normalized version of vector.
			* @see GetSafeNormal2D()
			*/
			FORCEINLINE FVector3 GetUnsafeNormal2D() const;

			/**
			 * Gets a copy of this vector snapped to a grid.
			 *
			 * @param gridSize Grid dimension.
			 * @return A copy of this vector snapped to a grid.
			 * @see FMath::GridSnap()
			 */
			[[nodiscard]] FVector3 GridSnap(const float& gridSize) const;

			/**
			 * Get a copy of this vector, clamped inside of a cube.
			 *
			 * @param radius Half size of the cube.
			 * @return A copy of this vector, bound by cube.
			 */
			[[nodiscard]] FVector3 BoundToCube(float radius) const;

			/** Get a copy of this vector, clamped inside of a cube. */
			[[nodiscard]] FVector3 BoundToBox(const FVector3& min, const FVector3& max) const;

			/** Create a copy of this vector, with its magnitude clamped between Min and Max. */
			[[nodiscard]] FVector3 GetClampedToSize(float min, float max) const;

			/** Create a copy of this vector, with the 2D magnitude clamped between Min and Max. Z is unchanged. */
			[[nodiscard]] FVector3 GetClampedToSize2D(float min, float max) const;

			/** Create a copy of this vector, with its maximum magnitude clamped to MaxSize. */
			[[nodiscard]] FVector3 GetClampedToMaxSize(float maxSize) const;

			/** Create a copy of this vector, with the maximum 2D magnitude clamped to MaxSize. Z is unchanged. */
			[[nodiscard]] FVector3 GetClampedToMaxSize2D(float maxSize) const;

			/**
			 * Add a vector to this and clamp the result in a cube.
			 *
			 * @param v Vector to add.
			 * @param radius Half size of the cube.
			 */
			void AddBounded(const FVector3& v, float radius = MAX_INT16);

			/**
			 * Gets the reciprocal of this vector, avoiding division by zero.
			 * Zero components are set to BIG_NUMBER.
			 *
			 * @return Reciprocal of this vector.
			 */
			[[nodiscard]] FVector3 Reciprocal() const;

			/**
			 * Check whether X, Y and Z are nearly equal.
			 *
			 * @param tolerance Specified Tolerance.
			 * @return true if X == Y == Z within the specified tolerance.
			 */
			[[nodiscard]] bool IsUniform(float tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Mirror a vector about a normal vector.
			 *
			 * @param mirrorNormal Normal vector to mirror about.
			 * @return Mirrored vector.
			 */
			[[nodiscard]] FVector3 MirrorByVector(const FVector3& mirrorNormal) const;

			/**
			 * Mirrors a vector about a plane.
			 *
			 * @param plane Plane to mirror about.
			 * @return Mirrored vector.
			 */
			[[nodiscard]] FVector3 MirrorByPlane(const Math::FPlane& plane) const;

			/**
			 * Rotates around Axis (assumes Axis.Size() == 1).
			 *
			 * @param angleDeg Angle to rotate (in degrees).
			 * @param axis Axis to rotate around.
			 * @return Rotated Vector.
			 */
			[[nodiscard]] FVector3 RotateAngleAxis(float angleDeg, const FVector3& axis) const;

			/**
			 * Returns the cosine of the angle between this vector and another projected onto the XY plane (no Z).
			 *
			 * @param b the other vector to find the 2D cosine of the angle with.
			 * @return The cosine.
			 */
			FORCEINLINE float CosineAngle2D(FVector3 b) const;

			/**
			 * Gets a copy of this vector projected onto the input vector.
			 *
			 * @param a	Vector to project onto, does not assume it is normalized.
			 * @return Projected vector.
			 */
			FORCEINLINE FVector3 ProjectOnTo(const FVector3& a) const;

			/**
			 * Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
			 *
			 * @param  normal Vector to project onto (assumed to be unit length).
			 * @return Projected vector.
			 */
			FORCEINLINE FVector3 ProjectOnToNormal(const FVector3& normal) const;

		public:
			/**
			 * Utility to check if there are any non-finite values (NaN or Inf) in this vector.
			 *
			 * @return true if there are any non-finite values in this vector, false otherwise.
			 */
			[[nodiscard]] bool ContainsNaN() const;

			/**
			 * Find good arbitrary axis vectors to represent U and V axes of a plane,
			 * using this vector as the normal of the plane.
			 *
			 * @param axis1 Reference to first axis.
			 * @param axis2 Reference to second axis.
			 */
			void FindBestAxisVectors(FVector3& axis1, FVector3& axis2) const;

			/** When this vector contains Euler angles (degrees), ensure that angles are between +/-180 */
			void UnwindEuler();

			/**
			 * Get a textual representation of this vector.
			 *
			 * @return A string describing the vector.
			 */
			[[nodiscard]] FString ToString() const;

			/**
			 * Create an orthonormal basis from a basis with at least two orthogonal vectors.
			 * It may change the directions of the X and Y axes to make the basis orthogonal,
			 * but it won't change the direction of the Z axis.
			 * All axes will be normalized.
			 *
			 * @param xAxis The input basis' XAxis, and upon return the orthonormal basis' XAxis.
			 * @param yAxis The input basis' YAxis, and upon return the orthonormal basis' YAxis.
			 * @param zAxis The input basis' ZAxis, and upon return the orthonormal basis' ZAxis.
			 */
			static void CreateOrthonormalBasis(FVector3& xAxis, FVector3& yAxis, FVector3& zAxis);
	};

	/**
	 * Multiplies a vector by a scaling factor.
	 *
	 * @param scale Scaling factor.
	 * @param v Vector to scale.
	 * @return Result of multiplication.
	 */
	FORCEINLINE FVector3 operator*(const float scale, const FVector3& v) {
		return v.operator*(scale);
	}

	/** 
	 * Util to calculate distance from a point to a bounding box 
	 *
	 * @param min 3D Point defining the lower values of the axis of the bound box
	 * @param max 3D Point defining the lower values of the axis of the bound box
	 * @param point 3D position of interest
	 * @return the distance from the Point to the bounding box.
	 */
	float ComputeSquaredDistanceFromBoxToPoint(const FVector3& min, const FVector3& max, const FVector3& point);
}

#include "FVector.inl"

#endif //VISREAL_F_VECTOR3_H
