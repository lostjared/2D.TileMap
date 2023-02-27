#ifndef _LEVEL_H__
#define _LEVEL_H__
#include<cstdint>
#include<iostream>
#include<string>

namespace game {

    struct Tile {
        Tile() = default;
        Tile(const Tile &tile);
        Tile(int32_t c, int32_t s, int32_t i);
        Tile(Tile &&tile) = default;
        Tile& operator=(const Tile &tile);
        Tile& operator=(Tile &&tile) = default;
        int32_t color = 0;
        int32_t solid = 0;
        int32_t img = 0;
        int32_t layers[3];
        void set(const Tile &tile);
    };   

    bool atPoint(int x1, int y1, int &x, int &y);

    class Level {
    public:
        Level();
        ~Level();
        bool loadLevel(const std::string &filename);
        int width, height;
        void create(int w, int h, const Tile &init_tile);
        Tile *at(int x, int y);
        void output_map(std::ostream &out);
    protected:
        Tile **tiles;
        bool resizeTiles(int w, int h);
        void releaseTiles();
    };
}

#endif