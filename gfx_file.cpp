#include "gfx_file.hpp"

namespace game {

     void GfxTable::addItem(const GfxItem &item) {
        table.push_back(item);
     }
     
     void GfxTable::addIiem(uint32_t index, uint32_t solid, uint32_t obj, const std::string &filename) {
        table.push_back( {index, solid, obj, filename });
     }

    void GfxTable::buildTable(const std::string &cfg) {
        clear();

    }

    void GfxTable::clear() {
        if(!table.empty()) {
            table.erase(table.begin(), table.end());
        }
    }

    bool GfxCompress::open(const std::string &text) {
        file.open(text, std::ios::out | std::ios::binary);
        return file.is_open();
    }

    bool GfxCompress::compress(const GfxTable &t) {
        for(std::vector<GfxItem>::size_type i = 0; i < t.table.size(); ++i) {
            write_string(t.table[i].filename);
            file.write(reinterpret_cast<const char*>(&t.table[i].index), sizeof(uint32_t));
            file.write(reinterpret_cast<const char*>(&t.table[i].solid), sizeof(uint32_t));
            file.write(reinterpret_cast<const char*>(&t.table[i].obj), sizeof(uint32_t));
            std::fstream in_file;
            in_file.open(t.table[i].filename, std::ios::in | std::ios::binary);
            if(!in_file.is_open()) {
                std::cerr << "Error could not open file: " << t.table[i].filename << "\n";
                return false;
            }
            in_file.seekg(std::ios::end);
            uint32_t len = in_file.tellg();
            file.write(reinterpret_cast<char*>(&len), sizeof(uint32_t));
            in_file.seekg(std::ios::beg);
            while(!in_file.eof()) {
                char buf[1024];
                in_file.read(reinterpret_cast<char*>(buf), sizeof(buf));
                file.write(reinterpret_cast<char*>(buf), in_file.gcount());                
            }
            in_file.close(); 
        }
        return true;
    }
     
     
    void GfxCompress::close() {
        file.close();
    }

    void GfxCompress::write_string(const std::string &item) {
        auto len = item.length();
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(reinterpret_cast<const char*>(item.c_str()), len);
    }


}

