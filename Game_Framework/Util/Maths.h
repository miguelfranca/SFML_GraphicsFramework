#pragma once

template <typename T>
T toRadians(T degrees)
{
    return degrees * M_PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / M_PI;
}