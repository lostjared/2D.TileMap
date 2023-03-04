#ifndef _LEVEL_H__
#define _LEVEL_H__
#include<cstdint>
#include<iostream>
#include<string>

namespace game {

    struct Tile {
        Tile() = default;
        Tile(const Tile &tile);
        Tile(uint8_t c, uint8_t s, uint8_t i);
        Tile(Tile &&tile) = default;
        Tile& operator=(const Tile &tile);
        Tile& operator=(Tile &&tile) = default;
        uint8_t color = 0;
        uint8_t solid = 0;
        uint8_t img = 0;
        uint8_t layers[3] = {0};
        void set(const Tile &tile);
    };   

    bool atPoint(int x1, int y1, int &x, int &y);

    class Level {
    public:
        Level();
        ~Level();
        bool loadLevel(const std::string &filename);
        bool saveLevel(const std::string &filename);
        int32_t width, height;
        void create(int32_t w, int32_t h, const Tile &init_tile);
        Tile *at(int32_t x, int32_t y);
        void output_map(std::ostream &out);
    protected:
        Tile **tiles;
        bool resizeTiles(int32_t w, int32_t h);
        void releaseTiles();
        bool serialize(std::ostream &out);
        bool unserialize(std::istream &in);
    };
}

#endif