
#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "../core/ray.h"

struct hit_record;

class material {
public:
    virtual bool scatter(ray& r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

static double schlick_approximation(double cosine, double ref_idx)
{
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1- r0) * pow(1 - cosine, 5);
}

#endif //RAYTRACER_MATERIAL_H
