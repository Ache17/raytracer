
#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "../utils/vec3.h"

class ray{
public:

    ray() {}
    ray(vec3 origin, vec3 direction, double time=0.0)
    {
        this->_origin = origin;
        this->_direction = direction;
        this->_time = time;
    }

    vec3 at(double t)
    {
        return this->_origin + t * this->_direction;
    }

    vec3 _origin, _direction;
    double _time;
};


#endif //RAYTRACER_RAY_H
