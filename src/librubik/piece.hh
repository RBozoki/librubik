#pragma once

#include <ostream>

#include "color.hh"
#include "matrix3D.hh"
#include "move.hh"
#include "vector3D.hh"

namespace rubik
{
    class Piece
    {
    public:
        Piece(Vector3D<int> coords, Vector3D<Color> colors)
            : coords(coords)
            , colors(colors)
        {}

        enum Type
        {
            CORNER,
            CENTER,
            EDGE,
            NONE
        };

        Vector3D<int> coords;
        Vector3D<Color> colors;

        Type get_type();

        bool operator==(const Piece& other);
        bool operator!=(const Piece& other);
        bool operator<(const Piece& other);
        bool operator<=(const Piece& other);
        bool operator>(const Piece& other);
        bool operator>=(const Piece& other);

        void do_move(Face face, Direction dir);
        void do_move(Axis axis, Direction dir);
    };

    std::ostream& operator<<(std::ostream& os, const Piece& p);
} // namespace rubik
