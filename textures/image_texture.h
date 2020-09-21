
#ifndef RAYTRACER_IMAGE_TEXTURE_H
#define RAYTRACER_IMAGE_TEXTURE_H
#include "texture.h"
#include "../core/fileSaver.h"
#include <jpeglib.h>

class image_texture : public texture {
public:
    const static int bytes_per_pixel = 3;

    image_texture(char *filename)
    {
        this->data = fileSaver::read_JPEG(filename, this->width, this->height);
    }
    ~image_texture()
    {
        delete[] data;
    }
    vec3 value(double u, double v, vec3 &p) override
    {
        if (data == nullptr)
            return vec3(0, 1, 0);

        // Clamp input texture coordinates to [0,1] x [1, 0]
        u = clamp(u, 0, 1);
        v = 1 - clamp(v, 0, 1);
        int i = u * width;
        int j = v * height;

        const auto color_scale = 1.0 / 255.0;
        auto pixel = data + j * this->width * this->bytes_per_pixel + i * this->bytes_per_pixel;

        return vec3(pixel[0], pixel[1], pixel[2]) * color_scale;
    }

private:
    JSAMPLE *data= nullptr;
    int width=0, height=0;
};


#endif //RAYTRACER_IMAGE_TEXTURE_H
