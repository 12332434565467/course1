#ifndef TRANSFORM2D_HPP_6A31CA41_7EDF_4BBD_BE8D_02F8ECD4A79D
#define TRANSFORM2D_HPP_6A31CA41_7EDF_4BBD_BE8D_02F8ECD4A79D

#include "stdtypes.hpp"
#include <cmath>

inline Mat22f make_scaling_2d(
    float x, float y) noexcept
{
    Mat22f result{};
    result[0, 0] = x;
    result[1, 1] = y;
    return result;
}

inline Mat22f make_scaling_2d(float scale) noexcept
{
    return make_scaling_2d(scale, scale);
}

inline Mat22f make_rotation_2d(float angle) noexcept
{
    Mat22f result{};

    const float c = std::cos(angle);
    const float s = std::sin(angle);

    result[0, 0] = c;
    result[0, 1] = -s;
    result[1, 0] = s;
    result[1, 1] = c;

    return result;
}

#endif