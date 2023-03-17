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
                std::cout << "gfx-cmp: Compressing table: " << argv[1] << "\n";
                if(comp.compress(table)) {
                    comp.close();
                    std::cout << "gfx-cmp: Success..\n";
                } else {
                    std::cout << "gfx-cmp: Failure..\n";
                }
            }
        }
    } else if(argc == 4 && std::string(argv[3]) == "-e") {
        game::GfxExtract ex;
        game::GfxTable table;
        if(ex.open(argv[1])) {
            mkdir(argv[2], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if(ex.extract(table, argv[2])) {
                std::cout << "gfx-cmp: Successflly Inflated: " << argv[1] << "\n";
            } else {
                std::cout << "gfx-cmp: Failed to Inflate: " << argv[1] << "\n";
            }
        }
    }
    else {
        std::cout << "use:\n" << argv[0] << " table.cfg output.gfx -c\nor:\n" << argv[0] << "file.gfx direcotry -e\n";
    }
    return 0;
}