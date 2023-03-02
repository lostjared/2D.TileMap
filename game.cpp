#include"game.hpp"


namespace game {
    
    Color::Color(unsigned char rr, unsigned char gg, unsigned char bb) : r{rr}, g{gg}, b{bb} {}
    
    Rect::Rect(int xx, int yy, int ww, int hh) : x{xx}, y{yy}, w{ww}, h{hh} {}

    Point::Point(int xx, int yy) : x{xx}, y{yy} {}

}