/**
 * Created by rayfalling on 2020/10/30.
 * */

#pragma once

#ifndef VISREAL_VISREAL_MATH_UTILITY_H
#define VISREAL_VISREAL_MATH_UTILITY_H

#include "Logger/CoreLog.h"
#include "Platform/PreCompile/Platform.h"
#include "Platform/PreCompile/PlatformMath.h"
#include "Platform/PreCompile/PlatformTypes.h"

// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
namespace Engine::Core::Math {

	#undef  PI
	#define PI						(3.1415926535897932f)    /* Extra digits if needed: 3.1415926535897932384626433832795f * */
	#define SMALL_NUMBER			(1.e-8f)
	#define KINDA_SMALL_NUMBER		(1.e-4f)
	#define BIG_NUMBER				(3.4e+38f)
	#define EULERS_NUMBER			(2.71828182845904523536f)
	#define GOLDEN_RATIO			(1.6180339887498948482045868343656381f)    /* Also known as divine proportion, golden mean, or golden section - related to the Fibonacci Sequence = (1 + sqrt(5)) / 2 * */

	// Copied from float.h
	#define MAX_FLT					(3.402823466e+38F)

	// Aux constants.
	#define INV_PI					(0.31830988618f)
	#define HALF_PI					(1.57079632679f)

	// Common square roots
	#define SQRT_2				(1.4142135623730950488016887242097f)
	#define SQRT_3				(1.7320508075688772935274463415059f)
	#define INV_SQRT_2			(0.70710678118654752440084436210485f)
	#define INV_SQRT_3			(0.57735026918962576450914878050196f)
	#define HALF_SQRT_2			(0.70710678118654752440084436210485f)
	#define HALF_SQRT_3			(0.86602540378443864676372317075294f)


	// Magic numbers for numerical precision.
	#define DELTA					(0.00001f)

	/**
	 * Lengths of normalized vectors (These are half their maximum values
	 * to assure that dot products with normalized vectors don't overflow).
	 * */
	#define FLOAT_NORMAL_THRESH					(0.0001f)

	//
	// Magic numbers for numerical precision.
	//
	#define THRESH_POINT_ON_PLANE				(0.10f)			/* Thickness of plane for front/back/inside test * */
	#define THRESH_POINT_ON_SIDE				(0.20f)			/* Thickness of polygon side's side-plane for point-inside/outside/on side test * */
	#define THRESH_POINTS_ARE_SAME				(0.00002f)		/* Two points are same if within this distance * */
	#define THRESH_POINTS_ARE_NEAR				(0.015f)		/* Two points are near if within this distance and can be combined if imprecise math is ok * */
	#define THRESH_NORMALS_ARE_SAME				(0.00002f)		/* Two normal points are same if within this distance * */
	#define THRESH_UVS_ARE_SAME					(0.0009765625f)	/* Two UV are same if within this threshold (1.0f/1024f) * */
	/* Making this too large results in incorrect CSG classification and disaster * */
	#define THRESH_VECTORS_ARE_NEAR				(0.0004f)		/* Two vectors are near if within this distance and can be combined if imprecise math is ok * */
	/* Making this too large results in lighting problems due to inaccurate texture coordinates * */
	#define THRESH_SPLIT_POLY_WITH_PLANE		(0.25f)			/* A plane splits a polygon in half * */
	#define THRESH_SPLIT_POLY_PRECISELY			(0.01f)			/* A plane exactly splits a polygon * */
	#define THRESH_ZERO_NORM_SQUARED			(0.0001f)		/* Size of a unit normal that is considered "zero", squared * */
	#define THRESH_NORMALS_ARE_PARALLEL			(0.999845f)		/* Two unit vectors are parallel if abs(A dot B) is greater than or equal to this. This is roughly cosine(1.0 degrees). * */
	#define THRESH_NORMALS_ARE_ORTHOGONAL		(0.017455f)		/* Two unit vectors are orthogonal (perpendicular) if abs(A dot B) is less than or equal this. This is roughly cosine(89.0 degrees). * */

	#define THRESH_VECTOR_NORMALIZED			(0.01f)			/** Allowed error for a normalized vector (against squared magnitude) * */
	#define THRESH_QUAT_NORMALIZED				(0.01f)			/** Allowed error for a normalized quaternion (against squared magnitude) * */

	// Forward declarations.
	class FVector2;
	class FVector3;
	class FVector4;
	class FBox;
	class FPlane;
	class FBox;
	class FRotator;
	class FMatrix;
	class FQuat;
	class FTwoVectors;
	class FTransform;
	class FSphere;
	class FLinearColor;

	struct FMath : public FPlatformMath {
		// Random Number Functions

		/** Helper function for rand implementations. Returns value random number in [0..A) * */
		static FORCEINLINE int32 RandHelper(const int32 value) {
			// Note that on some platforms RAND_MAX is value large number so we cannot do ((rand()/(RAND_MAX+1)) * A)
			// or else we may include the upper bound results, which should be excluded.
			return value > 0 ? Min(TruncToInt(FRand() * value), value - 1) : 0;
		}

		static FORCEINLINE int64 RandHelper64(const int64 value) {
			// Note that on some platforms RAND_MAX is a large number so we cannot do ((rand()/(RAND_MAX+1)) * value)
			// or else we may include the upper bound results, which should be excluded.
			return value > 0 ? Min<int64>(TruncToInt(value * FRand()), value - 1) : 0;
		}

		/** Helper function for rand implementations. Returns a random number >= Min and <= Max * */
		static FORCEINLINE int32 RandRange(const int32 min, const int32 max) {
			const auto range = (max - min) + 1;
			return min + RandHelper(range);
		}

		static FORCEINLINE int64 RandRange(const int64 min, const int64 max) {
			const auto Range = (max - min) + 1;
			return min + RandHelper64(Range);
		}

		/** Util to generate a random number in a range. Overloaded to distinguish from int32 version, where passing a float is typically a mistake. * */
		static FORCEINLINE float RandRange(const float inMin, const float inMax) {
			return FRandRange(inMin, inMax);
		}

		/** Util to generate a random number in a range. * */
		static FORCEINLINE float FRandRange(const float inMin, const float inMax) {
			return inMin + (inMax - inMin) * FRand();
		}

		/** Util to generate a random boolean. * */
		static FORCEINLINE bool RandBool() {
			return (RandRange(0, 1) == 1) ? true : false;
		}

		/** Return a uniformly distributed random unit length vector = point on the unit sphere surface. * */
		static FVector3 VRand();

		/**
		 * Returns a random unit vector, uniformly distributed, within the specified cone
		 * ConeHalfAngleRad is the half-angle of cone, in radians.  Returns a normalized vector.
		 * */
		static FVector3 VRandCone(FVector3 const& Dir, float ConeHalfAngleRad);

		/**
		 * This is a version of VRandCone that handles "squished" cones, i.e. with different angle limits in the Y and Z axes.
		 * Assumes world Y and Z, although this could be extended to handle arbitrary rotations.
		 * */
		static FVector3 VRandCone(FVector3 const& Dir, float HorizontalConeHalfAngleRad, float VerticalConeHalfAngleRad);

		/** Returns a random point, uniformly distributed, within the specified radius * */
		static FVector2 RandPointInCircle(float CircleRadius);

		/** Returns a random point within the passed in bounding box * */
		static FVector3 RandPointInBox(const FBox& Box);

		/**
		 * Given a direction vector and a surface normal, returns the vector reflected across the surface normal.
		 * Produces a result like shining a laser at a mirror!
		 *
		 * @param Direction Direction vector the ray is coming from.
		 * @param SurfaceNormal A normal of the surface the ray should be reflected on.
		 *
		 * @returns Reflected vector.
		 * */
		static FVector3 GetReflectionVector(const FVector3& Direction, const FVector3& SurfaceNormal);

		// Predicates

		/** Checks if value is within a range, exclusive on MaxValue) * */
		template <class U>
		static FORCEINLINE bool IsWithin(const U& testValue, const U& minValue, const U& maxValue) {
			return ((testValue >= minValue) && (testValue < maxValue));
		}

		/** Checks if value is within a range, inclusive on MaxValue) * */
		template <class U>
		static FORCEINLINE bool IsWithinInclusive(const U& testValue, const U& minValue, const U& maxValue) {
			return ((testValue >= minValue) && (testValue <= maxValue));
		}

		/**
		 *	Checks if two floating point numbers are nearly equal.
		 *	@param a				First number to compare
		 *	@param b				Second number to compare
		 *	@param errorTolerance	Maximum allowed difference for considering them as 'nearly equal'
		 *	@return					true if A and B are nearly equal
		 * */
		static FORCEINLINE bool IsNearlyEqual(const float a, const float b, const float errorTolerance = SMALL_NUMBER) {
			return Abs<float>(a - b) <= errorTolerance;
		}

		/**
		 *	Checks if two floating point numbers are nearly equal.
		 *	@param a				First number to compare
		 *	@param b				Second number to compare
		 *	@param errorTolerance	Maximum allowed difference for considering them as 'nearly equal'
		 *	@return					true if A and B are nearly equal
		 * */
		static FORCEINLINE bool IsNearlyEqual(const double a, const double b, const double errorTolerance = SMALL_NUMBER) {
			return Abs<double>(a - b) <= errorTolerance;
		}

		/**
		 *	Checks if a floating point number is nearly zero.
		 *	@param value			Number to compare
		 *	@param errorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
		 *	@return					true if Value is nearly zero
		 * */
		static FORCEINLINE bool IsNearlyZero(const float value, const float errorTolerance = SMALL_NUMBER) {
			return Abs<float>(value) <= errorTolerance;
		}

		/**
		 *	Checks if a floating point number is nearly zero.
		 *	@param value			Number to compare
		 *	@param errorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
		 *	@return					true if Value is nearly zero
		 * */
		static FORCEINLINE bool IsNearlyZero(const double value, const double errorTolerance = SMALL_NUMBER) {
			return Abs<double>(value) <= errorTolerance;
		}

		/**
		 *	Checks whether a number is a power of two.
		 *	@param value	Number to check
		 *	@return			true if Value is a power of two
		 * */
		template <typename T>
		static FORCEINLINE bool IsPowerOfTwo(T value) {
			return ((value & (value - 1)) == static_cast<T>(0));
		}


		// Math Operations

		/** Returns highest of 3 values * */
		template <class T>
		static FORCEINLINE T Max3(const T a, const T b, const T c) {
			return Max(Max(a, b), c);
		}

		/** Returns lowest of 3 values * */
		template <class T>
		static FORCEINLINE T Min3(const T a, const T b, const T c) {
			return Min(Min(a, b), c);
		}

		/** Multiples value by itself * */
		template <class T>
		static FORCEINLINE T Square(const T a) {
			return a * a;
		}

		/** Clamps X to be between Min and Max, inclusive * */
		template <class T>
		static FORCEINLINE T Clamp(const T x, const T min, const T max) {
			return x < min ? min : x < max ? x : max;
		}

		/** Snaps a value to the nearest grid multiple * */
		static FORCEINLINE float GridSnap(const float location, const float grid) {
			if (grid == 0.f) return location;
			return FloorToFloat((location + 0.5f * grid) / grid) * grid;
		}

		/** Snaps a value to the nearest grid multiple * */
		static FORCEINLINE double GridSnap(const double location, const double grid) {
			if (grid == 0.0) return location;
			return FloorToDouble((location + 0.5 * grid) / grid) * grid;
		}

		/** Divides two integers and rounds up * */
		template <class T>
		static FORCEINLINE T DivideAndRoundUp(T dividend, T divisor) {
			return (dividend + divisor - 1) / divisor;
		}

		/** Divides two integers and rounds down * */
		template <class T>
		static FORCEINLINE T DivideAndRoundDown(T dividend, T divisor) {
			return dividend / divisor;
		}

		/** Divides two integers and rounds to nearest * */
		template <class T>
		static FORCEINLINE T DivideAndRoundNearest(T dividend, T divisor) {
			return (dividend >= 0) ? (dividend + divisor / 2) / divisor : (dividend - divisor / 2 + 1) / divisor;
		}

		/**
		 * Computes the base 2 logarithm of the specified value
		 *
		 * @param value the value to perform the log on
		 *
		 * @return the base 2 log of the value
		 * */
		static FORCEINLINE float Log2(const float value) {
			// Cached value for fast conversions
			static const auto LogToLog2 = 1.f / Loge(2.f);
			// Do the platform specific log and convert using the cached value
			return Loge(value) * LogToLog2;
		}

		/**
		* Computes the sine and cosine of a scalar value.
		*
		* @param scalarSin	Pointer to where the Sin result should be stored
		* @param scalarCos	Pointer to where the Cos result should be stored
		* @param Value  input angles
		* */
		static FORCEINLINE void SinCos(float* scalarSin, float* scalarCos, const float Value) {
			// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
			auto quotient = (INV_PI * 0.5f) * Value;
			if (Value >= 0.0f) {
				quotient = static_cast<float>(static_cast<int>(0.5f + quotient));
			} else {
				quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
			}
			auto y = Value - (2.0f * PI) * quotient;

			// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
			float sign;
			if (y > HALF_PI) {
				y = PI - y;
				sign = -1.0f;
			} else if (y < -HALF_PI) {
				y = -PI - y;
				sign = -1.0f;
			} else {
				sign = +1.0f;
			}

			auto y2 = y * y;

			// 11-degree minimax approximation
			*scalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 +
				1.0f) * y;

			// 10-degree minimax approximation
			auto p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
			*scalarCos = sign * p;
		}


		// Note:  We use FASTASIN_HALF_PI instead of HALF_PI inside of FastASin(), since it was the value that accompanied the minimax coefficients below.
		// It is important to use exactly the same value in all places inside this function to ensure that FastASin(0.0f) == 0.0f.
		// For comparison:
		//		HALF_PI				== 1.57079632679f == 0x3fC90FDB
		//		FASTASIN_HALF_PI	== 1.5707963050f  == 0x3fC90FDA
		#define FASTASIN_HALF_PI (1.5707963050f)
		/**
		* Computes the ASin of a scalar value.
		*
		* @param value  input angle
		* @return ASin of Value
		* */
		static FORCEINLINE float FastAsin(const float value) {
			// Clamp input to [-1,1].
			const auto nonnegative = (value >= 0.0f);
			const auto x = Abs(value);
			auto omx = 1.0f - x;
			if (omx < 0.0f) {
				omx = 0.0f;
			}
			auto root = Sqrt(omx);
			// 7-degree minimax approximation
			auto result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x +
				0.0889789874f) * x - 0.2145988016f) * x + FASTASIN_HALF_PI;
			result *= root; // acos(|x|)
			// acos(x) = pi - acos(-x) when x < 0, asin(x) = pi/2 - acos(x)
			return (nonnegative ? FASTASIN_HALF_PI - result : result - FASTASIN_HALF_PI);
		}
		#undef FASTASIN_HALF_PI


		// Conversion Functions

		/**
		 * Converts radians to degrees.
		 * @param	radVal			Value in radians.
		 * @return					Value in degrees.
		 * */
		template <class T>
		static FORCEINLINE auto RadiansToDegrees(T const& radVal) -> decltype(radVal * (180.f / PI)) {
			return radVal * (180.f / PI);
		}

		/**
		 * Converts degrees to radians.
		 * @param	degVal			Value in degrees.
		 * @return					Value in radians.
		 * */
		template <class T>
		static FORCEINLINE auto DegreesToRadians(T const& degVal) -> decltype(degVal * (PI / 180.f)) {
			return degVal * (PI / 180.f);
		}

		/**
		 * Clamps an arbitrary angle to be between the given angles.  Will clamp to nearest boundary.
		 *
		 * @param AngleDegrees
		 * @param MinAngleDegrees	"from" angle that defines the beginning of the range of valid angles (sweeping clockwise)
		 * @param MaxAngleDegrees	"to" angle that defines the end of the range of valid angles
		 * @return Returns clamped angle in the range -180..180.
		 * */
		static float ClampAngle(float AngleDegrees, float MinAngleDegrees, float MaxAngleDegrees);

		/** Find the smallest angle between two headings (in degrees) * */
		static float FindDeltaAngleDegrees(const float a1, const float a2) {
			// Find the difference
			auto delta = a2 - a1;

			// If change is larger than 180
			if (delta > 180.0f) {
				// Flip to negative equivalent
				delta = delta - 360.0f;
			} else if (delta < -180.0f) {
				// Otherwise, if change is smaller than -180
				// Flip to positive equivalent
				delta = delta + 360.0f;
			}

			// Return delta in [-180,180] range
			return delta;
		}

		/** Find the smallest angle between two headings (in radians) * */
		static float FindDeltaAngleRadians(const float a1, const float a2) {
			// Find the difference
			auto delta = a2 - a1;

			// If change is larger than PI
			if (delta > PI) {
				// Flip to negative equivalent
				delta = delta - (PI * 2.0f);
			} else if (delta < -PI) {
				// Otherwise, if change is smaller than -PI
				// Flip to positive equivalent
				delta = delta + (PI * 2.0f);
			}

			// Return delta in [-PI,PI] range
			return delta;
		}

		/** Given a heading which may be outside the +/- PI range, 'unwind' it back into that range. * */
		static float UnwindRadians(float a) {
			while (a > PI) {
				a -= (static_cast<float>(PI) * 2.0f);
			}

			while (a < -PI) {
				a += (static_cast<float>(PI) * 2.0f);
			}

			return a;
		}

		/** Utility to ensure angle is between +/- 180 degrees by unwinding. * */
		static float UnwindDegrees(float a) {
			while (a > 180.f) {
				a -= 360.f;
			}

			while (a < -180.f) {
				a += 360.f;
			}

			return a;
		}

		/**
		 * Given two angles in degrees, 'wind' the rotation in Angle1 so that it avoids >180 degree flips.
		 * Good for winding rotations previously expressed as quaternions into a euler-angle representation.
		 * @param	InAngle0	The first angle that we wind relative to.
		 * @param	InOutAngle1	The second angle that we may wind relative to the first.
		 * */
		static void WindRelativeAnglesDegrees(float InAngle0, float& InOutAngle1);

		/** Returns a new rotation component value
		 *
		 * @param InCurrent is the current rotation value
		 * @param InDesired is the desired rotation value
		 * @param InDeltaRate is the rotation amount to apply
		 *
		 * @return a new rotation component value
		 * */
		static float FixedTurn(float InCurrent, float InDesired, float InDeltaRate);

		/** Converts given Cartesian coordinate pair to Polar coordinate system. * */
		static FORCEINLINE void CartesianToPolar(const float x, const float y, float& outRad, float& outAng) {
			outRad = Sqrt(Square(x) + Square(y));
			outAng = Atan2(y, x);
		}

		/** Converts given Cartesian coordinate pair to Polar coordinate system. * */
		static FORCEINLINE void CartesianToPolar(FVector2 InCart, FVector2& OutPolar);

		/** Converts given Polar coordinate pair to Cartesian coordinate system. * */
		static FORCEINLINE void PolarToCartesian(const float rad, const float ang, float& outX, float& outY) {
			outX = rad * Cos(ang);
			outY = rad * Sin(ang);
		}

		/** Converts given Polar coordinate pair to Cartesian coordinate system. * */
		static FORCEINLINE void PolarToCartesian(FVector2 InPolar, FVector2& OutCart);

		/**
		 * Calculates the dotted distance of vector 'Direction' to coordinate system O(AxisX,AxisY,AxisZ).
		 *
		 * Orientation: (consider 'O' the first person view of the player, and 'Direction' a vector pointing to an enemy)
		 * - positive azimuth means enemy is on the right of crosshair. (negative means left).
		 * - positive elevation means enemy is on top of crosshair, negative means below.
		 *
		 * @Note: 'Azimuth' (.X) sign is changed to represent left/right and not front/behind. front/behind is the funtion's return value.
		 *
		 * @param	OutDotDist	.X = 'Direction' dot AxisX relative to plane (AxisX,AxisZ). (== Cos(Azimuth))
		 *						.Y = 'Direction' dot AxisX relative to plane (AxisX,AxisY). (== Sin(Elevation))
		 * @param	Direction	direction of target.
		 * @param	AxisX		X component of reference system.
		 * @param	AxisY		Y component of reference system.
		 * @param	AxisZ		Z component of reference system.
		 *
		 * @return	true if 'Direction' is facing AxisX (Direction dot AxisX >= 0.f)
		 * */
		static bool GetDotDistance(FVector2& OutDotDist, const FVector3& Direction, const FVector3& AxisX, const FVector3& AxisY,
		                           const FVector3& AxisZ);

		/**
		 * Returns Azimuth and Elevation of vector 'Direction' in coordinate system O(AxisX,AxisY,AxisZ).
		 *
		 * Orientation: (consider 'O' the first person view of the player, and 'Direction' a vector pointing to an enemy)
		 * - positive azimuth means enemy is on the right of crosshair. (negative means left).
		 * - positive elevation means enemy is on top of crosshair, negative means below.
		 *
		 * @param	Direction		Direction of target.
		 * @param	AxisX			X component of reference system.
		 * @param	AxisY			Y component of reference system.
		 * @param	AxisZ			Z component of reference system.
		 *
		 * @return	FVector2	X = Azimuth angle (in radians) (-PI, +PI)
		 *						Y = Elevation angle (in radians) (-PI/2, +PI/2)
		 * */
		static FVector2 GetAzimuthAndElevation(const FVector3& Direction, const FVector3& AxisX, const FVector3& AxisY,
		                                       const FVector3& AxisZ);

		// Interpolation Functions

		/** Calculates the percentage along a line from MinValue to MaxValue that Value is. * */
		static FORCEINLINE float GetRangePct(const float minValue, const float maxValue, const float value) {
			// Avoid Divide by Zero.
			// But also if our range is a point, output whether Value is before or after.
			const auto Divisor = maxValue - minValue;
			if (IsNearlyZero(Divisor)) {
				return (value >= maxValue) ? 1.f : 0.f;
			}

			return (value - minValue) / Divisor;
		}

		/** Same as above, but taking a 2d vector as the range. * */
		static float GetRangePct(FVector2 const& Range, float Value);

		/** Basically a Vector2d version of Lerp. * */
		static float GetRangeValue(FVector2 const& Range, float Pct);

		/** For the given Value clamped to the [Input:Range] inclusive, returns the corresponding percentage in [Output:Range] Inclusive. * */
		static FORCEINLINE float
			GetMappedRangeValueClamped(const FVector2& inputRange, const FVector2& outputRange, const float value) {
			const auto clampedPct = Clamp<float>(GetRangePct(inputRange, value), 0.f, 1.f);
			return GetRangeValue(outputRange, clampedPct);
		}

		/** Transform the given Value relative to the input range to the Output Range. * */
		static FORCEINLINE float GetMappedRangeValueUnclamped(const FVector2& inputRange, const FVector2& outputRange, const float value) {
			return GetRangeValue(outputRange, GetRangePct(inputRange, value));
		}

		/** Performs a linear interpolation between two values, Alpha ranges from 0-1 * */
		template <class T, class U>
		static FORCEINLINE T Lerp(const T& a, const T& b, const U& alpha) {
			return static_cast<T>(a + alpha * (b - a));
		}

		/** Performs a linear interpolation between two values, Alpha ranges from 0-1. Handles full numeric range of T * */
		template <class T>
		static FORCEINLINE T LerpStable(const T& a, const T& b, double alpha) {
			return static_cast<T>((a * (1.0 - alpha)) + (b * alpha));
		}

		/** Performs a linear interpolation between two values, Alpha ranges from 0-1. Handles full numeric range of T * */
		template <class T>
		static FORCEINLINE T LerpStable(const T& a, const T& b, float alpha) {
			return static_cast<T>((a * (1.0f - alpha)) + (b * alpha));
		}

		/** Performs a 2D linear interpolation between four values values, FracX, FracY ranges from 0-1 * */
		template <class T, class U>
		static FORCEINLINE T BiLerp(const T& p00, const T& p10, const T& p01, const T& p11, const U& fracX, const U& fracY) {
			return Lerp(Lerp(p00, p10, fracX), Lerp(p01, p11, fracX), fracY);
		}

		/**
		 * Performs a cubic interpolation
		 *
		 * @param  p0 - end points
		 * @param  p1 - end points
		 * @param  t0 - tangent directions at end points
		 * @param  t1 - tangent directions at end points
		 * @param  a  - distance along spline
		 *
		 * @return  Interpolated value
		 * */
		template <class T, class U>
		static FORCEINLINE T CubicInterp(const T& p0, const T& t0, const T& p1, const T& t1, const U& a) {
			const float a2 = a * a;
			const float a3 = a2 * a;

			return static_cast<T>(((2 * a3) - (3 * a2) + 1) * p0) + ((a3 - (2 * a2) + a) * t0) + ((a3 - a2) * t1) + (((-2 * a3) + (3 * a2))
				* p1);
		}

		/**
		 * Performs a first derivative cubic interpolation
		 *
		 * @param  p0	- end points
		 * @param  p1	- end points
		 * @param  t0	- tangent directions at end points
		 * @param  t1	- tangent directions at end points
		 * @param  dis  - distance along spline
		 *
		 * @return  Interpolated value
		 * */
		template <class T, class U>
		static FORCEINLINE T CubicInterpDerivative(const T& p0, const T& t0, const T& p1, const T& t1, const U& dis) {
			T a = 6.f * p0 + 3.f * t0 + 3.f * t1 - 6.f * p1;
			T b = -6.f * p0 - 4.f * t0 - 2.f * t1 + 6.f * p1;
			T c = t0;

			const float a2 = dis * dis;

			return (a * a2) + (b * dis) + c;
		}

		/**
		 * Performs a second derivative cubic interpolation
		 *
		 * @param  p0	- end points
		 * @param  p1	- end points
		 * @param  t0	- tangent directions at end points
		 * @param  t1	- tangent directions at end points
		 * @param  dis  - distance along spline
		 *
		 * @return  Interpolated value
		 * */
		template <class T, class U>
		static FORCEINLINE T CubicInterpSecondDerivative(const T& p0, const T& t0, const T& p1, const T& t1, const U& dis) {
			T a = 12.f * p0 + 6.f * t0 + 6.f * t1 - 12.f * p1;
			T b = -6.f * p0 - 4.f * t0 - 2.f * t1 + 6.f * p1;

			return (a * dis) + b;
		}

		/** Interpolate between A and B, applying an ease in function.  Exp controls the degree of the curve. * */
		template <class T>
		static FORCEINLINE T InterpEaseIn(const T& a, const T& b, const float alpha, const float exp) {
			auto const modifiedAlpha = Pow(alpha, exp);
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolate between A and B, applying an ease out function.  Exp controls the degree of the curve. * */
		template <class T>
		static FORCEINLINE T InterpEaseOut(const T& a, const T& b, const float alpha, const float exp) {
			auto const modifiedAlpha = 1.f - Pow(1.f - alpha, exp);
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolate between A and B, applying an ease in/out function.  Exp controls the degree of the curve. * */
		template <class T>
		static FORCEINLINE T InterpEaseInOut(const T& a, const T& b, const float alpha, const float exp) {
			return Lerp<T>(a, b, (alpha < 0.5f)
				                     ? InterpEaseIn(0.f, 1.f, alpha * 2.f, exp) * 0.5f
				                     : InterpEaseOut(0.f, 1.f, alpha * 2.f - 1.f, exp) * 0.5f + 0.5f);
		}

		/** Interpolation between A and B, applying a step function. * */
		template <class T>
		static FORCEINLINE T InterpStep(const T& a, const T& b, const float alpha, const int32 steps) {
			if (steps <= 1 || alpha <= 0) {
				return a;
			}
			if (alpha >= 1) {
				return b;
			}

			const auto stepsAsFloat = static_cast<float>(steps);
			const auto numIntervals = stepsAsFloat - 1.f;
			auto const modifiedAlpha = FloorToFloat(alpha * stepsAsFloat) / numIntervals;
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying a sinusoidal in function. * */
		template <class T>
		static FORCEINLINE T InterpSinIn(const T& a, const T& b, const float alpha) {
			auto const modifiedAlpha = -1.f * Cos(alpha * HALF_PI) + 1.f;
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying a sinusoidal out function. * */
		template <class T>
		static FORCEINLINE T InterpSinOut(const T& a, const T& b, const float alpha) {
			auto const modifiedAlpha = Sin(alpha * HALF_PI);
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying a sinusoidal in/out function. * */
		template <class T>
		static FORCEINLINE T InterpSinInOut(const T& a, const T& b, const float alpha) {
			return Lerp<T>(a, b, (alpha < 0.5f)
				                     ? InterpSinIn(0.f, 1.f, alpha * 2.f) * 0.5f
				                     : InterpSinOut(0.f, 1.f, alpha * 2.f - 1.f) * 0.5f + 0.5f);
		}

		/** Interpolation between A and B, applying an exponential in function. * */
		template <class T>
		static FORCEINLINE T InterpExpoIn(const T& a, const T& b, const float alpha) {
			auto const modifiedAlpha = (alpha == 0.f) ? 0.f : Pow(2.f, 10.f * (alpha - 1.f));
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying an exponential out function. * */
		template <class T>
		static FORCEINLINE T InterpExpoOut(const T& a, const T& b, const float alpha) {
			auto const modifiedAlpha = (alpha == 1.f) ? 1.f : -Pow(2.f, -10.f * alpha) + 1.f;
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying an exponential in/out function. * */
		template <class T>
		static FORCEINLINE T InterpExpoInOut(const T& a, const T& b, const float alpha) {
			return Lerp<T>(a, b, (alpha < 0.5f)
				                     ? InterpExpoIn(0.f, 1.f, alpha * 2.f) * 0.5f
				                     : InterpExpoOut(0.f, 1.f, alpha * 2.f - 1.f) * 0.5f + 0.5f);
		}

		/** Interpolation between A and B, applying a circular in function. * */
		template <class T>
		static FORCEINLINE T InterpCircularIn(const T& a, const T& b, const float alpha) {
			auto const modifiedAlpha = -1.f * (Sqrt(1.f - alpha * alpha) - 1.f);
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying a circular out function. * */
		template <class T>
		static FORCEINLINE T InterpCircularOut(const T& a, const T& b, float alpha) {
			alpha -= 1.f;
			auto const modifiedAlpha = Sqrt(1.f - alpha * alpha);
			return Lerp<T>(a, b, modifiedAlpha);
		}

		/** Interpolation between A and B, applying a circular in/out function. * */
		template <class T>
		static FORCEINLINE T InterpCircularInOut(const T& a, const T& b, const float alpha) {
			return Lerp<T>(a, b, (alpha < 0.5f)
				                     ? InterpCircularIn(0.f, 1.f, alpha * 2.f) * 0.5f
				                     : InterpCircularOut(0.f, 1.f, alpha * 2.f - 1.f) * 0.5f + 0.5f);
		}

		// Rotator specific interpolation
		template <class U>
		static FRotator Lerp(const FRotator& A, const FRotator& B, const U& Alpha);
		template <class U>
		static FRotator LerpRange(const FRotator& A, const FRotator& B, const U& Alpha);

		// Quat-specific interpolation

		template <class U>
		static FQuat Lerp(const FQuat& A, const FQuat& B, const U& Alpha);
		template <class U>
		static FQuat BiLerp(const FQuat& P00, const FQuat& P10, const FQuat& P01, const FQuat& P11, float FracX, float FracY);

		/**
		 * In the case of quaternions, we use a bezier like approach.
		 * T - Actual 'control' orientations.
		 * */
		template <class U>
		static FQuat CubicInterp(const FQuat& P0, const FQuat& T0, const FQuat& P1, const FQuat& T1, const U& A);

		/*
		 *	Cubic Catmull-Rom Spline interpolation. Based on http://www.cemyuksel.com/research/catmullrom_param/catmullrom.pdf
		 *	Curves are guaranteed to pass through the control points and are easily chained together.
		 *	Equation supports abitrary parameterization. eg. Uniform=0,1,2,3 ; chordal= |Pn - Pn-1| ; centripetal = |Pn - Pn-1|^0.5
		 *	P0 - The control point preceding the interpolation range.
		 *	P1 - The control point starting the interpolation range.
		 *	P2 - The control point ending the interpolation range.
		 *	P3 - The control point following the interpolation range.
		 *	T0-3 - The interpolation parameters for the corresponding control points.
		 *	T - The interpolation factor in the range 0 to 1. 0 returns P1. 1 returns P2.
		 * */
		template <class U>
		static FORCEINLINE U CubicCRSplineInterp(const U& p0, const U& p1, const U& p2, const U& p3, const float t0,
		                                         const float t1, const float t2, const float t3, const float t) {
			//Based on http://www.cemyuksel.com/research/catmullrom_param/catmullrom.pdf 
			const auto invT1MinusT0 = 1.0f / (t1 - t0);
			U l01 = (p0 * ((t1 - t) * invT1MinusT0)) + (p1 * ((t - t0) * invT1MinusT0));
			const auto invT2MinusT1 = 1.0f / (t2 - t1);
			U l12 = (p1 * ((t2 - t) * invT2MinusT1)) + (p2 * ((t - t1) * invT2MinusT1));
			const auto invT3MinusT2 = 1.0f / (t3 - t2);
			U l23 = (p2 * ((t3 - t) * invT3MinusT2)) + (p3 * ((t - t2) * invT3MinusT2));

			const auto invT2MinusT0 = 1.0f / (t2 - t0);
			U l012 = (l01 * ((t2 - t) * invT2MinusT0)) + (l12 * ((t - t0) * invT2MinusT0));
			const auto invT3MinusT1 = 1.0f / (t3 - t1);
			U l123 = (l12 * ((t3 - t) * invT3MinusT1)) + (l23 * ((t - t1) * invT3MinusT1));

			return ((l012 * ((t2 - t) * invT2MinusT1)) + (l123 * ((t - t1) * invT2MinusT1)));
		}

		/* Same as CubicCRSplineInterp but with additional saftey checks. If the checks fail P1 is returned. ** */
		template <class U>
		static FORCEINLINE U CubicCRSplineInterpSafe(const U& p0, const U& p1, const U& p2, const U& p3, const float t0,
		                                             const float t1, const float t2, const float t3, const float t) {
			//Based on http://www.cemyuksel.com/research/catmullrom_param/catmullrom.pdf 
			const auto t1MinusT0 = (t1 - t0);
			const auto t2MinusT1 = (t2 - t1);
			const auto t3MinusT2 = (t3 - t2);
			const auto t2MinusT0 = (t2 - t0);
			const auto t3MinusT1 = (t3 - t1);
			if (IsNearlyZero(t1MinusT0) || IsNearlyZero(t2MinusT1) || IsNearlyZero(t3MinusT2) ||
				IsNearlyZero(t2MinusT0) || IsNearlyZero(t3MinusT1)) {
				//There's going to be a divide by zero here so just bail out and return P1
				return p1;
			}

			auto InvT1MinusT0 = 1.0f / t1MinusT0;
			const auto invT1MinusT0 = 1.0f / (t1 - t0);
			U l01 = (p0 * ((t1 - t) * invT1MinusT0)) + (p1 * ((t - t0) * invT1MinusT0));
			const auto invT2MinusT1 = 1.0f / (t2 - t1);
			U l12 = (p1 * ((t2 - t) * invT2MinusT1)) + (p2 * ((t - t1) * invT2MinusT1));
			const auto invT3MinusT2 = 1.0f / (t3 - t2);
			U l23 = (p2 * ((t3 - t) * invT3MinusT2)) + (p3 * ((t - t2) * invT3MinusT2));

			const auto invT2MinusT0 = 1.0f / (t2 - t0);
			U l012 = (l01 * ((t2 - t) * invT2MinusT0)) + (l12 * ((t - t0) * invT2MinusT0));
			const auto invT3MinusT1 = 1.0f / (t3 - t1);
			U l123 = (l12 * ((t3 - t) * invT3MinusT1)) + (l23 * ((t - t1) * invT3MinusT1));

			return ((l012 * ((t2 - t) * invT2MinusT1)) + (l123 * ((t - t1) * invT2MinusT1)));
		}


		// Special-case interpolation

		/** Interpolate a normal vector Current to Target, by interpolating the angle between those vectors with constant step. * */
		static FVector3 VInterpNormalRotationTo(const FVector3& Current, const FVector3& Target, float DeltaTime,
		                                        float RotationSpeedDegrees);

		/** Interpolate vector from Current to Target with constant step * */
		static FVector3 VInterpConstantTo(const FVector3& Current, const FVector3& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate vector from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. * */
		static FVector3 VInterpTo(const FVector3& Current, const FVector3& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate vector2D from Current to Target with constant step * */
		static FVector2 Vector2DInterpConstantTo(const FVector2& Current, const FVector2& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate vector2D from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. * */
		static FVector2 Vector2DInterpTo(const FVector2& Current, const FVector2& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate rotator from Current to Target with constant step * */
		static FRotator RInterpConstantTo(const FRotator& Current, const FRotator& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate rotator from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. * */
		static FRotator RInterpTo(const FRotator& Current, const FRotator& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate float from Current to Target with constant step * */
		static float FInterpConstantTo(float Current, float Target, float DeltaTime, float InterpSpeed);

		/** Interpolate float from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. * */
		static float FInterpTo(float Current, float Target, float DeltaTime, float InterpSpeed);

		/** Interpolate Linear Color from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. * */
		static FLinearColor CInterpTo(const FLinearColor& Current, const FLinearColor& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate quaternion from Current to Target with constant step (in radians) * */
		static FQuat QInterpConstantTo(const FQuat& Current, const FQuat& Target, float DeltaTime, float InterpSpeed);

		/** Interpolate quaternion from Current to Target. Scaled by angle to Target, so it has a strong start speed and ease out. * */
		static FQuat QInterpTo(const FQuat& Current, const FQuat& Target, float DeltaTime, float InterpSpeed);

		/**
		 * Simple function to create a pulsating scalar value
		 *
		 * @param  inCurrentTime  Current absolute time
		 * @param  inPulsesPerSecond  How many full pulses per second?
		 * @param  inPhase  Optional phase amount, between 0.0 and 1.0 (to synchronize pulses)
		 *
		 * @return  Pulsating value (0.0-1.0)
		 * */
		static float MakePulsatingValue(const double inCurrentTime, const float inPulsesPerSecond, const float inPhase = 0.0f) {
			return 0.5f + 0.5f * Sin(((0.25f + inPhase) * PI * 2.0) + (inCurrentTime * PI * 2.0) * inPulsesPerSecond);
		}

		// Geometry intersection 

		/**
		 * Find the intersection of a ray and a plane.  The ray has a start point with an infinite length.  Assumes that the
		 * line and plane do indeed intersect; you must make sure they're not parallel before calling.
		 *
		 * @param RayOrigin	The start point of the ray
		 * @param RayDirection	The direction the ray is pointing (normalized vector)
		 * @param Plane	The plane to intersect with
		 *
		 * @return The point of intersection between the ray and the plane.
		 * */
		static FVector3 RayPlaneIntersection(const FVector3& RayOrigin, const FVector3& RayDirection, const FPlane& Plane);

		/**
		 * Find the intersection of a line and an offset plane. Assumes that the
		 * line and plane do indeed intersect; you must make sure they're not
		 * parallel before calling.
		 *
		 * @param Point1 the first point defining the line
		 * @param Point2 the second point defining the line
		 * @param PlaneOrigin the origin of the plane
		 * @param PlaneNormal the normal of the plane
		 *
		 * @return The point of intersection between the line and the plane.
		 * */
		static FVector3 LinePlaneIntersection(const FVector3& Point1, const FVector3& Point2, const FVector3& PlaneOrigin,
		                                      const FVector3& PlaneNormal);

		/**
		 * Find the intersection of a line and a plane. Assumes that the line and
		 * plane do indeed intersect; you must make sure they're not parallel before
		 * calling.
		 *
		 * @param Point1 the first point defining the line
		 * @param Point2 the second point defining the line
		 * @param Plane the plane
		 *
		 * @return The point of intersection between the line and the plane.
		 * */
		static FVector3 LinePlaneIntersection(const FVector3& Point1, const FVector3& Point2, const FPlane& Plane);


		// @parma InOutScissorRect should be set to View.ViewRect before the call
		// @return 0: light is not visible, 1:use scissor rect, 2: no scissor rect needed
		static uint32 ComputeProjectedSphereScissorRect(struct FIntRect& InOutScissorRect, FVector3 SphereOrigin, float Radius,
		                                                FVector3 ViewOrigin, const FMatrix& ViewMatrix, const FMatrix& ProjMatrix);

		// @param ConeOrigin Cone origin
		// @param ConeDirection Cone direction
		// @param ConeRadius Cone Radius
		// @param CosConeAngle Cos of the cone angle
		// @param SinConeAngle Sin of the cone angle
		// @return Minimal bounding sphere encompassing given cone
		static FSphere ComputeBoundingSphereForCone(FVector3 const& ConeOrigin, FVector3 const& ConeDirection, float ConeRadius,
		                                            float CosConeAngle, float SinConeAngle);

		/**
		 * Determine if a plane and an AABB intersect
		 * @param P - the plane to test
		 * @param AABB - the axis aligned bounding box to test
		 * @return if collision occurs
		 * */
		static bool PlaneAABBIntersection(const FPlane& P, const FBox& AABB);

		/**
		 * Determine the position of an AABB relative to a plane:
		 * completely above (in the direction of the normal of the plane), completely below or intersects it
		 * @param P - the plane to test
		 * @param AABB - the axis aligned bounding box to test
		 * @return -1 if below, 1 if above, 0 if intersects
		 * */
		static int32 PlaneAABBRelativePosition(const FPlane& P, const FBox& AABB);

		/**
		 * Performs a sphere vs box intersection test using Arvo's algorithm:
		 *
		 *	for each i in (x, y, z)
		 *		if (SphereCenter(i) < BoxMin(i)) d2 += (SphereCenter(i) - BoxMin(i)) ^ 2
		 *		else if (SphereCenter(i) > BoxMax(i)) d2 += (SphereCenter(i) - BoxMax(i)) ^ 2
		 *
		 * @param Sphere the center of the sphere being tested against the AABB
		 * @param RadiusSquared the size of the sphere being tested
		 * @param AABB the box being tested against
		 *
		 * @return Whether the sphere/box intersect or not.
		 * */
		static bool SphereAABBIntersection(const FVector3& SphereCenter, float RadiusSquared, const FBox& AABB);

		/**
		 * Converts a sphere into a point plus radius squared for the test above
		 * */
		static bool SphereAABBIntersection(const FSphere& Sphere, const FBox& AABB);

		/** Determines whether a point is inside a box. * */
		static bool PointBoxIntersection(const FVector3& Point, const FBox& Box);

		/** Determines whether a line intersects a box. * */
		static bool LineBoxIntersection(const FBox& Box, const FVector3& Start, const FVector3& End, const FVector3& Direction);

		/** Determines whether a line intersects a box. This overload avoids the need to do the reciprocal every time. * */
		static bool LineBoxIntersection(const FBox& Box, const FVector3& Start, const FVector3& End, const FVector3& Direction,
		                                const FVector3& OneOverDirection);

		/* Swept-Box vs Box test * */
		static bool LineExtentBoxIntersection(const FBox& inBox, const FVector3& Start, const FVector3& End, const FVector3& Extent,
		                                      FVector3& HitLocation, FVector3& HitNormal, float& HitTime);

		/** Determines whether a line intersects a sphere. * */
		static bool LineSphereIntersection(const FVector3& Start, const FVector3& Dir, float Length, const FVector3& Origin, float Radius);

		/**
		 * Assumes the cone tip is at 0,0,0 (means the SphereCenter is relative to the cone tip)
		 * @return true: cone and sphere do intersect, false otherwise
		 * */
		static bool SphereConeIntersection(const FVector3& SphereCenter, float SphereRadius, const FVector3& ConeAxis, float ConeAngleSin,
		                                   float ConeAngleCos);

		/** Find the point on the line segment from LineStart to LineEnd which is closest to Point * */
		static FVector3 ClosestPointOnLine(const FVector3& lineStart, const FVector3& lineEnd, const FVector3& point);

		/** Find the point on the infinite line between two points (LineStart, LineEnd) which is closest to Point * */
		static FVector3 ClosestPointOnInfiniteLine(const FVector3& lineStart, const FVector3& lineEnd, const FVector3& point);

		/** Compute intersection point of three planes. Return 1 if valid, 0 if infinite. * */
		static bool IntersectPlanes3(FVector3& I, const FPlane& P1, const FPlane& P2, const FPlane& P3);

		/**
		 * Compute intersection point and direction of line joining two planes.
		 * Return 1 if valid, 0 if infinite.
		 * */
		static bool IntersectPlanes2(FVector3& I, FVector3& D, const FPlane& P1, const FPlane& P2);

		/**
		 * Calculates the distance of a given Point in world space to a given line,
		 * defined by the vector couple (Origin, Direction).
		 *
		 * @param	Point				Point to check distance to line
		 * @param	Direction			Vector indicating the direction of the line. Not required to be normalized.
		 * @param	Origin				Point of reference used to calculate distance
		 * @param	OutClosestPoint	optional point that represents the closest point projected onto Axis
		 *
		 * @return	distance of Point from line defined by (Origin, Direction)
		 * */
		static float PointDistToLine(const FVector3& Point, const FVector3& Direction, const FVector3& Origin, FVector3& OutClosestPoint);
		static float PointDistToLine(const FVector3& Point, const FVector3& Direction, const FVector3& Origin);

		/**
		 * Returns closest point on a segment to a given point.
		 * The idea is to project point on line formed by segment.
		 * Then we see if the closest point on the line is outside of segment or inside.
		 *
		 * @param	Point			point for which we find the closest point on the segment
		 * @param	StartPoint		StartPoint of segment
		 * @param	EndPoint		EndPoint of segment
		 *
		 * @return	point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
		 * */
		static FVector3 ClosestPointOnSegment(const FVector3& Point, const FVector3& StartPoint, const FVector3& EndPoint);

		/**
		* FVector2 version of ClosestPointOnSegment.
		* Returns closest point on a segment to a given 2D point.
		* The idea is to project point on line formed by segment.
		* Then we see if the closest point on the line is outside of segment or inside.
		*
		* @param	Point			point for which we find the closest point on the segment
		* @param	StartPoint		StartPoint of segment
		* @param	EndPoint		EndPoint of segment
		*
		* @return	point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
		* */
		static FVector2 ClosestPointOnSegment2D(const FVector2& Point, const FVector2& StartPoint, const FVector2& EndPoint);

		/**
		 * Returns distance from a point to the closest point on a segment.
		 *
		 * @param	Point			point to check distance for
		 * @param	StartPoint		StartPoint of segment
		 * @param	EndPoint		EndPoint of segment
		 *
		 * @return	closest distance from Point to segment defined by (StartPoint, EndPoint).
		 * */
		static float PointDistToSegment(const FVector3& Point, const FVector3& StartPoint, const FVector3& EndPoint);

		/**
		 * Returns square of the distance from a point to the closest point on a segment.
		 *
		 * @param	Point			point to check distance for
		 * @param	StartPoint		StartPoint of segment
		 * @param	EndPoint		EndPoint of segment
		 *
		 * @return	square of the closest distance from Point to segment defined by (StartPoint, EndPoint).
		 * */
		static float PointDistToSegmentSquared(const FVector3& Point, const FVector3& StartPoint, const FVector3& EndPoint);

		/**
		 * Find closest points between 2 segments.
		 *
		 * If either segment may have a length of 0, use SegmentDistToSegmentSafe instance.
		 *
		 * @param	(A1, B1)	defines the first segment.
		 * @param	(A2, B2)	defines the second segment.
		 * @param	OutP1		Closest point on segment 1 to segment 2.
		 * @param	OutP2		Closest point on segment 2 to segment 1.
		 * */
		static void SegmentDistToSegment(FVector3 A1, FVector3 B1, FVector3 A2, FVector3 B2, FVector3& OutP1, FVector3& OutP2);

		/**
		 * Find closest points between 2 segments.
		 *
		 * This is the safe version, and will check both segments' lengths.
		 * Use this if either (or both) of the segments lengths may be 0.
		 *
		 * @param	(A1, B1)	defines the first segment.
		 * @param	(A2, B2)	defines the second segment.
		 * @param	OutP1		Closest point on segment 1 to segment 2.
		 * @param	OutP2		Closest point on segment 2 to segment 1.
		 * */
		static void SegmentDistToSegmentSafe(FVector3 A1, FVector3 B1, FVector3 A2, FVector3 B2, FVector3& OutP1, FVector3& OutP2);

		/**
		 * returns the time (t) of the intersection of the passed segment and a plane (could be <0 or >1)
		 * @param StartPoint - start point of segment
		 * @param EndPoint   - end point of segment
		 * @param Plane		- plane to intersect with
		 * @return time(T) of intersection
		 * */
		static float GetTForSegmentPlaneIntersect(const FVector3& StartPoint, const FVector3& EndPoint, const FPlane& Plane);

		/**
		 * Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		 * the plane on which polygon Plane lies. If there is an intersection, the point is placed in out_IntersectionPoint
		 * @param StartPoint - start point of segment
		 * @param EndPoint   - end point of segment
		 * @param Plane		- plane to intersect with
		 * @param out_IntersectionPoint - out var for the point on the segment that intersects the mesh (if any)
		 * @return true if intersection occurred
		 * */
		static bool SegmentPlaneIntersection(const FVector3& StartPoint, const FVector3& EndPoint, const FPlane& Plane,
		                                     FVector3& out_IntersectionPoint);


		/**
		* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
		* the Triangle defined by A, B and C. If there is an intersection, the point is placed in out_IntersectionPoint
		* @param StartPoint - start point of segment
		* @param EndPoint   - end point of segment
		* @param A, B, C	- points defining the triangle
		* @param OutIntersectPoint - out var for the point on the segment that intersects the triangle (if any)
		* @param OutNormal - out var for the triangle normal
		* @return true if intersection occurred
		* */
		static bool SegmentTriangleIntersection(const FVector3& StartPoint, const FVector3& EndPoint, const FVector3& A, const FVector3& B,
		                                        const FVector3& C, FVector3& OutIntersectPoint, FVector3& OutTriangleNormal);

		/**
		 * Returns true if there is an intersection between the segment specified by SegmentStartA and SegmentEndA, and
		 * the segment specified by SegmentStartB and SegmentEndB, in 2D space. If there is an intersection, the point is placed in out_IntersectionPoint
		 * @param SegmentStartA - start point of first segment
		 * @param SegmentEndA   - end point of first segment
		 * @param SegmentStartB - start point of second segment
		 * @param SegmentEndB   - end point of second segment
		 * @param outIntersectionPoint - out var for the intersection point (if any)
		 * @return true if intersection occurred
		 * */
		static bool SegmentIntersection2D(const FVector3& SegmentStartA, const FVector3& SegmentEndA, const FVector3& SegmentStartB,
		                                  const FVector3& SegmentEndB, FVector3& outIntersectionPoint);


		/**
		 * Returns closest point on a triangle to a point.
		 * The idea is to identify the halfplanes that the point is
		 * in relative to each triangle segment "plane"
		 *
		 * @param	Point			point to check distance for
		 * @param	A,B,C			counter clockwise ordering of points defining a triangle
		 *
		 * @return	Point on triangle ABC closest to given point
		 * */
		static FVector3 ClosestPointOnTriangleToPoint(const FVector3& Point, const FVector3& A, const FVector3& B, const FVector3& C);

		/**
		 * Returns closest point on a tetrahedron to a point.
		 * The idea is to identify the halfplanes that the point is
		 * in relative to each face of the tetrahedron
		 *
		 * @param	Point			point to check distance for
		 * @param	A,B,C,D			four points defining a tetrahedron
		 *
		 * @return	Point on tetrahedron ABCD closest to given point
		 * */
		static FVector3 ClosestPointOnTetrahedronToPoint(const FVector3& Point, const FVector3& A, const FVector3& B, const FVector3& C,
		                                                 const FVector3& D);

		/**
		 * Find closest point on a Sphere to a Line.
		 * When line intersects		Sphere, then closest point to LineOrigin is returned.
		 * @param SphereOrigin		Origin of Sphere
		 * @param SphereRadius		Radius of Sphere
		 * @param LineOrigin		Origin of line
		 * @param LineDir			Direction of line. Needs to be normalized!!
		 * @param OutClosestPoint	Closest point on sphere to given line.
		 * */
		static void SphereDistToLine(FVector3 SphereOrigin, float SphereRadius, FVector3 LineOrigin, FVector3 LineDir,
		                             FVector3& OutClosestPoint);

		/**
		 * Calculates whether a Point is within a cone segment, and also what percentage within the cone (100% is along the center line, whereas 0% is along the edge)
		 *
		 * @param Point - The Point in question
		 * @param ConeStartPoint - the beginning of the cone (with the smallest radius)
		 * @param ConeLine - the line out from the start point that ends at the largest radius point of the cone
		 * @param radiusAtStart - the radius at the ConeStartPoint (0 for a 'proper' cone)
		 * @param radiusAtEnd - the largest radius of the cone
		 * @param percentageOut - output variable the holds how much within the cone the point is (1 = on center line, 0 = on exact edge or outside cone).
		 *
		 * @return true if the point is within the cone, false otherwise.
		 * */
		static bool GetDistanceWithinConeSegment(FVector3 Point, FVector3 ConeStartPoint, FVector3 ConeLine, float RadiusAtStart,
		                                         float RadiusAtEnd, float& PercentageOut);

		/**
		 * Determines whether a given set of points are coplanar, with a tolerance. Any three points or less are always coplanar.
		 *
		 * @param Points - The set of points to determine coplanarity for.
		 * @param Tolerance - Larger numbers means more variance is allowed.
		 *
		 * @return Whether the points are relatively coplanar, based on the tolerance
		 * */
		static bool PointsAreCoplanar(const Types::TArray<FVector3>& Points, float Tolerance = 0.1f);

		/**
		 * Truncates a floating point number to half if closer than the given tolerance.
		 * @param Value				Floating point number to truncate
		 * @param Tolerance			Maximum allowed difference to 0.5 in order to truncate
		 * @return					The truncated value
		 * */
		static float TruncateToHalfIfClose(float F, float Tolerance = SMALL_NUMBER);
		static double TruncateToHalfIfClose(double F, double Tolerance = SMALL_NUMBER);

		/**
		* Converts a floating point number to the nearest integer, equidistant ties go to the value which is closest to an even value: 1.5 becomes 2, 0.5 becomes 0
		* @param F		Floating point value to convert
		* @return		The rounded integer
		* */
		static float RoundHalfToEven(float F);
		static double RoundHalfToEven(double F);

		/**
		* Converts a floating point number to the nearest integer, equidistant ties go to the value which is further from zero: -0.5 becomes -1.0, 0.5 becomes 1.0
		* @param F		Floating point value to convert
		* @return		The rounded integer
		* */
		static float RoundHalfFromZero(float F);
		static double RoundHalfFromZero(double F);

		/**
		* Converts a floating point number to the nearest integer, equidistant ties go to the value which is closer to zero: -0.5 becomes 0, 0.5 becomes 0
		* @param F		Floating point value to convert
		* @return		The rounded integer
		* */
		static float RoundHalfToZero(float F);
		static double RoundHalfToZero(double F);

		/**
		* Converts a floating point number to an integer which is further from zero, "larger" in absolute value: 0.1 becomes 1, -0.1 becomes -1
		* @param f		Floating point value to convert
		* @return		The rounded integer
		* */
		static FORCEINLINE float RoundFromZero(const float f) {
			return (f < 0.0f) ? FloorToFloat(f) : CeilToFloat(f);
		}

		static FORCEINLINE double RoundFromZero(const double f) {
			return (f < 0.0) ? FloorToDouble(f) : CeilToDouble(f);
		}

		/**
		* Converts a floating point number to an integer which is closer to zero, "smaller" in absolute value: 0.1 becomes 0, -0.1 becomes 0
		* @param f		Floating point value to convert
		* @return		The rounded integer
		* */
		static FORCEINLINE float RoundToZero(const float f) {
			return (f < 0.0f) ? CeilToFloat(f) : FloorToFloat(f);
		}

		static FORCEINLINE double RoundToZero(const double f) {
			return (f < 0.0) ? CeilToDouble(f) : FloorToDouble(f);
		}

		/**
		* Converts a floating point number to an integer which is more negative: 0.1 becomes 0, -0.1 becomes -1
		* @param f		Floating point value to convert
		* @return		The rounded integer
		* */
		static FORCEINLINE float RoundToNegativeInfinity(const float f) {
			return FloorToFloat(f);
		}

		static FORCEINLINE double RoundToNegativeInfinity(const double f) {
			return FloorToDouble(f);
		}

		/**
		* Converts a floating point number to an integer which is more positive: 0.1 becomes 1, -0.1 becomes 0
		* @param f		Floating point value to convert
		* @return		The rounded integer
		* */
		static FORCEINLINE float RoundToPositiveInfinity(const float f) {
			return CeilToFloat(f);
		}

		static FORCEINLINE double RoundToPositiveInfinity(const double f) {
			return CeilToDouble(f);
		}


		// Formatting functions

		/**
		 * Formats an integer value into a human readable string (i.e. 12345 becomes "12,345")
		 *
		 * @param	Val		The value to use
		 * @return	FString	The human readable string
		 * */
		static Types::FString FormatIntToHumanReadable(int32 Val);


		// Utilities

		/**
		 * Tests a memory region to see that it's working properly.
		 *
		 * @param BaseAddress	Starting address
		 * @param NumBytes		Number of bytes to test (will be rounded down to a multiple of 4)
		 * @return				true if the memory region passed the test
		 * */
		static bool MemoryTest(void* BaseAddress, uint32 NumBytes);

		/**
		 * Evaluates a numerical equation.
		 *
		 * Operators and precedence: 1:+- 2:/% 3:* 4:^ 5:&|
		 * Unary: -
		 * Types: Numbers (0-9.), Hex ($0-$f)
		 * Grouping: ( )
		 *
		 * @param	Str			String containing the equation.
		 * @param	OutValue		Pointer to storage for the result.
		 * @return				1 if successful, 0 if equation fails.
		 * */
		static bool Eval(Types::FString Str, float& OutValue);

		/**
		 * Computes the barycentric coordinates for a given point in a triangle - simpler version
		 *
		 * @param	Point			point to convert to barycentric coordinates (in plane of ABC)
		 * @param	A,B,C			three non-colinear points defining a triangle in CCW
		 *
		 * @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
		 *							                                or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
		 * */
		static FVector3 GetBaryCentric2D(const FVector3& Point, const FVector3& A, const FVector3& B, const FVector3& C);

		/**
		 * Computes the barycentric coordinates for a given point in a triangle
		 *
		 * @param	Point			point to convert to barycentric coordinates (in plane of ABC)
		 * @param	A,B,C			three non-collinear points defining a triangle in CCW
		 *
		 * @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
		 *							                               or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
		 * */
		static FVector3 ComputeBaryCentric2D(const FVector3& Point, const FVector3& A, const FVector3& B, const FVector3& C);

		/**
		 * Computes the barycentric coordinates for a given point on a tetrahedron (3D)
		 *
		 * @param	Point			point to convert to barycentric coordinates
		 * @param	A,B,C,D			four points defining a tetrahedron
		 *
		 * @return Vector containing the four weights a,b,c,d such that Point = a*A + b*B + c*C + d*D
		 * */
		static FVector4 ComputeBaryCentric3D(const FVector3& Point, const FVector3& A, const FVector3& B, const FVector3& C,
		                                     const FVector3& D);

		/** 32 bit values where BitFlag[x] == (1<<x) * */
		static const uint32 BitFlag[32];

		/**
		 * Returns a smooth Hermite interpolation between 0 and 1 for the value X (where X ranges between A and B)
		 * Clamped to 0 for X <= A and 1 for X >= B.
		 *
		 * @param a Minimum value of X
		 * @param b Maximum value of X
		 * @param x Parameter
		 *
		 * @return Smoothed value between 0 and 1
		 * */
		static float SmoothStep(const float a, const float b, const float x) {
			if (x < a) {
				return 0.0f;
			} else if (x >= b) {
				return 1.0f;
			}
			const auto InterpFraction = (x - a) / (b - a);
			return InterpFraction * InterpFraction * (3.0f - 2.0f * InterpFraction);
		}

		/**
		 * Get a bit in memory created from bitflags (uint32 Value:1), used for EngineShowFlags,
		 * TestBitFieldFunctions() tests the implementation
		 * */
		static bool ExtractBoolFromBitfield(uint8* ptr, const uint32 index) {
			auto* const bytePtr = ptr + index / 8;
			const uint8 mask = 1 << (index & 0x7);

			return (*bytePtr & mask) != 0;
		}

		/**
		 * Set a bit in memory created from bitflags (uint32 Value:1), used for EngineShowFlags,
		 * TestBitFieldFunctions() tests the implementation
		 * */
		static void SetBoolInBitField(uint8* ptr, const uint32 index, const bool bSet) {
			const auto bytePtr = ptr + index / 8;
			const uint8 mask = 1 << (index & 0x7);

			if (bSet) {
				*bytePtr |= mask;
			} else {
				*bytePtr &= ~mask;
			}
		}

		/**
		 * Handy to apply scaling in the editor
		 * @param Dst in and out
		 * */
		static void ApplyScaleToFloat(float& Dst, const FVector3& DeltaScale, float Magnitude = 1.0f);

		// @param x assumed to be in this range: 0..1
		// @return 0..255
		static uint8 Quantize8UnsignedByte(const float x) {
			// 0..1 -> 0..255
			const auto ret = static_cast<int32>(x * 255.999f);

			if (ret < 0 || ret > 255) {
				CoreLog::GetInstance().LogError(Types::FString::Format("{},{}", __FILE__, __LINE__));
			}

			return static_cast<uint8>(ret);
		}

		// @param x assumed to be in this range: -1..1
		// @return 0..255
		static uint8 Quantize8SignedByte(const float x) {
			// -1..1 -> 0..1
			auto y = x * 0.5f + 0.5f;

			return Quantize8UnsignedByte(y);
		}

		// Use the Euclidean method to find the GCD
		static int32 GreatestCommonDivisor(int32 a, int32 b) {
			while (b != 0) {
				const auto t = b;
				b = a % b;
				a = t;
			}
			return a;
		}

		// LCM = a/gcd * b
		// a and b are the number we want to find the lcm
		static int32 LeastCommonMultiplier(const int32 a, const int32 b) {
			const auto currentGcd = GreatestCommonDivisor(a, b);
			return currentGcd == 0 ? 0 : (a / currentGcd) * b;
		}

		/**
		 * Generates a 1D Perlin noise from the given value.  Returns a continuous random value between -1.0 and 1.0.
		 *
		 * @param	Value	The input value that Perlin noise will be generated from.  This is usually a steadily incrementing time value.
		 *
		 * @return	Perlin noise in the range of -1.0 to 1.0
		 * */
		static float PerlinNoise1D(float Value);

		/**
		* Generates a 1D Perlin noise sample at the given location.  Returns a continuous random value between -1.0 and 1.0.
		*
		* @param	Location	Where to sample
		*
		* @return	Perlin noise in the range of -1.0 to 1.0
		* */
		static float PerlinNoise2D(const FVector2& Location);


		/**
		* Generates a 3D Perlin noise sample at the given location.  Returns a continuous random value between -1.0 and 1.0.
		*
		* @param	Location	Where to sample
		*
		* @return	Perlin noise in the range of -1.0 to 1.0
		* */
		static float PerlinNoise3D(const FVector3& Location);

		/**
		 * Calculates the new value in a weighted moving average series using the previous value and the weight
		 *
		 * @param currentSample - The value to blend with the previous sample to get a new weighted value
		 * @param previousSample - The last value from the series
		 * @param weight - The weight to blend with
		 *
		 * @return the next value in the series
		 * */
		static float WeightedMovingAverage(const float currentSample, const float previousSample, float weight) {
			weight = Clamp<float>(weight, 0.f, 1.f);
			const auto wAvg = (currentSample * weight) + (previousSample * (1.f - weight));
			return wAvg;
		}

		/**
		 * Calculates the new value in a weighted moving average series using the previous value and a weight range.
		 * The weight range is used to dynamically adjust based upon distance between the samples
		 * This allows you to smooth a value more aggressively for small noise and let large movements be smoothed less (or vice versa)
		 *
		 * @param currentSample - The value to blend with the previous sample to get a new weighted value
		 * @param previousSample - The last value from the series
		 * @param maxDistance - Distance to use as the blend between min weight or max weight
		 * @param minWeight - The weight use when the distance is small
		 * @param maxWeight - The weight use when the distance is large
		 *
		 * @return the next value in the series
		 * */
		static float DynamicWeightedMovingAverage(const float currentSample, const float previousSample, const float maxDistance,
		                                          const float minWeight, const float maxWeight) {
			// We need the distance between samples to determine how much of each weight to use
			const auto distance = Abs<float>(currentSample - previousSample);
			auto weight = minWeight;
			if (maxDistance > 0) {
				// Figure out the lerp value to use between the min/max weights
				const auto lerpAlpha = Clamp<float>(distance / maxDistance, 0.f, 1.f);
				weight = Lerp<float>(minWeight, maxWeight, lerpAlpha);
			}
			return WeightedMovingAverage(currentSample, previousSample, weight);
		}
	};
}

#endif //VISREAL_VISREAL_MATH_UTILITY_H
