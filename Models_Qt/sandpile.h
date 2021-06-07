#ifndef SANDPILE_H
#define SANDPILE_H
#include <iostream>
#include <vector>

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(Point b) const {
        return x == b.x && y == b.y;
    }
};

class Sandpile {
public:
    int height, width;
    unsigned int stability;
    int type;
    bool v_teleport, h_teleport;


    std::vector<std::vector<unsigned int>> matrix;

    Sandpile(int height, int width);

    void landslide(Point point, unsigned int num);

    void landslide_square(Point point, unsigned int num);
    void landslide_triangle(Point point, unsigned int num);
    void landslide_hexagon(Point point, unsigned int num);

    void add_pieces_to_centere(unsigned int num);
    void add_pieces(unsigned int num, int y, int x);

    void change_settings(int heigt_arg, int width_arg, int a = 3);

    void change_type(int new_type);

};


#endif // SANDPILE_H
