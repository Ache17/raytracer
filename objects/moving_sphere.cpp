
#include "moving_sphere.h"

bool moving_sphere::hit(ray &r, double t_min, double t_max, hit_record &rec) {

    vec3 oc = r._origin - this->center(r._time);
    auto a = r._direction.length_squared();
    auto half_b = dot(oc, r._direction);
    auto c = oc.length_squared() - _radius * _radius;
    auto discr = half_b * half_b - a * c;

    if (discr > 0) {
        auto root = sqrt(discr);

        auto tmp = (-half_b - root) / a;
        if (tmp < t_max && tmp > t_min)
        {
            rec.t = tmp;
            rec.p = r.at(tmp);
            vec3 outward_normal = (rec.p - this->center(r._time)) / _radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = this->_mat_ptr;
            return true;
        }

        tmp = (-half_b + root) / a;
        if (tmp < t_max && tmp > t_min)
        {
            rec.t = tmp;
            rec.p = r.at(tmp);
            vec3 outward_normal = (rec.p - this->center(r._time)) / _radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = this->_mat_ptr;
            return true;
        }
    }
    return false;
}

// linear interpolation between center_start and center_end ( controlled by t)
vec3 moving_sphere::center(double t) const  {
    return this->_center_start + (t - _t_start) / (_t_end - _t_start) * (this->_center_end - this->_center_start);
}

bool moving_sphere::bounding_box(double t0, double t1, aabb &output_box) {
    aabb box0(center(t0) - vec3(_radius, _radius, _radius),
              center(t0) + vec3(_radius, _radius, _radius));
    aabb box1(center(t1) - vec3(_radius, _radius, _radius),
              center(t1) + vec3(_radius, _radius, _radius));

    output_box = surrounding_box(box0, box1);
    return true;
}
