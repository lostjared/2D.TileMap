#ifndef _GFX_DATA_H_
#define _GFX_DATA_H_

#include<iostream>
#include<fstream>
#include<vector>
#include"game.hpp"

namespace game {

    struct GfxImage {
        Image image;
    };

    class GfxData {
    public:
        GfxData() = default;
        bool open(const std::string &filename);
        bool load(RenderObject *ro, const Color &c);
        void close();
    protected:
        std::vector<GfxImage> gfx;
        std::fstream file;
    };

}


#endif