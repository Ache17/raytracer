
#include "renderer.h"
#include "fileSaver.h"
#include "ray.h"
#include "../utils/vec3.h"
#include <vector>
#include "../objects/hittable.h"
#include "../objects/hittable_list.h"
#include "../objects/sphere.h"
#include "../utils/util.h"
#include "camera.h"
#include "../utils/sampler.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "../objects/moving_sphere.h"
#include "../textures/checker_texture.h"
#include "../textures/noise_texture.h"
#include "../textures/image_texture.h"

using namespace std;

const int max_recursion_depth = 10;
double eps = 0.001;

hittable_list scene2()
{
    hittable_list world;

    //auto checker = make_shared<checker_texture>(vec3(1,1,1), vec3(0,0,0));
//    auto noisy = make_shared<noise_texture>(4);

    auto tex1 = make_shared<solid_color>(vec3{1, 0, 0});
    auto tex2 = make_shared<solid_color>(vec3{0,1,0});
    
    world.add(make_shared<sphere>(vec3(0,1,0), 1, make_shared<lambertian>(tex1)));
    world.add(make_shared<sphere>(vec3(2,1,0), 1, make_shared<dielectric>(-0.4)));
    world.add(make_shared<sphere>(vec3(-2,1,0), 1, make_shared<dielectric>(-0.4)));
    world.add(make_shared<sphere>(vec3{0,-100, 0}, 100, make_shared<lambertian>(tex2)));
    return world;
}
vec3 raytrace( ray& r, hittable &world, int recursion_depth = 0)
{
    if (recursion_depth == max_recursion_depth)
        return vec3(0,0,0);
    hit_record rec;
    if (world.hit(r, eps, infinity,rec)) {
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * raytrace(scattered, world, recursion_depth + 1);
        }
        return vec3(0,0,0);
    }
    vec3 unit_dir = unit_vector(r._direction);
    auto t = 0.5 * (unit_dir.y() + 1.0);
    return (1. - t) * vec3(1., 1., 1.) + t * vec3(0.5, 0.7, 1.);
}


void renderer::render_test(int width, double aspect_ratio, int samples)
{
    // set width x height with given aspect ratio
    int height = double(width) / aspect_ratio;
    this->samples_per_pixel = samples;

    hittable_list world;

    auto R = cos(pi / 4);

    world = scene2();

    // Camera
    double fov = 60;
    vec3 observator(0, 1, 8);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1 ,0 );
    auto dist_to_focus = 10;
    auto aperture = .01;

    camera cam(observator, lookat, vup, fov, 16. / 9., aperture, dist_to_focus);

    // matrix of intensities
    vector<vector<vec3>> intensity(height, vector<vec3>(width));

    for (int y = height - 1; y >= 0; -- y)
    {
        for (int x = 0; x < width; ++ x) {

            vec3 color(0,0,0);
            for (int s = 0; s < this->samples_per_pixel; ++s)
            {
                double coef1 = double(x + randomUnit()) / double(width - 1);
                double coef2 = double(y + randomUnit()) / double(height - 1);
                ray r = cam.get_ray(coef1, coef2);
                color += raytrace(r, world);
            }
            correction(color);
            intensity[y][x] = color;
        }
    }


    // cast to raw buffer to save as jpeg
    uint8_t* rawBuff = rawRGB_from_vectors(intensity);
    fileSaver::write_JPEG((char *)"diffuset.jpg", rawBuff, width, height);

    delete rawBuff;
}

uint8_t *renderer::rawRGB_from_vectors(vector<vector<vec3>> &buff)
{

    int width = buff[0].size();
    int height = buff.size();
    auto* rawBuff = new uint8_t [ 3 *  width * height];

    int total = 3 * width * height - 3;

    //  conversion from double 0.0-1.0 which describes intensity to 8 bit value representing color ]
    for (int y = buff.size()-1; y >= 0; --y )
    {
        for (int x = 0; x < buff[y].size(); ++x)
        {
            int pos = 3 * (y * width + x);
            rawBuff[total - pos] = buff[y][x].x() * 255.99999;
            rawBuff[total - pos + 1] = buff[y][x].y() * 255.99999;
            rawBuff[total - pos + 2] = buff[y][x].z() * 255.99999;
        }
    }

    return rawBuff;
}

void renderer::correction(vec3 &v) const {
    // gamma correction
    v *= (1. / double(samples_per_pixel));
    v.sqrtEl();
}

