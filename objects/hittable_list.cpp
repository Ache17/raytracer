
#include "hittable_list.h"

bool hittable_list::hit(ray &r, double tmin, double tmax, hit_record &rec)  {
    hit_record rec_;
    bool hit_anything = false;
    auto closest_so_far = tmax;

    for (auto &obj : objects)
    {
        if (obj->hit(r, tmin, closest_so_far, rec_))
        {
            hit_anything = true;
            closest_so_far = rec_.t;
            rec = rec_;
        }
    }
    return hit_anything;
}

bool hittable_list::bounding_box(double t0, double t1, aabb &output_box) {
    if (objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto & obj : objects)
    {
        if (!obj->bounding_box(t0, t1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }
    return false;
}
