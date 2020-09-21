
#ifndef RAYTRACER_MOVING_SPHERE_H
#define RAYTRACER_MOVING_SPHERE_H


#include "hittable.h"

class moving_sphere : public hittable {
public:
    moving_sphere(vec3 center_start, vec3 center_end, double t_start, double t_end,
                  double r, std::shared_ptr<material> m)
                  : _center_start(center_start), _center_end(center_end), _t_start(t_start), _t_end(t_end),
                  _radius(r), _mat_ptr(m)
    {}
    bool hit(ray &r, double t_min, double t_max, hit_record &rec) override;
    bool bounding_box(double t0, double t1, aabb &output_box) override;
    vec3 center(double t) const ;

    vec3 _center_start, _center_end;
    double _t_start, _t_end;
    double _radius;
    std::shared_ptr<material> _mat_ptr;
};



#endif //RAYTRACER_MOVING_SPHERE_H
