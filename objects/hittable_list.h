
#ifndef RAYTRACER_HITTABLE_LIST_H
#define RAYTRACER_HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"

class hittable_list : public hittable {
public:
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }
    virtual bool hit(ray & r, double tmin, double tmax, hit_record &rec) override;
    bool bounding_box(double t0, double t1, aabb &output_box) override;
    std::vector<std::shared_ptr<hittable>> objects;
};


#endif //RAYTRACER_HITTABLE_LIST_H
