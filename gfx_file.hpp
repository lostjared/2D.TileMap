#ifndef _GFX_FILE_H__
#define _GFX_FILE_H__


#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

namespace game {
    class GfxCompress {
    public:
        bool open(const std::string &file);
        bool compress(const std::string &config);
        void close();
    protected:
        std::fstream file;
    };
}


#endif