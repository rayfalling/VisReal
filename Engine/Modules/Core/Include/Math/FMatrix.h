/**
 * Created by rayfalling on 2020/11/10.
 * */

#pragma once

#ifndef VISREAL_MATRIX_H
#define VISREAL_MATRIX_H

#include "Axis.h"
#include "VisRealMathUtility.h"
#include "Marco/PlatformMarcos.h"
#include "Container/FString.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Math {
	class FVector3;
	class FPlane;
	/**
	 * 4x4 matrix of floating point values.
	 * Matrix-matrix multiplication happens with a pre-multiple of the transpose --
	 * in other words, Res = Mat1.operator*(Mat2) means Res = Mat2^T * Mat1, as
	 * opposed to Res = Mat1 * Mat2.
	 * Matrix elements are accessed with M[RowIndex][ColumnIndex].
	 */
	class FMatrix {
		public:
			union {
				MS_ALIGN(16) float M[4][4] GCC_ALIGN(16);
			};

			//Identity matrix
			MS_ALIGN(16) static const FMatrix Identity GCC_ALIGN(16);

			// Constructors.
			FORCEINLINE FMatrix();

			/**
			 * Constructor.
			 *
			 * @param InX X plane
			 * @param InY Y plane
			 * @param InZ Z plane
			 * @param InW W plane
			 */
			FORCEINLINE FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW);

			/**
			 * Constructor.
			 *
			 * @param InX X vector
			 * @param InY Y vector
			 * @param InZ Z vector
			 * @param InW W vector
			 */
			FORCEINLINE FMatrix(const FVector3& InX, const FVector3& InY, const FVector3& InZ, const FVector3& InW);

			// Set this to the identity matrix
			inline void SetIdentity();

			/**
			 * Gets the result of multiplying a Matrix to this.
			 *
			 * @param Other The matrix to multiply this by.
			 * @return The result of multiplication.
			 */
			FORCEINLINE FMatrix operator*(const FMatrix& Other) const;

			/**
			 * Multiply this by a matrix.
			 *
			 * @param Other the matrix to multiply by this.
			 * @return reference to this after multiply.
			 */
			FORCEINLINE FMatrix operator*=(const FMatrix& Other);

			/**
			 * Gets the result of adding a matrix to this.
			 *
			 * @param Other The Matrix to add.
			 * @return The result of addition.
			 */
			FORCEINLINE FMatrix operator+(const FMatrix& Other) const;

			/**
			 * Adds to this matrix.
			 *
			 * @param Other The matrix to add to this.
			 * @return Reference to this after addition.
			 */
			FORCEINLINE FMatrix operator+=(const FMatrix& Other);

			/**
			  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
			  */
			FORCEINLINE FMatrix operator*(float Other) const;

			/**
			 * Multiply this matrix by a weighting factor.
			 *
			 * @param Other The weight.
			 * @return a reference to this after weighting.
			 */
			FORCEINLINE FMatrix operator*=(float Other);

			/**
			 * Checks whether two matrix are identical.
			 *
			 * @param Other The other matrix.
			 * @return true if two matrix are identical, otherwise false.
			 */
			inline bool operator==(const FMatrix& Other) const;

			/**
			 * Checks whether another Matrix is equal to this, within specified tolerance.
			 *
			 * @param Other The other Matrix.
			 * @param Tolerance Error Tolerance.
			 * @return true if two Matrix are equal, within specified tolerance, otherwise false.
			 */
			[[nodiscard]] inline bool Equals(const FMatrix& Other, float Tolerance = KINDA_SMALL_NUMBER) const;

			/**
			 * Checks whether another Matrix is not equal to this, within specified tolerance.
			 *
			 * @param Other The other Matrix.
			 * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
			 */
			inline bool operator!=(const FMatrix& Other) const;

			// Homogeneous transform.
			// FORCEINLINE FVector4 TransformFVector34(const FVector4& V) const;

			/** Transform a location - will take into account translation part of the FMatrix. */
			// FORCEINLINE FVector4 TransformPosition(const FVector3& V) const;

			/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
			FORCEINLINE FVector3 InverseTransformPosition(const FVector3& V) const;

			/**
			 *	Transform a direction vector - will not take into account translation part of the FMatrix.
			 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
			 */
			// FORCEINLINE FVector4 TransformVector(const FVector3& V) const;

			/**
			 *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
			 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
			 */
			FORCEINLINE FVector3 InverseTransformVector(const FVector3& V) const;

			// Transpose.

			FORCEINLINE FMatrix GetTransposed() const;

			// @return determinant of this matrix.

			[[nodiscard]] inline float Determinant() const;

			/** @return the determinant of rotation 3x3 matrix */
			[[nodiscard]] inline float RotDeterminant() const;

			/** Fast path, doesn't check for nil matrices in final release builds */
			[[nodiscard]] inline FMatrix InverseFast() const;

			/** Fast path, and handles nil matrices. */
			[[nodiscard]] inline FMatrix Inverse() const;

			[[nodiscard]] inline FMatrix TransposeAdjoint() const;

			// NOTE: There is some compiler optimization issues with WIN64 that cause FORCEINLINE to cause a crash
			// Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
			inline void RemoveScaling(float Tolerance = SMALL_NUMBER);

			// Returns matrix after RemoveScaling with error Tolerance
			[[nodiscard]] inline FMatrix GetMatrixWithoutScale(float Tolerance = SMALL_NUMBER) const;

			/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
			inline FVector3 ExtractScaling(float Tolerance = SMALL_NUMBER);

			/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
			[[nodiscard]] inline FVector3 GetScaleVector(float Tolerance = SMALL_NUMBER) const;

			// Remove any translation from this matrix
			[[nodiscard]] inline FMatrix RemoveTranslation() const;

			/** Returns a matrix with an additional translation concatenated. */
			[[nodiscard]] inline FMatrix ConcatTranslation(const FVector3& Translation) const;

			/** Returns true if any element of this matrix is NaN */
			[[nodiscard]] inline bool ContainsNaN() const;

			/** Scale the translation part of the matrix by the supplied vector. */
			inline void ScaleTranslation(const FVector3& Scale3D);

			/** @return the maximum magnitude of any row of the matrix. */
			[[nodiscard]] inline float GetMaximumAxisScale() const;

			/** Apply Scale to this matrix **/
			[[nodiscard]] inline FMatrix ApplyScale(float Scale) const;

			// @return the origin of the co-ordinate system
			[[nodiscard]] inline FVector3 GetOrigin() const;

			/**
			 * get axis of this matrix scaled by the scale of the matrix
			 *
			 * @param i index into the axis of the matrix
			 * @ return vector of the axis
			 */
			[[nodiscard]] inline FVector3 GetScaledAxis(EAxis::Type Axis) const;

			/**
			 * get axes of this matrix scaled by the scale of the matrix
			 *
			 * @param X axes returned to this param
			 * @param Y axes returned to this param
			 * @param Z axes returned to this param
			 */
			inline void GetScaledAxes(FVector3& X, FVector3& Y, FVector3& Z) const;

			/**
			 * get unit length axis of this matrix
			 *
			 * @param i index into the axis of the matrix
			 * @return vector of the axis
			 */
			[[nodiscard]] inline FVector3 GetUnitAxis(EAxis::Type Axis) const;

			/**
			 * get unit length axes of this matrix
			 *
			 * @param X axes returned to this param
			 * @param Y axes returned to this param
			 * @param Z axes returned to this param
			 */
			inline void GetUnitAxes(FVector3& X, FVector3& Y, FVector3& Z) const;

			/**
			 * set an axis of this matrix
			 *
			 * @param i index into the axis of the matrix
			 * @param Axis vector of the axis
			 */
			inline void SetAxis(int32 i, const FVector3& Axis);

			// Set the origin of the coordinate system to the given vector
			inline void SetOrigin(const FVector3& NewOrigin);

			/**
			 * Update the axes of the matrix if any value is NULL do not update that axis
			 *
			 * @param Axis0 set matrix row 0
			 * @param Axis1 set matrix row 1
			 * @param Axis2 set matrix row 2
			 * @param Origin set matrix row 3
			 */
			inline void SetAxes(FVector3* Axis0 = nullptr, FVector3* Axis1 = nullptr, FVector3* Axis2 = nullptr, FVector3* Origin = nullptr);


			/**
			 * get a column of this matrix
			 *
			 * @param i index into the column of the matrix
			 * @return vector of the column
			 */
			[[nodiscard]] inline FVector3 GetColumn(int32 i) const;

			/**
			 * Set a column of this matrix
			 *
			 * @param i index of the matrix column
			 * @param Value new value of the column
			 */
			inline void SetColumn(int32 i, FVector3 Value);

			/** @return rotator representation of this matrix */
			// FRotator Rotator() const;

			/**
			 * Transform a rotation matrix into a quaternion.
			 *
			 * @warning rotation part will need to be unit length for this to be right!
			 */
			// FQuat ToQuat() const;

			// Frustum plane extraction.
			/** @param OutPlane the near plane of the Frustum of this matrix */
			FORCEINLINE bool GetFrustumNearPlane(FPlane& OutPlane) const;

			/** @param OutPlane the far plane of the Frustum of this matrix */
			FORCEINLINE bool GetFrustumFarPlane(FPlane& OutPlane) const;

			/** @param OutPlane the left plane of the Frustum of this matrix */
			FORCEINLINE bool GetFrustumLeftPlane(FPlane& OutPlane) const;

			/** @param OutPlane the right plane of the Frustum of this matrix */
			FORCEINLINE bool GetFrustumRightPlane(FPlane& OutPlane) const;

			/** @param OutPlane the top plane of the Frustum of this matrix */
			FORCEINLINE bool GetFrustumTopPlane(FPlane& OutPlane) const;

			/** @param OutPlane the bottom plane of the Frustum of this matrix */
			FORCEINLINE bool GetFrustumBottomPlane(FPlane& OutPlane) const;

			/**
			 * Utility for mirroring this transform across a certain plane, and flipping one of the axis as well.
			 */
			inline void Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis);

			/**
			 * Get a textual representation of the vector.
			 *
			 * @return Text describing the vector.
			 */
			[[nodiscard]] FString ToString() const;

			/** Output ToString */
			void DebugPrint() const;

			/** For debugging purpose, could be changed */
			[[nodiscard]] uint32 ComputeHash() const;

			/**
			 * Convert this Atom to the 3x4 transpose of the transformation matrix.
			 */
			void To3x4MatrixTranspose(float* Out) const {
				const float* RESTRICT Src = &(M[0][0]);
				float* RESTRICT Dest = Out;

				Dest[0] = Src[0];  // [0][0]
				Dest[1] = Src[4];  // [1][0]
				Dest[2] = Src[8];  // [2][0]
				Dest[3] = Src[12]; // [3][0]

				Dest[4] = Src[1];  // [0][1]
				Dest[5] = Src[5];  // [1][1]
				Dest[6] = Src[9];  // [2][1]
				Dest[7] = Src[13]; // [3][1]

				Dest[8] = Src[2];   // [0][2]
				Dest[9] = Src[6];   // [1][2]
				Dest[10] = Src[10]; // [2][2]
				Dest[11] = Src[14]; // [3][2]
			}

		private:

			/**
			 * Output an error message and trigger an ensure
			 */
			static void ErrorEnsure(const TCHAR* Message);
	};
}

#endif // VISREAL_MATRIX_H
