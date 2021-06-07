#include <SFML/Graphics.hpp>
#include <list>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

const int screen_width = 600, screen_height = 600;


/*!
	\brief Структура Точка

	Данная структура содержит координаты x и y
*/
struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point(sf::Vector2f pos) : x(pos.y), y(pos.x) {}

    bool operator==(Point b) const {
        return x == b.x && y == b.y;
    }
};


class Sandpile {
public:
    int height, width;
    std::vector<std::vector<int>> matrix;

    Sandpile(int height, int width) : height(height), width(width) {
        matrix = std::vector(height, std::vector<int>(width, 3));
    }

    void landslide(Point point, int num = 0, bool v_teleport = false, bool h_teleport = false) {
        if (point.x < 0 || point.x > width - 1 || point.y < 0 || point.y > height - 1) {
            return;
        }

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
            matrix[point.y][point.x] = remain_part;
            matrix[point.y][point.x - 1] += whole_part;
            matrix[point.y + 1][point.x] += whole_part;
            matrix[point.y - 1][point.x] += whole_part;
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
        matrix[point.y + 1][point.x] += whole_part;
        matrix[point.y - 1][point.x] += whole_part;
        matrix[point.y][point.x + 1] += whole_part;
        matrix[point.y][point.x - 1] += whole_part;

    }
    void landslide_triangle(Point point, int num = 0, bool v_teleport = false, bool h_teleport = false) {
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
        matrix[point.y ][point.x - 2] += whole_part;
        matrix[point.y ][point.x + 2]  += whole_part;

    }

};


int main() {
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "MODELS");
    window.setFramerateLimit(60);
    Sandpile model(screen_height, screen_width);
    sf::VertexArray arr_point(sf::Points, screen_height * (screen_width + 1));


    sf::Event event;
    int size_iteration = 1000000;
    model.matrix[screen_height / 2][screen_width / 2] = size_iteration;

    bool flag = true;
    while (window.isOpen()) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
//        std::cout << pixelPos.x
//                  << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
//        std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты
        flag = true;
        for (int y = 0; y < screen_height; ++y) {
            for (int x = 0; x < screen_width; ++x) {
                if (model.matrix[y][x] > 3) {
                    Point a(x, y);
                    model.landslide_triangle(a);
                    flag = false;
                }
                arr_point[y * screen_width + x].position = sf::Vector2f(y, x);
                switch (model.matrix[y][x]) {
                    case 0:
                        arr_point[y * screen_width + x].color = sf::Color(255, 255, 0);
                        break;
                    case 1:
                        arr_point[y * screen_width + x].color = sf::Color(0, 125, 52);
                        break;
                    case 2:
                        arr_point[y * screen_width + x].color = sf::Color(0, 125, 255);
                        break;
                    case 3:
                        arr_point[y * screen_width + x].color = sf::Color(139, 0, 255);
                        break;
                    default:
                        arr_point[y * screen_width + x].color = sf::Color(0, 0, 0);
                        break;
                }
            }
        }
        if (flag) {
//            std::cout << "Matrix aproximate\n";
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {//если нажата клавиша мыши
                if (event.key.code == sf::Mouse::Left) {//а именно левая
                    std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
                    model.landslide(pos, 4);
                }
                if (event.key.code == sf::Mouse::Right) {//а именно левая
                    std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
                    model.landslide(pos, 100);
                }
            }

        }

        // Выполняем необходимые действия по отрисовке
        window.clear();
        window.draw(arr_point);
        window.display();
    }
    return 0;
}
/*
     x  -
     ╔══════╗
   y ║      ║
   | ║      ║
     ╚══════╝
 */
