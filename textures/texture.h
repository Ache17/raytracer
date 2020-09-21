
#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H
#include "../utils/util.h"
#include "../utils/vec3.h"

class texture {
public:
    virtual vec3 value(double u, double v, vec3 &p) = 0;
};

class solid_color : public texture
{
public:
    solid_color()   {}
    solid_color(vec3 c) : color_val(c) {}
    solid_color(double red, double green, double blue)  { color_val = vec3(red, green, blue); }
    vec3 value(double u, double v, vec3 &p) override
    {
        return this->color_val;
    }
    vec3 color_val;
};

#endif //RAYTRACER_TEXTURE_H
