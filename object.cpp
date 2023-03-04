#include"object.hpp"

namespace game {

    Item::Item(int xx, int yy, int t, int item_t, int item_a) : item_type{item_t}, item_amount{item_a} {
        x = xx;
        y = yy;
        type = t;   
    }

    
    void Item::init(RenderObject *ro) {

    }
    
    void Item::draw(RenderObject *ro) {

    }

    void Item::release() {

    }

    void Hero::init(RenderObject *ro) {

    }
    
    void Hero::draw(RenderObject *ro) {

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