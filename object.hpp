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
        virtual void draw(RenderObject *ro, int x, int y) = 0;
        void setImages(const std::vector<Image> &v);
        virtual void release() = 0;
        int x = 0,y = 0,cur_frame = 0, type = 0;
        std::vector<Image> frame_data;
        bool active = true;
    };


    class Item : public CObject {
    public:
        Item() = default;
        Item(int xx, int yy, int type, int item_t, int item_a);
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro, int x, int y) override;
        void release() override;
        int grab();
        int item_type = 0;
        int item_amount = 0;
    };

    class Hero : public CObject {
    public:
        Hero() = default;
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro, int x, int y) override;
        void release() override;
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
    };
}


#endif