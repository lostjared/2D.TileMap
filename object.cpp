#include"object.hpp"
#include"level.hpp"
#include"camera.hpp"
#include<iostream>

namespace game {

    void CObject::setImages(const std::vector<Image> &v) {

        if(!frame_data.empty())
            frame_data.erase(frame_data.begin(), frame_data.end());

        std::copy(v.begin(), v.end(), std::back_inserter(frame_data));
    }


    Item::Item(int xx, int yy, int t, int item_t, int item_a) : item_type{item_t}, item_amount{item_a} {
        x = xx;
        y = yy;
        type = t;  
        active = true; 
    }

    
    void Item::init(RenderObject *ro) {

    }
    
    void Item::draw(RenderObject *ro, int x, int y) {
        if(active) ro->drawAt(frame_data[item_type], x, y);
    }

    int Item::grab() {
        active = false;
        return item_amount;
    }

    void Item::release() {

    }

    void Hero::init(RenderObject *ro) {
        cur_frame = 0;
        dir = Direction::RIGHT;
        x = 5;
        y = (720/16)/2-4;
        draw_x = x*16;
        draw_y = y*16;
        jumping = false;
        jump_index = 0;
        grounded = false;
    }
    
    void Hero::draw(RenderObject *ro, int pos_x, int pos_y) {
        if(dir == Direction::LEFT)
            ro->drawAt(left[cur_frame], draw_x, draw_y);
        else if(dir == Direction::RIGHT)
            ro->drawAt(right[cur_frame],draw_x, draw_y);

    }

    void Hero::setImages(const std::vector<Image> &vl, const std::vector<Image> &vr) {
        if(!left.empty())
            left.erase(left.begin(), left.end());
        if(!right.empty())
            right.erase(right.begin(), right.end());

        std::copy(vl.begin(), vl.end(), std::back_inserter(left));
        std::copy(vr.begin(), vr.end(), std::back_inserter(right));
    }

    void Hero::set() {
        draw_x = x*16;
        draw_y = y*16;
    }

    void Hero::release() {
        cur_frame = 0;
    }

    void Hero::moveLeft(bool scroll) {
        if(moving_ == false) {
            dir = Direction::LEFT;
            moving_ = true;
            scroll_map[0] = scroll;
            moving_index[0] = 0;
        }
    }

    void Hero::moveRight(bool scroll) {
        if(moving_ == false) {
            dir = Direction::RIGHT;
            moving_= true;
            scroll_map[1] = scroll;
            moving_index[1] = 0;
        }
    }

    void Hero::moveDown(bool scroll) {
        if(grounded == false) {
            grounded = true;
            moving_index[2] = 0;
            scroll_map[2] = scroll;
        }
     }


    void Hero::cycle_frame() {
        if(move_right == true) {
            cur_frame ++;
            if(cur_frame >= 3) {
                cur_frame = 3;
                move_right = false;
            }
        } else {
            cur_frame--;
            if(cur_frame <= 0) {
                cur_frame = 0;
                move_right = true;
            }
        }
    }

    void Hero::update(Camera *cam) {

        if(moving_ == true) {
            if(dir == Direction::RIGHT) {
                if(scroll_map[1] == false) {
                    draw_x += 8;
                    cycle_frame();
                    moving_index [1] ++;
                    if(moving_index[1] >= 2) {
                        moving_index[1] = 0;
                        moving_ = false;
                        x += 1;
                        cur_frame = 0;
                    }
                } else {
                    cam->move(0.5f, 1.0f, 0.0f);
                    moving_index[1] ++;
                    if(moving_index[1] >= 2 && (cam->getX()%16)==0) {
                        moving_index[1] = 0;
                        moving_ = false;
                    }
                    cycle_frame();
                }

            } else if(dir == Direction::LEFT) {
                if(scroll_map[0] == false) {
                    draw_x -= 8;
                    cycle_frame();
                    moving_index [0] ++;
                    if(moving_index[0] >= 2) {
                        moving_index[0] = 0;
                        moving_ = false;
                        cur_frame = 0;
                        x -= 1;
                    }
                } else {
                    cam->move(0.5f, -1.0f, 0.0f);
                    cycle_frame();
                    moving_index[0] ++;
                    if(moving_index[0] >= 2 && (cam->getX()%16==0)) {
                        moving_index[0] = 0;
                        moving_ = false;
                        cur_frame = 0;
                    }
                    
                }
            }
        }      
    }

    void Hero::updateDown(Level *level, Camera *cam) {

        
        if(jumping == true) {
            bool dir[3];
            int hx = x+cam->getCamX();
            int hy = y+cam->getCamY();

            dir[0] = level->checkRect(Rect(hx, hy-1, 1, 3));
            if(dir[0] == false) {
                jumping = false;
                grounded = false;
                falling = true;
                jump_height[0] = jump_height[1] = 0;
                return;
            }
        }

        if(jumping == true) {
            if(cam->getCamY() == 0) {
                moveUp(false, cam);
                jump_height[0] ++;
                if((jump_height[0]%10) == 0) {
                    jump_height[0] = 0;
                    jumping = false;
                    grounded = false;
                    falling = true;
                }
            }
            else {
                moveUp(true, cam);
                jump_height[0] ++;
                if(jump_height[0]%10== 0) {
                    jump_height[0] = 0;
                    jumping = false;
                    grounded = false;
                    falling = true;
                }
            } 
        } else if(grounded == true) {
            if(scroll_map[2] == false) {
                draw_y += 8;
                cur_frame = 4;
                moving_index[2] ++;
                if((moving_index[2]%2) == 0) {
                    moving_index[2] = 0;
                    cur_frame = 4;
                    grounded = false;
                    y += 1;
                }
            } else {
                cur_frame = 4;
                moving_index[2] ++;
                cam->move(0.5f, 0.0f, 1.0f);
                if((moving_index[2]%2) == 0 && (cam->getY()%16)==0) {
                    moving_index[2] = 0;
                    cur_frame = 4;
                    grounded = false;
                }
            }
        } 
    }

    void Hero::restore() {
          cur_frame = 0;
    }

    void Hero::moveUp(bool scroll, Camera *cam) {
        if(scroll == false) {
            draw_y -= 16;
            cur_frame = 4;
             y --;
        } else {
            cam->move(1.0f, 0.0f, -1.0f);
            cur_frame = 4;
        }
    }
    void Hero::jump() {
        if(jumping == false && grounded == false) {
            jumping = true;
            jump_index = 0;
        }
    }

    void Hero::proc_jump(Level *level, Camera *cam) {

    }

    bool Hero::isJumping() const {
        return jumping;
    }
}