#include<iostream>
#include<string>
#include "../gfx_file.hpp"

int main(int argc, char **argv) {
    if(argc == 3) {
        game::GfxTable table;
        if(table.buildTable(argv[1])) {
            game::GfxCompress comp;
            if(comp.open(argv[2])) {
                std::cout << "compressing table: " << argv[1] << "\n";
                comp.compress(table);
                comp.close();
            }
        }
    } else {
        std::cout << "use:\n" << argv[0] << " table.cfg output.gfx\n";
    }
    return 0;
}