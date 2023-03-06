#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

#include"camera.hpp"
#include"level.hpp"
#include"game.hpp"
#include"object.hpp"

#include<vector>

namespace game {
     class GameLevel : public GameObject {
    public:
        GameLevel() = default;
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro) override;
        void release(RenderObject *ro) override;
        void keydown(char key) override;
        void keyup(char key) override;  
        void loadLevel(const std::string &filename);
        void loadResources();
    protected:    
        Level level;
        Camera cam;
        std::vector<Image> images;
        std::vector<CObject *> objects;
        std::vector<Image> object_images;
        Font arial;
        int tsize;
        float delta;
        const int TILE_W=16;
        static const int WINDOW_SIZE_W = 1280/16;
        static const int WINDOW_SIZE_H = 720/16;
        RenderObject *render_object;
    };
}














#endif