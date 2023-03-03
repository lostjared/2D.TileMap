#include"game.hpp"


namespace game {

    Point::Point(int xx, int yy) : x{xx}, y{yy} {}

    Point::Point(const Point &p) : x{p.x}, y{p.y} {}

    Point &Point::operator=(const Point &p) {
        x = p.x;
        y = p.y;
        return *this;
    }    
}