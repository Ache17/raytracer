
#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "ray.h"

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio,
           double aperture, double focus_dist, double t_start = 0, double t_end = 0);
    ray get_ray(double u, double v);

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal, vertical;
    vec3 u, v, w;
    double aperture, focus_dist, aspect_ratio;
    double lens_radius;
    double t_start, t_end;
};


#endif //RAYTRACER_CAMERA_H
