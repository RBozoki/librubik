#pragma once

#include <cstring>
#include <fstream>
#include <istream>
#include <iterator>
#include <string>
#include <vector>

#include "piece.hh"

namespace rubik
{
    class Cube
    {
    public:
        Cube()
        {
            for (int x = -1; x < 2; x++)
                for (int y = -1; y < 2; y++)
                    for (int z = -1; z < 2; z++)
                    {
                        auto coords = Vector3D<int>(x, y, z);

                        Color x_color;
                        if (x == -1)
                            x_color = Color::BLUE;
                        else if (x == 0)
                            x_color = Color::NONE;
                        else
                            x_color = Color::GREEN;

                        Color y_color;
                        if (y == -1)
                            y_color = Color::ORANGE;
                        else if (y == 0)
                            y_color = Color::NONE;
                        else
                            y_color = Color::RED;

                        Color z_color;
                        if (z == -1)
                            z_color = Color::YELLOW;
                        else if (z == 0)
                            z_color = Color::NONE;
                        else
                            z_color = Color::WHITE;

                        auto colors =
                            Vector3D<Color>(x_color, y_color, z_color);

                        pieces_.push_back(Piece(coords, colors));
                    }
        }

        friend std::ostream& operator<<(std::ostream& os, const Cube& c);

        static Cube from_stream(std::istream& is);

        using iterator = std::vector<Piece>::iterator;
        using const_iterator = std::vector<Piece>::const_iterator;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        Piece find_piece(Vector3D<int> coords) const;
        Piece find_piece(Vector3D<Color> colors) const;

    private:
        std::vector<Piece> pieces_;
    };

} // namespace rubik
