#include"object.hpp"
#include<iostream>

namespace game {

    void CObject::setImages(const std::vector<Image> &v) {
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

    void Item::release() {

    }

    void Hero::init(RenderObject *ro) {

    }
    
    void Hero::draw(RenderObject *ro, int x, int y) {

    }

    void Hero::release() {
        
    }

    void Hero::moveLeft() {

    }

    void Hero::moveRight() {
        
    }
    
    void Hero::moveDown() {
        
    }
    void Hero::moveUp() {
        
    }

}