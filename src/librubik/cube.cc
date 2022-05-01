#include "cube.hh"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace rubik
{
    std::ostream& operator<<(std::ostream& os, const Cube& c)
    {
        for (int i = 0; i < 27; i++)
        {
            os << c.pieces_[i] << "\n";
        }
        return os;
    }

    Cube Cube::from_stream(std::istream& is)
    {
        auto cube = Cube();

        std::string line;
        for (int k = 0; k < 27; k++)
        {
            std::getline(is, line);

            char* content;

            const char* line_tmp = line.c_str();

            // line_char = strcpy(line_char, line_tmp);

            char* line_unconst = (char*)line_tmp;
            content = std::strtok(line_unconst, " (),");

            int i = 0;
            std::vector<int> coords_tmp;
            std::vector<Color> colors_tmp;
            while (content != NULL)
            {
                if (i < 3)
                {
                    coords_tmp.push_back(std::stoi(content));
                }
                else
                {
                    switch (content[0])
                    {
                    case 'W':
                        colors_tmp.push_back(Color::WHITE);
                        break;
                    case 'Y':
                        colors_tmp.push_back(Color::YELLOW);
                        break;
                    case 'G':
                        colors_tmp.push_back(Color::GREEN);
                        break;
                    case 'B':
                        colors_tmp.push_back(Color::BLUE);
                        break;
                    case 'R':
                        colors_tmp.push_back(Color::RED);
                        break;
                    case 'O':
                        colors_tmp.push_back(Color::ORANGE);
                        break;
                    case 'X':
                        colors_tmp.push_back(Color::NONE);
                        break;
                    }
                }
                content = std::strtok(NULL, " (),");

                i++;
            }

            auto coords =
                Vector3D<int>(coords_tmp[0], coords_tmp[1], coords_tmp[2]);

            auto colors =
                Vector3D<Color>(colors_tmp[0], colors_tmp[1], colors_tmp[2]);

            cube.pieces_[k] = Piece(coords, colors);
        }
        return cube;
    }

    Cube::iterator Cube::begin()
    {
        return pieces_.begin();
    }

    Cube::iterator Cube::end()
    {
        return pieces_.end();
    }

    Cube::const_iterator Cube::begin() const
    {
        return pieces_.cbegin();
    }

    Cube::const_iterator Cube::end() const
    {
        return pieces_.cend();
    }

    Piece Cube::find_piece(Vector3D<int> coords) const
    {
        for (auto piece : pieces_)
        {
            if (piece.coords == coords)
                return piece;
        }

        throw std::invalid_argument("not found");
    }

    Piece Cube::find_piece(Vector3D<Color> colors) const
    {
        auto colors2 = Vector3D<Color>(colors.x, colors.z, colors.y);
        auto colors3 = Vector3D<Color>(colors.y, colors.x, colors.z);
        auto colors4 = Vector3D<Color>(colors.y, colors.z, colors.x);
        auto colors5 = Vector3D<Color>(colors.z, colors.x, colors.y);
        auto colors6 = Vector3D<Color>(colors.z, colors.y, colors.x);

        for (auto piece : pieces_)
        {
            if (piece.colors == colors || piece.colors == colors2
                || piece.colors == colors3 || piece.colors == colors4
                || piece.colors == colors5 || piece.colors == colors6)
                return piece;
        }

        throw std::invalid_argument("not found");
    }
} // namespace rubik
