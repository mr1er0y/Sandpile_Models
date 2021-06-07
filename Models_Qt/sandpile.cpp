#include "sandpile.h"

Sandpile::Sandpile(int height, int width): height(height), width(width)
{
     matrix = std::vector(height, std::vector<unsigned int>(width, 3));
     stability = 3;
     type = 0;
}
void Sandpile::landslide(Point point, unsigned int num = 0) {
    switch(type){
        case 0:
            landslide_square(point, num);
            break;
        case 1:
            landslide_triangle(point, num);
            break;
        case 2:
            landslide_hexagon(point, num);
            break;
        }
}

void Sandpile::landslide_square(Point point, unsigned int num = 0) {
    if (point.x < 0 || point.x > width - 1 || point.y < 0 || point.y > height - 1) {
        return;
    }

//    int a = 50;
//    if (((width - a) / 2 < point.x &&  (width + a) / 2 > point.x ) &&
//            ((height - a) / 2 < point.y &&  (height + a) / 2 > point.y)) {
//        matrix[point.x][point.y] = 0;
//        return;
//    }

    int whole_part = (num + matrix[point.y][point.x]) / 4;
    int remain_part = (num + matrix[point.y][point.x]) % 4;

    if (point.y == 0 && point.x == 0) {
        /*
            x  -
             *══════╗
           y ║      ║
           | ║      ║
             ╚══════╝
         */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y + 1][point.x] += whole_part;
        matrix[point.y][point.x + 1] += whole_part;

        return;
    }
    if (point.y == width - 1 && point.x == width - 1) {
        /*
         ╔══════╗
         ║      ║
         ║      ║
         ╚══════*
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y - 1][point.x] += whole_part;
        matrix[point.y][point.x - 1] += whole_part;
        return;
    }
    if (point.y == 0 && point.x == width - 1) {
        /*
         ╔══════*
         ║      ║
         ║      ║
         ╚══════╝
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y + 1][point.x] += whole_part;
        matrix[point.y][point.x - 1] += whole_part;

        return;
    }
    if (point.y == height - 1 && point.x == 0) {
        /*
         ╔══════╗
         ║      ║
         ║      ║
         *══════╝
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y - 1][point.x] += whole_part;
        matrix[point.y][point.x + 1] += whole_part;
        return;
    }
    if (point.y == 0 && 0 < point.x && point.x < width - 1) {
        /*
         ╔═══*══╗
         ║      ║
         ║      ║
         ╚══════╝
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y][point.x + 1] += whole_part;
        matrix[point.y][point.x - 1] += whole_part;
        matrix[point.y + 1][point.x] += whole_part;
        if (v_teleport) {
            matrix[height - 1][width - point.x] += whole_part;
        }
        return;
    }
    if (point.x == 0 && 0 < point.y && point.y < height - 1) {
        /*
         ╔══════╗
         *      ║
         ║      ║
         ╚══════╝
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y][point.x + 1] += whole_part;
        matrix[point.y + 1][point.x] += whole_part;
        matrix[point.y - 1][point.x] += whole_part;
        if (h_teleport) {
            matrix[height - point.y][width - 1] += whole_part;
        }
        return;
    }
    if (point.x == width - 1 && 0 < point.y && point.y < height - 1) {
        /*
         ╔══════╗
         ║      *
         ║      ║
         ╚══════╝
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y][point.x - 1] += whole_part;
        matrix[point.y + 1][point.x] += whole_part;
        matrix[point.y - 1][point.x] += whole_part;
        if (h_teleport) {
            matrix[height - point.y][0] += whole_part;
        }
        return;
    }
    if (point.y == height - 1 && 0 < point.x && point.x < width - 1) {
        /*
         ╔══════╗
         ║      ║
         ║      ║
         ╚═══*══╝
        */
        matrix[point.y][point.x] = remain_part;
        matrix[point.y][point.x + 1] += whole_part;
        matrix[point.y][point.x - 1] += whole_part;
        matrix[point.y - 1][point.x] += whole_part;
        if (v_teleport) {
            matrix[0][width - point.x] += whole_part;
        }
        return;
    }
    // normal
    matrix[point.y][point.x] = remain_part;
    matrix[point.y + 1][point.x] += whole_part;
    matrix[point.y - 1][point.x] += whole_part;
    matrix[point.y][point.x + 1] += whole_part;
    matrix[point.y][point.x - 1] += whole_part;
}
void Sandpile::landslide_triangle(Point point, unsigned int num = 0) {
//        if (point.x < 0 || point.x > width - 1 || point.y < 0 || point.y > height - 1) {
//            return;
//        }

       if (point.x < 1 || point.x > width - 2 || point.y < 1 || point.y > height - 2) {
           return;
       }

       int whole_part = (num + matrix[point.y][point.x]) / 6;
       int remain_part = (num + matrix[point.y][point.x]) % 6;

       if (point.y == 0 && point.x == 0) {
           /*
               x  -
                *══════╗
              y ║      ║
              | ║      ║
                ╚══════╝
            */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y + 1][point.x] += whole_part;
           matrix[point.y][point.x + 1] += whole_part;

           return;
       }
       if (point.y == width - 1 && point.x == width - 1) {
           /*
            ╔══════╗
            ║      ║
            ║      ║
            ╚══════*
           */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y - 1][point.x] += whole_part;
           matrix[point.y][point.x - 1] += whole_part;
           return;
       }
       if (point.y == 0 && point.x == width - 1) {
           /*
            ╔══════*
            ║      ║
            ║      ║
            ╚══════╝
           */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y + 1][point.x] += whole_part;
           matrix[point.y][point.x - 1] += whole_part;

           return;
       }
       if (point.y == height - 1 && point.x == 0) {
           /*
            ╔══════╗
            ║      ║
            ║      ║
            *══════╝
           */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y - 1][point.x] += whole_part;
           matrix[point.y][point.x + 1] += whole_part;
           return;
       }
       if (point.y == 0 && 0 < point.x && point.x < width - 1) {
           /*
            ╔═══*══╗
            ║      ║
            ║      ║
            ╚══════╝
           */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y][point.x + 1] += whole_part;
           matrix[point.y][point.x - 1] += whole_part;
           matrix[point.y + 1][point.x] += whole_part;
           if (h_teleport) {
               matrix[height - 1][width - point.x] += whole_part;
           }
           return;
       }
       if (point.x == 0 && 0 < point.y && point.y < height - 1) {
           /*
            ╔══════╗
            *      ║
            ║      ║
            ╚══════╝
           */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y][point.x + 1] += whole_part;
           matrix[point.y + 1][point.x] += whole_part;
           matrix[point.y - 1][point.x] += whole_part;
           if (v_teleport) {
               matrix[height - point.y][width - 1] += whole_part;
           }
           return;
       }
       if (point.x == width - 1 && 0 < point.y && point.y < height - 1) {
           /*
            ╔══════╗
            ║      *
            ║      ║
            ╚══════╝
           */

           if (v_teleport) {
               matrix[height - point.y][0] += whole_part;
           }
           return;
       }
       if (point.y == height - 1 && 0 < point.x && point.x < width - 1) {
           /*
            ╔══════╗
            ║      ║
            ║      ║
            ╚═══*══╝
           */
           matrix[point.y][point.x] = remain_part;
           matrix[point.y][point.x + 1] += whole_part;
           matrix[point.y][point.x - 1] += whole_part;
           matrix[point.y - 1][point.x] += whole_part;
           if (h_teleport) {
               matrix[0][width - point.x] += whole_part;
           }
           return;
       }
       // normal
       matrix[point.y][point.x] = remain_part;
       matrix[point.y - 1][point.x - 1] += whole_part;
       matrix[point.y - 1][point.x + 1] += whole_part;
       matrix[point.y + 1][point.x - 1] += whole_part;
       matrix[point.y + 1][point.x + 1] += whole_part;
       matrix[point.y][point.x - 2] += whole_part;
       matrix[point.y][point.x + 2] += whole_part;

}

void Sandpile::landslide_hexagon(Point point, unsigned int num)
{
    if (point.x < 1 || point.x > width - 2 || point.y < 1 || point.y > height - 2) {
        return;
    }

    int whole_part = (num + matrix[point.y][point.x]) / 3;
    int remain_part = (num + matrix[point.y][point.x]) % 3;

   if (point.y % 2 == 0 && point.x % 4 == 0 ) {
       matrix[point.y][point.x] = remain_part;
       matrix[point.y][point.x - 1] += whole_part;
       matrix[point.y - 1][point.x + 1] += whole_part;
       matrix[point.y + 1][point.x + 1] += whole_part;
   }

   if (point.y % 2 == 1 && point.x % 4 == 1 ) {
       matrix[point.y][point.x] = remain_part;
       matrix[point.y][point.x + 1] += whole_part;
       matrix[point.y - 1][point.x - 1] += whole_part;
       matrix[point.y + 1][point.x - 1] += whole_part;
   }
   if (point.y % 2 == 1 && point.x % 4 == 2 ) {
       matrix[point.y][point.x] = remain_part;
       matrix[point.y][point.x - 1] += whole_part;
       matrix[point.y - 1][point.x + 1] += whole_part;
       matrix[point.y + 1][point.x + 1] += whole_part;
   }
   if (point.y % 2 == 0 && point.x % 4 == 3 ) {
       matrix[point.y][point.x] = remain_part;
       matrix[point.y][point.x + 1] += whole_part;
       matrix[point.y - 1][point.x - 1] += whole_part;
       matrix[point.y + 1][point.x - 1] += whole_part;
   }

}

void Sandpile::add_pieces_to_centere(unsigned int num)
{
    matrix[height / 2][width / 2] += num;
}

void Sandpile::add_pieces(unsigned int num, int y, int x)
{
    matrix[x][y] += num;
}

void Sandpile::change_settings(int heigt_arg, int width_arg, int a)
{
    height = heigt_arg;
    width = width_arg;
    matrix.assign(height, std::vector<unsigned int>(width, a));
}

void Sandpile::change_type(int new_type)
{
    type = new_type;
    switch(type){
        case 0:
            stability = 3;
            break;
        case 1:
            stability = 5;
            break;
        case 2:
            stability = 2;
            break;
        }
}
