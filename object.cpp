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

    void Hero::moveLeft() {
        dir = Direction::LEFT;
        if(moving_ == false) {
            moving_ = true;
            moving_index[0] = 0;
        }
    }

    void Hero::cycle_frame() {
    }

    void Hero::moveRight() {
        dir = Direction::RIGHT;
        if(moving_ == false) {
            moving_= true;
            moving_index[1] = 0;
        }
    }

    void Hero::update() {
        if(moving_ == true) {
            if(dir == Direction::RIGHT) {
                moving_index[1] ++;
                draw_x += 4;
                if(moving_index[1] >= 4) {
                    moving_index[1] = 0;
                    moving_ = false;
                    x += 1;
                }
            } else if(dir == Direction::LEFT) {
                moving_index[0] ++;
                if(draw_x > 0) {
                    draw_x -= 4;
                }
                if(moving_index[0] >= 4) {
                    moving_index[1] = 0;
                    moving_ = false;
                    x -= 1;
                }
            }
        }
    }

    void Hero::restore() {
          cur_frame = 0;
    }
    
    void Hero::moveDown(bool draw) {
        draw_y += 16;  
     }

    void Hero::jump() {

    }

    void Hero::proc_jump(Level *level, Camera *cam, float delta) {
    }

    bool Hero::isJumping() const {
        return jumping;
    }
}