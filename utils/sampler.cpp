
#include "sampler.h"
#include "util.h"

vec3 sampler::sampleUnitSphere() {

    double theta = random(0, pi);
    double phi   = random(0, 2 * pi);
    return vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

vec3 sampler::sampleUnitCube() {
    return vec3(randomUnit(), randomUnit(), randomUnit());
}

// more uniform scattering, greater variance of directions ( more vectors are
//                                                          scattered not to normal direction )
vec3 sampler::sampleUnitSphereCosDistr() {
    auto phi = random(0, 2 * pi);
    auto z = random(-1, 1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(phi), r * sin(phi), z);
}

vec3 sampler::sampleUnitDisk() {
    double theta = random(0, 2 * pi);
    return vec3(cos(theta), sin(theta), 0);
}
