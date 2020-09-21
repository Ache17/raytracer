
#ifndef RAYTRACER_SAMPLER_H
#define RAYTRACER_SAMPLER_H


#include "vec3.h"

class sampler {
public:
    static vec3 sampleUnitSphere();
    static vec3 sampleUnitCube();
    static vec3 sampleUnitSphereCosDistr();
    static vec3 sampleUnitDisk();
};


#endif //RAYTRACER_SAMPLER_H
