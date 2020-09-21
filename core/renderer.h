
#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H


#include <cstdint>
#include <vector>
#include "../utils/vec3.h"

class renderer {

public:
    void render_test(int width, double aspect_ratio, int samples);
    void correction(vec3 &v) const;
    static uint8_t* rawRGB_from_vectors(std::vector<std::vector<vec3>> &buff);

protected:
    int samples_per_pixel;
};


#endif //RAYTRACER_RENDERER_H
