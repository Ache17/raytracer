
#ifndef RAYTRACER_NOISE_TEXTURE_H
#define RAYTRACER_NOISE_TEXTURE_H
#include "texture.h"
#include "../utils/perlin.h"

class noise_texture : public texture {
public:
    noise_texture()
    {
        this->_scale = 1;
    }
    noise_texture(double scale)
    {
        this->_scale = scale;
    }

    vec3 value(double u, double v, vec3 &p) override
    {
        // return vec3(1,1,1) * 0.5 * (1.0 + noise.noise(this->_scale * p));
        return vec3(1,1,1) * noise.turb(p);
    }
    perlin noise;
    double _scale;
};


#endif //RAYTRACER_NOISE_TEXTURE_H
