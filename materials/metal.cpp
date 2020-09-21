
#include "metal.h"
#include "../objects/hittable.h"
#include "../utils/sampler.h"

bool metal::scatter(ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in._direction), rec.normal);
    scattered = ray(rec.p, reflected + this->_fuzziness * sampler::sampleUnitSphere(), r_in._time);
    attenuation = color;
    return (dot(scattered._direction, rec.normal) > 0);
}
