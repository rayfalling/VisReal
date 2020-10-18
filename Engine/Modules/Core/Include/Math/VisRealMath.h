/**
 * Created by rayfalling on 2020/10/18.
 * */

#ifndef VISREAL_VISREAL_MATH_H
#define VISREAL_VISREAL_MATH_H

#include <cmath>
#include "Types/PlatformTypes.h"

namespace Engine::Core::Math {
    /** Converts a float to an integer with truncation towards zero. */
    static int32 TruncToInt(float value)
    {
        return (int32)value;
    }

    /** Converts a float to an integer value with truncation towards zero. */
    static float TruncToFloat(float value)
    {
        return (float)TruncToInt(value);
    }

    /** Converts a float to a nearest less or equal integer. */
    static  int32 FloorToInt(float value)
    {
        return TruncToInt(floorf(value));
    }

    /** Converts a float to the nearest less or equal integer. */
    static  float FloorToFloat(float value)
    {
        return floorf(value);
    }

    /** Converts a double to a less or equal integer. */
    static  double FloorToDouble(double value)
    {
        return floor(value);
    }

    /** Converts a float to the nearest integer. Rounds up when the fraction is .5 */
    static int32 RoundToInt(float value)
    {
        return FloorToInt(value + 0.5f);
    }

    /** Converts a float to the nearest integer. Rounds up when the fraction is .5 */
    static float RoundToFloat(float value)
    {
        return FloorToFloat(value + 0.5f);
    }

    /** Converts a double to the nearest integer. Rounds up when the fraction is .5 */
    static double RoundToDouble(double value)
    {
        return FloorToDouble(value + 0.5);
    }

    /** Converts a float to the nearest greater or equal integer. */
    static int32 CeilToInt(float value)
    {
        return TruncToInt(ceilf(value));
    }

    /* Converts a float to the nearest greater or equal integer. */
    static float CeilToFloat(float value) {
        return std::ceilf(value);
    }

    /* Converts a float to the nearest greater or equal integer. */
    static double CeilToDouble(double value) {
        return std::ceil(value);
    }


    //TODO
    //    Math.ceil(Math.log(x)/Math.log(2))
    static uint32 upper_power_of_two(uint32 v) {
        std::ceil(std::log(v) / std::log(2));
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    int nearestPowerOfTwo(int n) {
        int v = n;

        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++; // next power of 2

        int x = v >> 1; // previous power of 2

        return (v - n) > (n - x) ? x : v;
    }
}


#endif //VISREAL_VISREAL_MATH_H
