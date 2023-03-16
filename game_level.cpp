#include"game_level.hpp"
#include"window_const.hpp"
#include<sstream>
#include<iostream>
#include<string>
#include<fstream>

namespace game {

  void GameLevel::init(RenderObject *ro) {
        render_object = ro;
        delta = 0;
        hero.init(ro);
    }

    void GameLevel::loadResources(const std::string &gfx_file) {
    
        std::fstream file;
        file.open(gfx_file, std::ios::in | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error could not open graphics file: " << gfx_file << "\n";
            exit(EXIT_FAILURE);
        }

        uint32_t magic = 0;
        file.read(reinterpret_cast<char*>(&magic), sizeof(magic));

        if(magic != 0x421) {
            std::cerr << "game: Invalid resource file...\n";
            exit(EXIT_FAILURE);
        }

        std::cout << "game: Loading resource file: " << gfx_file << "\n";

        while(!file.eof()) {
            uint32_t len;
            file.read(reinterpret_cast<char*>(&len), sizeof(len));
            if(file) {
                char *tmp = new char [len+1];
                file.read(reinterpret_cast<char*>(tmp), len);
                tmp[len] = 0;
                std::string filename;
                filename = tmp;
                delete [] tmp;
                uint32_t index = 0, solid = 0, obj = 0, length = 0;
                file.read(reinterpret_cast<char*>(&index), sizeof(uint32_t));
                file.read(reinterpret_cast<char*>(&solid), sizeof(uint32_t));
                file.read(reinterpret_cast<char*>(&obj), sizeof(uint32_t));
                file.read(reinterpret_cast<char*>(&length), sizeof(uint32_t));
                std::cout << "reading file: " << filename  << " of size: " << length << " index: " << index << " solid: " << solid << " obj: " << obj << "\n";
                char *buffer = new char [ length + 1 ];
                file.read(buffer, length);
                // read image
                Image img = render_object->loadImage(buffer, length, Color(255, 255, 255));

                switch(obj) {
                    case 0:
                        images.push_back(img);
                        break;
                    case 1:
                        object_images.push_back(img);
                        break;
                    case 2:
                        hero_images_right.push_back(img);
                        break;
                    case 3:
                        hero_images_left.push_back(img);
                        break;
                }
                
                delete [] buffer;
            }
        } 
        file.close();    
    }

    void GameLevel::loadResources() {
        /*
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

        if(!hero_images_left.empty())
            hero_images_left.erase(hero_images_left.begin(), hero_images_left.end());

        if(!hero_images_right.empty())
            hero_images_right.erase(hero_images_right.begin(), hero_images_right.end());
         


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
      
        */
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

        render_object->releaseResources();
        arial = render_object->loadFont("./img/arial.ttf", 24);

       if(!images.empty())
            images.erase(images.begin(), images.end());

        if(!object_images.empty())
            object_images.erase(object_images.begin(), object_images.end());

        if(!hero_images_left.empty())
            hero_images_left.erase(hero_images_left.begin(), hero_images_left.end());

        if(!hero_images_right.empty())
            hero_images_right.erase(hero_images_right.begin(), hero_images_right.end());


        loadResources("./img/level.gfx");
        loadResources("./img/hero.gfx");

        hero.setImages(hero_images_left, hero_images_right);

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

        if(ro->keyDown(Key::KEY_A)) {
            if(amt > 10) {
                hero.jump();
            }
        }

        if(ro->keyDown(Key::KEY_RIGHT)) {
            if(amt > 10) {
                int hx = hero.x+cam.getCamX();
                int hy = hero.y+cam.getCamY();
                bool solid = level.checkRect(Rect(hx+1, hy, 1, 3));
                if(solid) {
                    if(hero.x <= HALF_MAP_W) {
                        hero.moveRight(false);                
                    } else {
                        int hx = hero.x+cam.getCamX();
                        if(hx >= level.width-HALF_MAP_W-1) {
                            if(hero.draw_x < 1280-48) {
                                hero.moveRight(false);
                            }
                        } else
                            hero.moveRight(true);
                    }
                }
            }
        } else if(ro->keyDown(Key::KEY_LEFT)) {
                if(amt > 10) {
                    int hx = hero.x+cam.getCamX();
                    int hy = hero.y+cam.getCamY();
                    bool solid = level.checkRect(Rect(hx-1, hy, 2, 3));
                    if(solid) {
                        if((cam.getX() == 0 && hero.x > 0 && hero.x <= HALF_MAP_W) || hero.x > 40) {
                            hero.moveLeft(false);
                        }  
                        else {
                            hero.moveLeft(true);
                        }
                    }
                }   
        } else {
            if(hero.grounded == false)
                hero.restore();
        }
        if(amt > 10) {
            hero.update(&cam); 
            int hx = hero.x+cam.getCamX();
            int hy = hero.y+cam.getCamY();
            bool directions[5];
            directions[0] = level.checkRect(Rect(hx, hy, 2, 4));
            directions[1] = level.checkRect(Rect(hx, hy+1, 2, 4));
            if(directions[0]) {
                    if(hero.y < HALF_MAP_H) {
                        hero.moveDown(false);                
                    } else {
                        int hy = hero.y+cam.getCamY();
                        if(hy >= level.height-HALF_MAP_H-2) {
                            if(hero.draw_y < 720-64) {
                                hero.moveDown(false);
                            }
                        } else
                            hero.moveDown(true);
                    }
            } 
            amt = 0; 
            hero.updateDown(&cam);
        }

        if(hero.grounded == true)
            hero.cur_frame = 4;

        int xx = 0, yy = 0;
        hero.draw(ro, xx, yy);
        

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