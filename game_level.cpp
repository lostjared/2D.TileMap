#include"game_level.hpp"
#include"window_const.hpp"
#include<sstream>
#include<iostream>
#include<string>

namespace game {

  void GameLevel::init(RenderObject *ro) {
        loadLevel("levels/level1.lvl");
        const char *fileNames[] = {  "black.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp", "snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", 0 };
        for(uint8_t i = 0; fileNames[i] != 0; ++i) {
            std::ostringstream stream;
            stream << "./img/" << fileNames[i];
            int img = ro->loadImage(stream.str());
            images.push_back(img);
        }
        arial = ro->loadFont("./img/arial.ttf", 24);
        delta = 0;
    }

    void GameLevel::release() {
        std::cout << "Level objects release\n";
         if(!objects.empty()) {
            for(auto &i : objects) {
                std::cout << "released object type: " << i->type << "\n";
                i->release();
                delete i;
            }
            objects.erase(objects.begin(), objects.end());
        }
    }

    void GameLevel::loadLevel(const std::string &filename) {
        if(!level.loadLevel(filename)) {
            std::cerr << "Error loading level..\n";
            exit(0);
        }
        int max_x = level.width * 16 - WINDOW_SIZE_WIDTH -1;
        int max_y = level.height * 16 - WINDOW_SIZE_HEIGHT -1;
        tsize = 16;
        cam.init(1280, 720, max_x, max_y);
        // free level objects
        if(!objects.empty()) {
            for(auto &i : objects) {
                i->release();
                delete i;
            }
            objects.erase(objects.begin(), objects.end());
        }
        // load level objects
        for(int i = 0; i < level.width; ++i) {
            for(int z = 0; z < level.height; ++z) {
                Tile *tile = level.at(i, z);
                if(tile != nullptr) {
                    switch(tile->layers[0]) {
                        case 1: {
                            Item *item = new Item(i, z, 1, 1, 100);
                            objects.push_back(item);
                            int index = objects.size()-1;
                            tile->layers[1] = index;
                        }
                        break;
                    }
                }
            }
        }
    }

    void GameLevel::draw(RenderObject *ro) {
        int start_col = cam.getX() / tsize;
        int end_col = start_col + (cam.getWidth() / tsize);
        int start_row = cam.getY() / tsize;
        int end_row = start_row + (cam.getHeight() / tsize);

        int cx = cam.getX();
        int cy = cam.getY();

        int off_x = -cx + start_col * tsize;
        int off_y = -cy + start_row * tsize;

        // draw background
        for(int x = start_col; x < end_col; ++x) {
            for(int y = start_row; y < end_row; ++y) {
                Tile *tile = level.at(x, y);
                if(tile != nullptr && tile->img != 0) {
                    int xx = (x - start_col) * tsize + off_x;
                    int yy = (y - start_row) * tsize + off_y;
                    ro->drawAt(images[tile->img], xx, yy);                 
                }
            }
        }       

        // draw objects
        for(int x = start_col; x < end_col; ++x) {
            for(int y = start_row; y < end_row; ++y) {
                Tile *tile = level.at(x, y);
                if(tile != nullptr && tile->layers[0] == 1) {
                    int xx = (x - start_col) * tsize + off_x;
                    int yy = (y - start_row) * tsize + off_y;
                    Item *item = dynamic_cast<Item *>(objects[tile->layers[1]]);
                    //std::ostringstream stream;
                    //stream << item->item_type;
                    //ro->drawAt(images[tile->img], xx, yy);    
                    // temporary             
                    //ro->printText(arial, xx, yy, stream.str(), Color(255,255,255));
                }
            }
        }       
    

        unsigned int tick = ro->getTicks();
        static unsigned int prev_tick = 0;
        delta = float(tick-prev_tick)/1000;
        prev_tick = tick; 
        if(ro->keyDown(Key::KEY_RIGHT)) {
            cam.move(std::min(0.009f, delta), 1.0f, 0.0f);
        } else if(ro->keyDown(Key::KEY_LEFT)) {
            cam.move(std::min(0.009f, delta), -1.0f, 0.0f);
        }
        if(ro->keyDown(Key::KEY_UP)) {
            cam.move(std::min(0.009f, delta), 0.0f, -1.0f);
        } else if(ro->keyDown(Key::KEY_DOWN)) {
            cam.move(std::min(0.009f, delta), 0.0f, 1.0f);
        }
#ifdef DEBUG_MODE
        unsigned int tc = tick / 1000;
        static unsigned int pv = 0;
        static unsigned int frame_c = 0;
        static int frame_counter = 0;
        if(tc > pv) {
            pv = tc;
            frame_counter = frame_c;
            frame_c = 0;
        } else {
            frame_c += 1;
        }
        std::ostringstream frame_count;
        frame_count << frame_counter << " FPS Camera: X: " << cam.getX() << " - Y: " << cam.getY();
        ro->printText(arial, 15, 15, frame_count.str(), Color(255,255,255));
#endif
    }
     
    void GameLevel::keydown(char key) {

  
    }
     
    void GameLevel::keyup(char key) {

    }        
}