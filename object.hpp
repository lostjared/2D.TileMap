#ifndef _OBJECT_H__
#define _OBJECT_H__

#include"game.hpp"
#include<vector>

namespace game {

    class Camera;
    class Level;

    enum class Direction { LEFT=1, RIGHT, UP, DOWN };

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
        Direction dir;
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
        void setImages(const std::vector<Image> &vl, const std::vector<Image> &vr);
        void draw(RenderObject *ro, int x, int y) override;
        void release() override;
        void moveLeft(bool scroll);
        void moveRight(bool scroll);
        void moveDown(bool draw);
        void restore();
        void cycle_frame();
        void jump();
        void proc_jump(Level *level, Camera *cam, float delta);
        bool isJumping() const;
        void update(Camera *cam);
        void updateDown(Camera *cam);
        void set();
        bool grounded = false;
        int draw_x = 0, draw_y = 0;
    protected:
        std::vector<Image> left, right;
        bool move_right = true;
        bool jumping = false;
        int jump_index = 0;
        bool moving_ = false;
        int moving_index[4] = {0};
        bool scroll_map[4] =  {false};        
    };

}


#endif