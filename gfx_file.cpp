#include "gfx_file.hpp"

namespace game {

     void GfxTable::addItem(const GfxItem &item) {
        table.push_back(item);
     }
     
     void GfxTable::addItem(uint32_t index, uint32_t solid, uint32_t obj, const std::string &filename) {
        std::cout << "adding item: " << filename << " of type: " << obj << "\n";
        table.push_back( {index, solid, obj, filename });
     }

    bool GfxTable::buildTable(const std::string &cfg) {
        clear();
        std::fstream file;
        file.open(cfg, std::ios::in);
        if(!file.is_open())
            return false;

        int type = 0;
        while(!file.eof()) {
            std::string line;
            std::getline(file, line);
            if(file) {
                if(line == "[tiles]") {
                    type = 0;
                } else if(line == "[objects]") {
                    type = 1;
                } else if(line == "[hero:right]") {
                    type = 2;
                } else if(line == "[hero:left]") {
                    type = 3;
                } else {
                    std::string tokens[3];
                    auto pos = line.find(":");
                    if(pos == std::string::npos) {
                        std::cerr << "missing colon on type: " << type << "\n";
                        return false;
                    }
                    tokens[0] = line.substr(0, pos);
                    std::string right;
                    right = line.substr(pos+1, line.length());
                    pos = right.find(":");
                    if(pos == std::string::npos) {
                        std::cerr << "missing colon on type: " << type << "\n";
                        return false;
                    }
                    tokens[1] = right.substr(0, pos);
                    tokens[2] = right.substr(pos+1, right.length());
                    addItem(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), type, tokens[2]);
                }
            }
        }


        file.close();
        return true;
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
            auto pos = t.table[i].filename.rfind("/");
            std::string id;
            if(pos == std::string::npos) 
                id = t.table[i].filename;
            else
                id = t.table[i].filename.substr(pos+1, t.table[i].filename.length());
            std::cout << "gfx-cmp: adding: " << t.table[i].filename << " as " << id << "\n";
            write_string(id);
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

