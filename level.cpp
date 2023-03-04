#include"level.hpp"
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>

namespace game {  

    Tile::Tile(const Tile &tile) {
        set(tile);
    }

    
    Tile::Tile(uint8_t c, uint8_t s, uint8_t i) : color{c}, solid{s}, img{i} {
        layers[0] = 0;
        layers[1] = 0;
        layers[2] = 0;
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

    void Tile::setTile(const Tile &tile) {
        color = tile.color;
        img = tile.img;
        solid = tile.solid;
    }

   Level::Level() : width{0}, height{0}, tiles{nullptr} {

   }

    Level::~Level() {
        releaseTiles();
    }

    bool Level::loadLevel(const std::string &filename) {
        std::fstream file;
        file.open(filename, std::ios::in | std::ios::binary);
        if(!file.is_open()) 
            return false;
        return unserialize(file);
    }

    bool Level::saveLevel(const std::string &filename) {
        std::fstream file;
        file.open(filename, std::ios::out | std::ios::binary);
        if(!file.is_open()) 
            return false;
        return serialize(file);
    }

    void Level::create(int32_t w, int32_t h, const Tile &init_tile) {
        resizeTiles(w, h);
        for(int i = 0; i < w; ++i) {
            for(int z = 0; z < h; ++z) {
                tiles[i][z] = init_tile;
            }
        }
    }

    Tile *Level::at(int32_t x, int32_t y) {
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

    bool Level::resizeTiles(int32_t w, int32_t h) {
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
            tiles = nullptr;
        }
    }

   bool Level::serialize(std::ostream &out) {
        if(tiles == nullptr) return false;
        uint32_t type = 0x420;
        out.write(reinterpret_cast<char*>(&type), sizeof(type));
        out.write(reinterpret_cast<char*>(&width), sizeof(width));
        out.write(reinterpret_cast<char*>(&height), sizeof(height));
        for(int i = 0; i < width; ++i) {
            for(int z = 0; z < height; ++z) {
                out.write(reinterpret_cast<char*>(&tiles[i][z]), sizeof(tiles[i][z]));
            }
        }
        return true;
   }
   
   bool Level::unserialize(std::istream &in) {
        uint32_t type = 0;
        in.read(reinterpret_cast<char*>(&type), sizeof(type));
        if(type != 0x420) return false;
        releaseTiles();
        in.read(reinterpret_cast<char*>(&width), sizeof(width));
        in.read(reinterpret_cast<char*>(&height), sizeof(height));
        create(width, height, game::Tile{});
        for(int i = 0; i < width; ++i) {
            for(int z = 0; z < height; ++z) {
                in.read(reinterpret_cast<char*>(&tiles[i][z]), sizeof(tiles[i][z]));
            }
        }
        return true;
   }

    bool atPoint(int x1, int y1, int w, int h, int &x, int &y) {
        y1 -= 16;
        x1 -= 16;
        for(int i = 0; i < 1280/16; ++i) {
            for(int z = 0; z < 720/16; ++z) {
                int cx = i*16;
                int cy = z*16;
                if(cx >= x1 && cx <= x1+w && cy >= y1 && cy <= y1+h) {
                    x = i;
                    y = z;
                    return true;
                }
            }
        }
        return false;
    }

}