#include "aabb.h"

aabb surrounding_box(aabb box0, aabb box1) {
    vec3 small(fmin(box0._max.x(), box1._min.x()),
               fmin(box0._min.y(), box1._min.y()),
               fmin(box0._min.z(), box1._min.z()));

    vec3 big(fmax(box0._max.x(), box1._max.x()),
             fmax(box0._max.y(), box1._max.y()),
             fmax(box0._max.z(), box1._max.z()));

    return aabb(small,big);
}

