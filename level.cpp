#include"level.hpp"
#include<iostream>
#include<sstream>
#include<string>

namespace game {  

    Tile::Tile(const Tile &tile) {
        set(tile);
    } 

    Tile& Tile::operator=(const Tile &tile) {
        set(tile);
        return *this;
    }
   
    void Tile::set(const Tile &tile) { 
        color = tile.color;
        img = tile.img;
        solid = tile.solid;
        layers[0] = tile.layers[0];
        layers[1] = tile.layers[1];
        layers[2] = tile.layers[2];
    }

   Level::Level() : width{0}, height{0}, tiles{nullptr} {

   }

    Level::~Level() {
        releaseTiles();
    }

    bool Level::loadLevel(const std::string &filename) {

        return true;
    }

    void Level::create(int w, int h, const Tile &init_tile) {
        resizeTiles(w, h);
        for(int i = 0; i < w; ++i) {
            for(int z = 0; z < h; ++z) {
                tiles[i][z] = init_tile;
            }
        }
    }

    Tile *Level::at(int x, int y) {
        if(x >= 0 && x < width && y >= 0 && y < height) {
            return &tiles[x][y];
        }
        return nullptr;
    }

    void Level::output_map(std::ostream &out) {
        if(width == 0 || height == 0 || tiles == nullptr) {
            out << "[empty map]\n";
            return;
        }
        for(int x = 0; x < width; ++x) {
            for(int y = 0; y < height; ++y) {
                Tile *t = at(x,y);
                if(t != nullptr) {
                     out << "x: " << x << ", y: " << y << " " << t->color << "\n";
                }
            }
        }
    }

    bool Level::resizeTiles(int w, int h) {
        releaseTiles();
        width = w;
        height = h;
        tiles = new Tile*[width];
        for(int i = 0; i < width; ++i) {
            tiles[i] = new Tile[height];
        }
        return true;
    }

    void Level::releaseTiles() {
        if(tiles != nullptr && width != 0) {
            for(int i = 0; i < width; ++i) {
                delete [] tiles[i];
            }
            delete [] tiles;
        }
    }

    bool atPoint(int x1, int y1, int &x, int &y) {
        for(int i = 0; i < 1280/16; ++i) {
            for(int z = 0; z < 720/16; ++z) {
                int cx = i*16;
                int cy = z*16;
                if(cx >= x1 && cx <= x1+16 && cy >= y1 && cy <= y1+16) {
                    x = i;
                    y = z;
                    return true;
                }
            }
        }
        return false;
    }

}