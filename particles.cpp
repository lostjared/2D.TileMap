#include"particles.hpp"

namespace game {

    void ParticleEmiter::addParticle(int x, int y, int type, int dir) {
        particles.push_back( { x,y,type,dir } );
    }

}