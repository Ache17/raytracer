
#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.h"
#include <memory>


class sphere : public hittable {
public:
    sphere() {}
    sphere(vec3 cen, double r, std::shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m)
    {}
    virtual bool hit(ray &r, double tmin, double tmax, hit_record &rec) override;
    bool bounding_box(double t0, double t1, aabb &output_box) override;
    vec3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;
};


#endif //RAYTRACER_SPHERE_H
