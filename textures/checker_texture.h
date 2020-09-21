
#ifndef RAYTRACER_CHECKER_TEXTURE_H
#define RAYTRACER_CHECKER_TEXTURE_H

#include <memory>
#include "texture.h"

class checker_texture : public texture {
public:
    checker_texture(std::shared_ptr<texture> t0, std::shared_ptr<texture> t1)
            :   odd(t0), even(t1) {}

    checker_texture(vec3 col1, vec3 col2)
    {
        even = std::make_shared<solid_color>(col1);
        odd  = std::make_shared<solid_color>(col2);
    }
    vec3 value(double u, double v, vec3 &p) override
    {
        auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
            if (sines < 0)
            return odd->value(u,v, p);
        return even->value(u,v,p);
    }

    std::shared_ptr<texture> odd, even;
};


#endif //RAYTRACER_CHECKER_TEXTURE_H
