#pragma once

#include <cmath>

#define POINT_PRECISION 1e-12


template<class T>
bool isEqual(T a, T b, typename std::enable_if<std::is_integral<T>::value >::type* = 0)
{
    return a == b;
}

template<class T>
bool isEqual(T first, T second, typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
{
    return std::abs(first - second) < POINT_PRECISION;
}

template<class T>
bool isLessOrEq(T first, T second, typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
{
    double difference = first - second;
    return difference < POINT_PRECISION or std::abs(difference) < POINT_PRECISION;
}
