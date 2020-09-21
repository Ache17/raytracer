
#include "lambertian.h"
#include "../objects/hittable_list.h"
#include "../utils/sampler.h"

bool lambertian::scatter(ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 scatter_direction = rec.normal + sampler::sampleUnitSphereCosDistr();
    scattered = ray(rec.p, scatter_direction, r_in._time);
    attenuation = this->_texture->value(rec.u, rec.v, rec.p);
    return true ;
}

lambertian::lambertian(const vec3 &color) {
    this->_texture = std::make_shared<solid_color>(color);
}
