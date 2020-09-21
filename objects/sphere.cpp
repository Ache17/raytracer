
#include "sphere.h"
#include "../utils/util.h"

bool sphere::hit( ray &r, double tmin, double tmax, hit_record &rec)  {
    vec3 oc = r._origin - this->center;
    auto a = r._direction.length_squared();
    auto half_b = dot(oc, r._direction);
    auto c = oc.length_squared() - radius * radius;
    auto discr = half_b * half_b - a * c;

    if (discr > 0) {
        auto root = sqrt(discr);

        auto tmp = (-half_b - root) / a;
        if (tmp < tmax && tmp > tmin)
        {
            rec.t = tmp;
            rec.p = r.at(tmp);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.mat_ptr = this->mat_ptr;

            rec.p = rec.p + 0.01 * rec.normal;
            return true;
        }

        tmp = (-half_b + root) / a;
        if (tmp < tmax && tmp > tmin)
        {
            rec.t = tmp;
            rec.p = r.at(tmp);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.mat_ptr = this->mat_ptr;

            rec.p = rec.p + 0.01 * rec.normal;
            return true;
        }
    }
    return false;
}

bool sphere::bounding_box(double t0, double t1, aabb &output_box) {
    output_box= aabb(center - vec3(radius, radius, radius),
                     center + vec3(radius, radius, radius));
    return true;
}
