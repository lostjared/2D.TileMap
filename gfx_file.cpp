#include "gfx_file.hpp"

namespace game {

    bool GfxCompress::open(const std::string &text) {
        file.open(text, std::ios::out | std::ios::binary);
        return file.is_open();
    }

    bool GfxCompress::compress(const std::string &config) {

        return true;
    }
     
     
    void GfxCompress::close() {
        file.close();
    }

}

