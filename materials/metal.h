
#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "material.h"

class metal : public material {
public:
    metal(vec3 a, double fuzziness=0) : color(a), _fuzziness(fuzziness){}
    bool scatter(ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const override;


    double _fuzziness = 0;
    vec3 color;
};


#endif //RAYTRACER_METAL_H
