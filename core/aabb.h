
#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H
#include "../utils/vec3.h"
#include "ray.h"

class aabb {
public:
    aabb() {}
    aabb(vec3 a, vec3 b) : _min(a), _max(b) {}
    bool hit(ray &r, double tmin, double tmax)
    {
        for (int a = 0; a < 3; ++a)
        {
            auto invD = 1. /  r._direction[a];
            auto t0 = (_min[a] - r._origin[a]) * invD;
            auto t1 = (_max[a] - r._origin[a]) * invD;
            if (invD < .0f)
            {
                std::swap(t0, t1);
            }
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if (tmax <= tmin)
                return false;
        }
        return true;
    }

    vec3 _min, _max;
};

aabb surrounding_box(aabb box0, aabb box1);

#endif //RAYTRACER_AABB_H
