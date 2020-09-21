
#include "camera.h"
#include "../utils/util.h"
#include "../utils/sampler.h"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture,
               double focus_dist, double t_start, double t_end) {

    this->t_start = t_start;
    this->t_end = t_end;

    auto theta = d2r(vfov);
    auto h = tan(theta / 2);

    this->aspect_ratio = aspect_ratio;
    auto viewport_height = 2.0 * h;
    auto viewport_width  = aspect_ratio * viewport_height;
    auto focal_length = 1;

    // create orthonormal basis set
    this->w = unit_vector(lookfrom - lookat);
    this->u = unit_vector(cross(vup, w));
    this->v = cross(w, u);


    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical   = focus_dist * viewport_height * v;
    lower_left_corner = origin - 0.5 * horizontal - 0.5 * vertical - focus_dist * w;

    lens_radius = aperture / 2.;
}

ray camera::get_ray(double s, double t) {

    vec3 rd = lens_radius * sampler::sampleUnitDisk();
    vec3 offset = u * rd.x() + v * rd.y();

    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset,
               random(this->t_start, this->t_end));
}
