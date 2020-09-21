
#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H
#include "material.h"

class dielectric : public material{
public:
    dielectric(double ri) : ref_idx(ri) {}
    bool scatter(ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const override;



    double ref_idx;
};


#endif //RAYTRACER_DIELECTRIC_H
