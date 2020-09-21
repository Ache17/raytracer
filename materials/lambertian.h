
#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "material.h"
#include "../textures/texture.h"
#include <memory>

class lambertian : public material {
public:
    lambertian(const vec3 &color);
    lambertian(std::shared_ptr<texture> a) : _texture(a) {}
    virtual bool scatter(ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const override;


    std::shared_ptr<texture> _texture;
};


#endif //RAYTRACER_LAMBERTIAN_H
