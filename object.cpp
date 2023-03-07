#include"object.hpp"
#include"level.hpp"
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
        y = (720/16)-15;
        draw_x = x*16;
        draw_y = y*16;
    }
    
    void Hero::draw(RenderObject *ro, int pos_x, int pos_y) {

        assert(cur_frame >= 0 && cur_frame < left.size());

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


    void Hero::release() {
        
    }

    void Hero::moveLeft() {
        dir = Direction::LEFT;
        if(draw_x > 0) {
            draw_x -= 8;
            cycle_frame();
            int xx, yy;
            if(atPoint(draw_x, draw_y, 16, 16, xx, yy)) {
                x = xx;
                y = yy;
            }
        }
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
        draw_x += 8;
        cycle_frame();
        int xx, yy;
        if(atPoint(draw_x, draw_y, 16, 16, xx, yy)) {
            x = xx;
            y = yy;
        }
    }

    void Hero::restore() {
          cur_frame = 0;
    }
    
    void Hero::moveDown() {
        
    }
    void Hero::moveUp() {
        
    }

}