#pragma once

#include <iostream>
#include <ostream>

namespace rubik
{
    template <typename T>
    class Vector3D
    {
    public:
        Vector3D(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {}

        bool operator==(const Vector3D other)
        {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const Vector3D other)
        {
            return x != other.x || y != other.y || z != other.z;
        }

        T x;
        T y;
        T z;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3D<T>& v)
    {
        os << "(" << v.x << "," << v.y << "," << v.z << ")";
        return os;
    }

} // namespace rubik
