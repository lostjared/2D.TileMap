#include"game.hpp"


namespace game {
    
    Color::Color(unsigned char rr, unsigned char gg, unsigned char bb) : r{rr}, g{gg}, b{bb} {}

    Color::Color(const Color &c) : r{c.r}, g{c.g}, b{c.b} {}
    
    Color &Color::operator=(const Color &c) {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }
    Rect::Rect(int xx, int yy, int ww, int hh) : x{xx}, y{yy}, w{ww}, h{hh} {}

    Rect::Rect(const Rect &r) : x{r.x}, y{r.y}, w{r.w}, h{r.h} {}

    Rect &Rect::operator=(const Rect &r) {
        x = r.x;
        y = r.y;
        w = r.w;
        h = r.h;
        return *this;
    }

    Point::Point(int xx, int yy) : x{xx}, y{yy} {}

    Point::Point(const Point &p) : x{p.x}, y{p.y} {}

    Point &Point::operator=(const Point &p) {
        x = p.x;
        y = p.y;
        return *this;
    }    
}