#include"game_level.hpp"
#include"gfx_data.hpp"
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
        newGame();
    }

    int GameLevel::hX() const {
        return hero.x + cam.getCamX();
    }
     
    int GameLevel::hY() const {
        return hero.y + cam.getCamY();
    }


    void GameLevel::newGame() {
        score = 0;
        lives = 10;
    }

    void GameLevel::resetLevel() {
        cam.reset();
        hero.reset();
        lives --;
        if(lives <= 0) {
            // game over
        }
        // reset items / objects
    }

    void GameLevel::nextLevel() {
        
    }

    void GameLevel::loadResources(const std::string &gfx_file) {  
            GfxData data;
            if(data.open(gfx_file)) {
                std::cout << "game: Opened resource file: " << gfx_file << "\n";
                data.load([&](int obj, char *buffer, int size) {
                    switch(obj) {
                        case 0:
                            images.push_back(render_object->loadImage(buffer, size, Color(255, 255, 255)));
                            break;
                        case 1:
                            object_images.push_back(render_object->loadImage(buffer, size, Color(255, 255, 255)));
                            break;
                        case 2:
                            hero_images_right.push_back(render_object->loadImage(buffer, size, Color(255, 255, 255)));
                            break;
                        case 3:
                            hero_images_left.push_back(render_object->loadImage(buffer, size, Color(255, 255, 255)));
                            break;
                        case 4:
                            stars.push_back(render_object->loadImage(buffer, size, Color(0,0,0)));
                            break;
                        case 5:
                            g_img_r.push_back(render_object->loadImage(buffer, size, Color(255,255,255)));
                            break;
                        case 6:
                            g_img_l.push_back(render_object->loadImage(buffer, size, Color(255,255,255)));
                            break;
                    }
                });
            } else {
                std::cout << "game: Could not open resource file: " << gfx_file << "....\n";
                exit(EXIT_FAILURE);
            }
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

    void GameLevel::loadLevel(const std::string &filename, const std::string &gfx_, const std::string &background) {

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


        loadResources(gfx_);
        loadResources("./img/hero.gfx");
        loadResources("./img/enemy1.gfx");

        hero.setImages(hero_images_left, hero_images_right);

        if(!shot.empty()) 
            shot.erase(shot.begin(), shot.end());

        shot.push_back(render_object->loadImage("./img/shot.bmp"));

        emiter.setImages(shot);

        if(!level.loadLevel(filename)) {
            std::cerr << "Error loading level..\n";
            exit(0);
        }
        
        bg_img = render_object->loadImage(background);        

        if(background.find("bg1.bmp") != std::string::npos) {
            if(!stars.empty())
                stars.erase(stars.begin(), stars.end());

            loadResources("./img/bg1.gfx");
            field.setImages(stars);
            field.init(25);
            field_enabled = true;
        } else {
            field_enabled = false;
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
                        case 8: {
                            /*Enemy *e = new Enemy(i, z, 8);
                            e->setImages(g_img_l, g_img_r);
                            objects.push_back(e);
                            int index = objects.size()-1;
                            tile->layers[1] = index;*/
                        } 
                        break;
                    }
                }
            }
        }
    }

    void GameLevel::procParticles() {
        for(auto i = emiter.particles.begin(); i != emiter.particles.end(); ++i) {
            if(i->dir == 0) {
                if(i->x > 0) i->x--;
                if(level.checkRect(Rect(i->x, i->y, 1, 1)) == false) {
                    emiter.particles.erase(i);
                    break;
                }
            }
            else{
                if(i->x < level.width) i->x++;
                if(level.checkRect(Rect(i->x, i->y, 1, 1)) == false) {
                    emiter.particles.erase(i);
                    break;
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
        ro->drawAt(bg_img, 0, 0);
        
        if(field_enabled == true) {  
            field.draw(ro);
        }


        // draw background
        for(int x = start_col; x < end_col; ++x) {
            for(int y = start_row; y < end_row; ++y) {
                Tile *tile = level.at(x, y);
                if(tile != nullptr && tile->img != 0) {
                    int xx = (x - start_col) * tsize + off_x;
                    int yy = (y - start_row) * tsize + off_y;
                    if(tile->solid != 2 && tile->solid != 3)
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


        // draw particles
        for(int x = start_col; x < end_col; ++x) {
            for(int y = start_row; y < end_row; ++y) {
                Tile *tile = level.at(x, y);
                if(tile != nullptr) {
                    int xx = (x - start_col) * tsize + off_x;
                    int yy = (y - start_row) * tsize + off_y;
                    for(auto &i : emiter.particles) {
                        if(i.x == x && i.y == y) {
                            ro->drawAt(shot[i.type], xx, yy);                 
                        }
                    }
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

        if(amt > 20) {
            field.proc();
        }

        if(ro->keyDown(Key::KEY_A)) {
            if(amt > 20) {
                if(hero.falling == false) 
                    hero.jump();
            }
        } else if(ro->keyDown(Key::KEY_S)) {
            if(amt > 20) {
                hero.fire();
            }
        }


        if(amt > 20) {
            procParticles();
        }

        if(hero.shot == false) {

           if(ro->keyDown(Key::KEY_RIGHT)) {
                if(amt > 20) {
                    int hx = hero.x+cam.getCamX();
                    int hy = hero.y+cam.getCamY();
                    bool solid = level.checkRect(Rect(hx+1, hy, 1, 3));

                    if(solid) {     

                        if(hero.falling == true && level.check({Point{hx+2, hy+4}, Point{hx+2, hy}, Point{hx+1, hy}})) {
                        } else 
                        if(hero.x <= HALF_MAP_W) {
                            hero.moveRight(false);                
                        } else {
                            int hx = hero.x+cam.getCamX();
                            if(hx >= level.width-HALF_MAP_W-1) {
                                if(hero.draw_x < 1280-48) {
                                    hero.moveRight(false);
                                }
                            } else {
                                hero.moveRight(true);
                                hero.draw_x = hero.x*16;
                                hero.draw_y = hero.y*16;
                            }
                        }
                    } else {
                        if(hero.falling == false)
                            hero.cur_frame = 0;
                    }
                }
            } else if(ro->keyDown(Key::KEY_LEFT)) {
                    if(amt > 20) {
                        int hx = hero.x+cam.getCamX();
                        int hy = hero.y+cam.getCamY();
                        bool solid = level.checkRect(Rect(hx-1, hy, 1, 3));
                        if(solid) {
                            if(hero.falling == true && level.check({Point{hx-1, hy+4}, Point{hx-1, hy}})) {

                            } else
                            if((cam.getX() == 0 && hero.x > 0 && hero.x <= HALF_MAP_W) || hero.x > 40) {
                                hero.moveLeft(false);
                            }  
                            else {
                                hero.moveLeft(true);
                                hero.draw_x = hero.x*16;
                                hero.draw_y = hero.y*16;
                            }
                        } else {
                            if(hero.falling == false)
                                hero.cur_frame = 0;
                        }
                    }   
            } else {
                if(hero.grounded == false)
                    hero.restore();
            }

            if(level.checkRectForType(Rect(hX(), hY(), 2, 4), 2)) {
                resetLevel();
            } else if(level.checkRectForType(Rect(hX(), hY(), 2, 4), 3)) {
                nextLevel();
            }

            if(amt > 20) {
                hero.update(&cam); 
                int hx = hero.x+cam.getCamX();
                int hy = hero.y+cam.getCamY();
                bool directions[5];
                directions[0] = level.checkRect(Rect(hx, hy+1, 1, 3));
                directions[1] = level.checkRect(Rect(hx, hy+1, 2, 4));
                if(directions[0]) {
                        hero.falling = true;
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
                } else {
                    hero.falling = false;
                    hero.jump_height[0] = hero.jump_height[1] = 0;
                } 
                amt = 0; 
                hero.updateDown(&level, &cam);
            }

            if(hero.grounded == true || hero.falling == true)
                hero.cur_frame = 4;

            } else {
                if(amt > 100) {
                    hero.cur_frame ++;
                    if(hero.cur_frame >= 8) {
                        hero.shot = false;

                    if(hero.dir == Direction::RIGHT)
                        emiter.addParticle(hX()+2,hY()+2, 0, 1);
                    else
                        emiter.addParticle(hX()-1,hY()+2, 0, 0);

                }
                 amt = 0;
            }
        }
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
        frame_count << frame_counter << " FPS Camera: X: " << cam.getX() << " - Y: " << cam.getY() << " HX: "<< hero.x << "/" << hX() << " HY: " << hero.y << "/" << hY();
        ro->printText(arial, 15, 15, frame_count.str(), Color(255,255,255));
#endif
        std::ostringstream score_stream;
        score_stream << "Lives: " << lives << " Score: " << score; 
        ro->printText(arial, 25, 50, score_stream.str(), Color(255, 255, 255));
    }

    bool GameLevel::checkPoint(const Point &p) {
        return false;
    }

    void GameLevel::keydown(char key) {
#ifdef DEBUG_MODE
        if(key == 'r' || key == 'R')
            resetLevel();
#endif
    }
     
    void GameLevel::keyup(char key) {

    }        
}