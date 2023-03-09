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
        y = (720/16)/2-1;
        draw_x = x*16;
        draw_y = y*16;
        jumping = false;
        jump_index = 0;
    }
    
    void Hero::draw(RenderObject *ro, int pos_x, int pos_y) {
        if(dir == Direction::LEFT)
            ro->drawAt(left[cur_frame], pos_x, pos_y);
        else if(dir == Direction::RIGHT)
            ro->drawAt(right[cur_frame],pos_x, pos_y);

        std::cout << x << ":" << pos_x << " " << y << ":" << pos_y << "\n";

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

    void Hero::moveLeft() {
        dir = Direction::LEFT;
        if(moving_ == false)
            moving_ = true;
    }

    void Hero::cycle_frame() {
      if(move_right == true) {
            cur_frame ++;
            if(cur_frame >= 3) {
                move_right = false;
                cur_frame = 3;
            }
        } else {
            cur_frame --;
            if(cur_frame <= 0) {
                move_right = true;
                cur_frame = 0;
            }
        }
    }

    void Hero::moveRight() {
        dir = Direction::RIGHT;
        if(moving_ == false)
            moving_ = true;

    }

    void Hero::update() {
        if(moving_ == true) {
            if(dir == Direction::RIGHT) {
                draw_x += 8;
                cycle_frame();
                moving_index[0] += 1;
                if(moving_index[0] >= 2) {
                    moving_index[0] = 0;
                    moving_ = false;
                    x += 1;
                }
            } else if(dir == Direction::LEFT) {
                if(x > 0) draw_x -= 8;
                cycle_frame();
                moving_index[1] += 1;
                if(moving_index[1] >= 2) {
                    moving_index[1] = 0;
                    moving_ = false;
                    if(x > 0) x -= 1;
                }
            }
        }
    }

    void Hero::restore() {
          cur_frame = 0;
    }
    
    void Hero::moveDown(bool draw) {
        cur_frame = 4;
        if(draw) {
            draw_y += 16;
            y += 1;
        }
    }

    void Hero::jump() {
       if(jumping == false) {
            jumping = true;   
            jump_index = 0;
       }
    }

    void Hero::proc_jump(Level *level, Camera *cam, float delta) {
        if(jumping == true) {
            jump_index += 1;
            cur_frame = 4;
            if(level->checkRect(Rect(x+(cam->getX()/16), (y+(cam->getY()/16)), 2, 4))) {
                 if(y > 0) {
                    if(cam->getY() <= 0) {
                        draw_y -= 16;
                        y -= 1;
                    }
                    else {
                        cam->move(std::min(0.009f, delta), 0.0f, -1.0f);
                    }
                    cur_frame = 4;        
                }
            }
            if(jump_index >= 14) {
                jump_index = 0;
                grounded = false;
                jumping = false;
            }            
        } else if(grounded == false)
            cur_frame = 4;
    }

    bool Hero::isJumping() const {
        return jumping;
    }
}