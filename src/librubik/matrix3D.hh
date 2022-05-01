#pragma once

#include <array>

#include "vector3D.hh"

namespace rubik
{
    template <typename T>
    class Matrix3D
    {
    public:
        Matrix3D(std::array<std::array<T, 3>, 3> matrix)
            : matrix_(matrix)
        {}

        T at(int i, int j)
        {
            return matrix_[i][j];
        }

        Vector3D<T> operator*(const Vector3D<T>& v) const
        {
            T new_x =
                matrix_[0][0] * v.x + matrix_[0][1] * v.y + matrix_[0][2] * v.z;
            T new_y =
                matrix_[1][0] * v.x + matrix_[1][1] * v.y + matrix_[1][2] * v.z;
            ;
            T new_z =
                matrix_[2][0] * v.x + matrix_[2][1] * v.y + matrix_[2][2] * v.z;
            ;
            return Vector3D<T>(new_x, new_y, new_z);
        }

        void transpose()
        {
            for (int i = 0; i < 2; i++)
                for (int j = i + 1; j < 3; j++)
                {
                    T tmp = matrix_[i][j];
                    matrix_[i][j] = matrix_[j][i];
                    matrix_[j][i] = tmp;
                }
        }

    private:
        std::array<std::array<T, 3>, 3> matrix_;
    };

} // namespace rubik
