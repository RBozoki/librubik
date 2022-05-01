#include "piece.hh"

#include <algorithm>
#include <cmath>
#include <ostream>

namespace rubik
{
    Piece::Type Piece::get_type()
    {
        int list[] = { coords.x, coords.y, coords.z };

        if (coords.x == 0 && coords.x == coords.y && coords.y == coords.z)
            return Piece::Type::NONE;

        else if (abs(coords.x) == 1 && abs(coords.y) == 1 && abs(coords.z) == 1)
            return Piece::Type::EDGE;

        else if (std::count(list, list + 3, 0) == 2)
            return Piece::Type::CENTER;

        else
            return Piece::Type::CORNER;
    }

    bool Piece::operator==(const Piece& other)
    {
        return coords == other.coords && colors == other.colors;
    }

    bool Piece::operator!=(const Piece& other)
    {
        return coords != other.coords || colors != other.colors;
    }

    bool Piece::operator<(const Piece& other)
    {
        if (coords.x < other.coords.x)
            return true;
        else if (coords.y < other.coords.y)
            return true;
        else if (coords.z < other.coords.z)
            return true;
        else
            return false;
    }

    bool Piece::operator<=(const Piece& other)
    {
        if (coords.x <= other.coords.x)
            return true;
        else if (coords.y <= other.coords.y)
            return true;
        else if (coords.z <= other.coords.z)
            return true;
        else
            return false;
    }

    bool Piece::operator>(const Piece& other)
    {
        if (coords.x > other.coords.x)
            return true;
        else if (coords.y > other.coords.y)
            return true;
        else if (coords.z > other.coords.z)
            return true;
        else
            return false;
    }

    bool Piece::operator>=(const Piece& other)
    {
        if (coords.x >= other.coords.x)
            return true;
        else if (coords.y >= other.coords.y)
            return true;
        else if (coords.z >= other.coords.z)
            return true;
        else
            return false;
    }

    std::ostream& operator<<(std::ostream& os, const Piece& p)
    {
        os << p.coords << " " << p.colors;
        return os;
    }

    void Piece::do_move(Face face, Direction dir)
    {
        std::array<std::array<int, 3>, 3> values = {
            { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }
        };

        Vector3D<int> original_coords = coords;

        bool transpose = false;

        switch (face)
        {
        case Face::UP:
            values[0][1] = -1;
            values[1][0] = 1;
            values[2][2] = 1;
            transpose = true;
            break;

        case Face::DOWN:
            values[0][1] = -1;
            values[1][0] = 1;
            values[2][2] = 1;
            break;

        case Face::LEFT:
            values[0][2] = 1;
            values[1][1] = 1;
            values[2][0] = -1;
            break;

        case Face::RIGHT:
            values[0][2] = 1;
            values[1][1] = 1;
            values[2][0] = -1;
            transpose = true;
            break;

        case Face::FRONT:
            values[0][0] = 1;
            values[1][2] = -1;
            values[2][1] = 1;
            transpose = true;
            break;

        case Face::BACK:
            values[0][0] = 1;
            values[1][2] = -1;
            values[2][1] = 1;
            break;
        }

        auto rotation = Matrix3D<int>(values);
        if (transpose)
            rotation.transpose();

        if (dir == Direction::ANTI_CLOCKWISE)
            rotation.transpose();

        coords = rotation * coords;

        if (original_coords != coords)
        {
            Color tmp;
            switch (face)
            {
            case Face::UP: // Z
                tmp = colors.x;
                colors.x = colors.y;
                colors.y = tmp;
                break;

            case Face::DOWN: // Z
                tmp = colors.x;
                colors.x = colors.y;
                colors.y = tmp;
                break;

            case Face::LEFT: // Y
                tmp = colors.x;
                colors.x = colors.z;
                colors.z = tmp;
                break;

            case Face::RIGHT: // Y
                tmp = colors.x;
                colors.x = colors.z;
                colors.z = tmp;
                break;

            case Face::FRONT: // X
                tmp = colors.y;
                colors.y = colors.z;
                colors.z = tmp;
                break;

            case Face::BACK: // X
                tmp = colors.y;
                colors.y = colors.z;
                colors.z = tmp;
                break;
            }
        }
    }

    void Piece::do_move(Axis axis, Direction dir)
    {
        switch (axis)
        {
        case Axis::X:
            do_move(Face::RIGHT, dir);
            break;
        case Axis::Y:
            do_move(Face::UP, dir);
            break;
        case Axis::Z:
            do_move(Face::FRONT, dir);
            break;
        }
    }
} // namespace rubik
