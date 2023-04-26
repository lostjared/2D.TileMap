#include"level.hpp"
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>

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
        uint32_t name_len = static_cast<uint32_t>(level_name.length());
        out.write(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        out.write(reinterpret_cast<const char*>(level_name.c_str()), name_len);
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
        char *tmp;
        uint32_t name_len = 0;
        in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        tmp = new char [ name_len + 1 ];
        in.read(reinterpret_cast<char*>(tmp), name_len);
        tmp[name_len] = 0;
        level_name = tmp;
        delete [] tmp;
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

    bool Level::checkType(const Point &p, int type) {
        Tile *tile = at(p.x, p.y);
        if(tile != nullptr) {
            if(tile->solid == type)
                return true;
        }
        return false;
    }
    
    bool Level::checkTypes(const std::vector<Point> &p, int type) {
        for(auto &i : p) {
            if(checkType(i, type) == false)
                return false;
        }
        return true;
    }

    bool Level::checkTileSolid(int x, int y) {
        Tile *tile = at(x, y);
        if(tile != nullptr) {
            if(tile->solid == 0)
                return false;
        }
        return true;
    }

    bool Level::checkSolid(const Point &p) {
        return checkTileSolid(p.x, p.y);
    }


    bool Level::check(const std::vector<Point> &p) {
        for(auto &i : p) {
            if(checkTileSolid(i.x, i.y))
                return true;
        }
        return false;
    }    

    bool Level::checkRect(const Rect &r) {
        for(int i = r.x; i <= r.x+r.w; ++i) {
            for(int z = r.y; z <= r.y+r.h; ++z) {
                Tile *tile = at(i, z);
                if(tile != nullptr) {
                    if(tile->solid == 1)
                        return false;
                } else return false;
            }
        }
        return true;
    }

    bool Level::checkRectForType(const Rect &r, int type) {
        for(int i = r.x; i <= r.x+r.w; ++i) {
            for(int z = r.y; z <= r.y+r.h; ++z) {
                Tile *tile = at(i, z);
                if(tile != nullptr) {
                    if(tile->solid == type)
                        return true;
                }
            }
        }
        return false;
    }

    bool Level::checkRectsForType(const std::vector<Rect> &v, int type) {
        for(auto &i : v) {
            if(!checkRectForType(i, type))
                return false;
        }
        return true;
    }

    void Level::setLevelName(const std::string &name) {
         level_name = name;
    }
  
    std::string Level::getLevelName() const {
        return level_name;  
    }

    bool atPoint(int x1, int y1, int w, int h, int &x, int &y) {
       x = x1/w;
       y = y1/h;
       if(x >= 0 && y >= 0)
            return true;
        return false;
    }

    bool PointInRect(const Point &p, const Rect &r) {
        if(p.x >= r.x && p.x <= r.x+r.w && p.y >= r.y && p.y <= r.y+r.h)
            return true;
        return false;
    }

}