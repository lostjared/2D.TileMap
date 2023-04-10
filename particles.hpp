#ifndef __PARTICLES_H__
#define __PARTICLES_H__
#include<list>


namespace game {


    class Particle {
    public:
        int x,y,type,dir;
    };

    class ParticleEmiter {
    public:
        ParticleEmiter() = default;
        void addParticle(int x, int y, int type, int dir);
    protected:
        std::list<Particle> particles;    
    };

}

#endif