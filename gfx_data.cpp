#include"gfx_data.hpp"

namespace game {
    bool GfxData::open(const std::string &filename) {
        file.open(filename, std::ios::in | std::ios::binary);
        if(!file.is_open())
            return false;
            
        return true;   
    }
    bool GfxData::load(RenderObject *ro, const Color &c) {

        return true;
    }

}