#ifndef _OBJECT_H__
#define _OBJECT_H__

#include"game.hpp"
#include<vector>

namespace game {

    class CObject {
    public:
        CObject() = default;
        virtual ~CObject() = default;
        virtual void init(RenderObject *ro) = 0;
        virtual void draw(RenderObject *ro) = 0;

        int x,y,cur_frame;
        std::vector<Image> frame_data;
    };


    class Item : public CObject {
    public:
        Item() = default;
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro) override;

        int item_type;
        int item_amount;
    };

    class Hero : public CObject {
    public:
        Hero() = default;
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro) override;

        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
    };
}


#endif