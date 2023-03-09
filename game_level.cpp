#include"game_level.hpp"
#include"window_const.hpp"
#include<sstream>
#include<iostream>
#include<string>

namespace game {

  void GameLevel::init(RenderObject *ro) {
        render_object = ro;
        delta = 0;
        loadLevel("levels/level1.lvl");
        hero.init(ro);
    }

// TODO: make load resources from text file
    void GameLevel::loadResources() {

        render_object->releaseResources();

        if(!images.empty())
            images.erase(images.begin(), images.end());

        const char *fileNames[] = {  "black.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp", "snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", "grass.bmp", 0 };
        for(uint8_t i = 0; fileNames[i] != 0; ++i) {
            std::ostringstream stream;
            stream << "./img/" << fileNames[i];
            int img = render_object->loadImage(stream.str());
            images.push_back(img);
        }

        arial = render_object->loadFont("./img/arial.ttf", 24);

        if(!object_images.empty())
            object_images.erase(object_images.begin(), object_images.end());
            
        object_images.push_back(render_object->loadImage("./img/col1.bmp"));
        object_images.push_back(render_object->loadImage("./img/col2.bmp"));
        object_images.push_back(render_object->loadImage("./img/col3.bmp"));
        object_images.push_back(render_object->loadImage("./img/col4.bmp"));
        object_images.push_back(render_object->loadImage("./img/col5.bmp"));
        object_images.push_back(render_object->loadImage("./img/col6.bmp"));
        object_images.push_back(render_object->loadImage("./img/tree.bmp"));

        const char *hero_filenames[] = {"hero1", "hero2", "hero3", "hero4", "hero_jump1", "hero_shot1", "hero_shot2", "hero_shot3", "hero_shot4", "hero_shot5", 0 };
        for(int i = 0; hero_filenames[i] != 0; ++i) {
            std::ostringstream stream;
            stream << "./img/hero/" << hero_filenames[i] << ".bmp";
            hero_images_right.push_back(render_object->loadImage(stream.str()));
            stream.str("");
            stream << "./img/hero/" << hero_filenames[i] << "_left.bmp";
            hero_images_left.push_back(render_object->loadImage(stream.str()));
        }
        hero.setImages(hero_images_left, hero_images_right);
    }

    void GameLevel::release(RenderObject *ro) {
        std::cout << "Level objects release\n";
         if(!objects.empty()) {
            for(auto &i : objects) {
                std::cout << "released object type: " << i->type << "\n";
                i->release();
                delete i;
            }
            objects.erase(objects.begin(), objects.end());
        }
        ro->releaseResources();
    }

    void GameLevel::loadLevel(const std::string &filename) {
        loadResources();
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
                        case 1: 
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7: {
                            Item *item = new Item(i, z, 1, tile->layers[0]-1, 10+(tile->layers[0]*5));
                            item->setImages(object_images);
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
        for(int x = start_col-16; x < end_col; ++x) {
            for(int y = start_row-16; y < end_row; ++y) {
                Tile *tile = level.at(x, y);
                if(tile != nullptr && tile->layers[0] > 0 && tile->layers[0] <= 7) {
                    int xx = (x - start_col) * tsize + off_x;
                    int yy = (y - start_row) * tsize + off_y;
                    //Item *item = dynamic_cast<Item *>(objects[tile->layers[1]]);
                    CObject *item = objects[tile->layers[1]];
                    item->draw(ro, xx, yy);
                }
            }
        }
        unsigned int tick = ro->getTicks();
        static unsigned int prev_tick = 0;
        delta = float(tick-prev_tick)/1000;
        unsigned int timeout = tick-prev_tick;
        static unsigned int amt = 0;
        amt += timeout;
        prev_tick = tick; 
        if(ro->keyDown(Key::KEY_RIGHT)) {
            if(amt > 10) {
                if(hero.x < HALF_MAP_W) {
                    hero.moveRight();
                    hero.update();
                } else {
                     int hx = hero.x+cam.getCamX();
                     if(hx >= level.width-HALF_MAP_W-1) {
                        if(hero.draw_x < 1280-48) {
                            hero.moveRight();
                            hero.update();
                        }
                     } else {
                       cam.move(std::min(0.009f, delta), 1.0f, 0.0f);
                     }
                }
            }
        } else if(ro->keyDown(Key::KEY_LEFT)) {
                if(amt > 10) {
                    if(cam.getCamX() == 0 && hero.x > 0) {
                        hero.moveLeft();
                        hero.update();
                    } else {
                        cam.move(std::min(0.009f, delta), -1.0f, 0.0f);
                    }
                }   
        }
        int xx, yy;
        hero.draw(ro, xx, yy);
        if(amt > 10)
            amt = 0;


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
        frame_count << frame_counter << " FPS Camera: X: " << cam.getX() << " - Y: " << cam.getY() << " HX: "<< hero.x << " HY: " << hero.y;
        ro->printText(arial, 15, 15, frame_count.str(), Color(255,255,255));
#endif
    }

    bool GameLevel::checkPoint(const Point &p) {
        return false;
    }

    void GameLevel::keydown(char key) {

  
    }
     
    void GameLevel::keyup(char key) {

    }        
}