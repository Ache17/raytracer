#include "../objects/hittable.h"

#include "dielectric.h"
#include "../utils/util.h"

bool dielectric::scatter(ray &r_in, hit_record &rec, vec3 &attenuation, ray &scattered) const {
    attenuation = vec3(1. ,1. , 1.);
    double etai_over_etat = rec.front_face ? (1. / ref_idx) : ref_idx;
    vec3 unit_direction = unit_vector(r_in._direction);

    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.);
    double sin_theta = sqrt(1. - cos_theta * cos_theta);
    double reflect_prob = schlick_approximation(cos_theta, etai_over_etat);
    if (etai_over_etat * sin_theta > 1.0 || randomUnit() < reflect_prob)
    {
        vec3 reflected = reflect(unit_direction, rec.normal);
        scattered = ray(rec.p, reflected);
        return true;
    }

    vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
    scattered = ray(rec.p, refracted, r_in._time);
    return true;
}
