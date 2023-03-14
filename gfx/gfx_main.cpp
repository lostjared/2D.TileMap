#include<iostream>
#include<string>
#include<sys/stat.h>
#include "../gfx_file.hpp"

int main(int argc, char **argv) {
    if(argc == 4 && std::string(argv[3]) == "-c") {
        game::GfxTable table;
        if(table.buildTable(argv[1])) {
            game::GfxCompress comp;
            if(comp.open(argv[2])) {
                std::cout << "compressing table: " << argv[1] << "\n";
                if(comp.compress(table)) {
                    comp.close();
                    std::cout << "success..\n";
                } else {
                    std::cout << "failure..\n";
                }
            }
        }
    } else if(argc == 4 && std::string(argv[3]) == "-e") {
        game::GfxExtract ex;
        if(ex.open(argv[1])) {
            mkdir(argv[2], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if(ex.extract(argv[2])) {
                std::cout << "Successflly inflated: " << argv[1] << "\n";
            } else {
                std::cout << "Failed to inflate: " << argv[1] << "\n";
            }
        }
    }
    else {
        std::cout << "use:\n" << argv[0] << " table.cfg output.gfx -c\nor:\n" << argv[0] << "file.gfx direcotry -e\n";
    }
    return 0;
}