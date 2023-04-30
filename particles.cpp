#include"particles.hpp"
#include"game.hpp"

namespace game {

    // add new particle
    void ParticleEmiter::addParticle(int x, int y, int type, int dir) {
        particles.push_back( { x,y,type,dir } );
    }

    // set particle images
    void ParticleEmiter::setImages(const std::vector<int> &v) {
        if(!images.empty()) {
            images.erase(images.begin(), images.end());
        }
        std::copy(v.begin(), v.end(), std::back_inserter(images));
    }
}