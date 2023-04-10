#ifndef __PARTICLES_H__
#define __PARTICLES_H__
#include<list>
#include<vector>

namespace game {


    struct RenderObject;

    class Particle {
    public:
        int x,y,type,dir;
    };

    class ParticleEmiter {
    public:
        ParticleEmiter() = default;
        void setImages(const std::vector<int> &v);
        void addParticle(int x, int y, int type, int dir);
        void draw(RenderObject *ro);
    protected:
        std::list<Particle> particles;  
        std::vector<int> images;  
    };

}

#endif