
#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H
#include "../utils/vec3.h"
#include "../core/ray.h"
#include "../materials/material.h"
#include "../core/aabb.h"

#include <memory>

class material;

struct hit_record
{
    vec3 p;
    vec3 normal;
    double t;
    double u;
    double v;
    bool front_face;
    std::shared_ptr<material> mat_ptr;

    inline void set_face_normal(ray &r, vec3 &outward_normal)
    {
        front_face = dot(r._direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(ray &r, double t_min, double t_max, hit_record &rec) = 0;
    virtual bool bounding_box(double t0, double t1, aabb &output_box) = 0;
};


#endif //RAYTRACER_HITTABLE_H
