
#ifndef RAYTRACER_BVH_NODE_H
#define RAYTRACER_BVH_NODE_H


#include "hittable_list.h"

class bvh_node : public hittable {
public:
        bvh_node(std::vector<std::shared_ptr<hittable>> &objects, size_t start, size_t end, double t0, double t1);
    bool hit(ray &r, double t_min, double t_max, hit_record &rec) override;
    bool bounding_box(double t0, double t1, aabb &output_box) override;

    std::shared_ptr<bvh_node> left;
    std::shared_ptr<bvh_node> right;
    aabb box;
};


#endif //RAYTRACER_BVH_NODE_H
