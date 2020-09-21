cmake_minimum_required(VERSION 3.16)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(raytracer main.cpp core/ray.cpp core/ray.h core/renderer.cpp core/renderer.h core/fileSaver.cpp core/fileSaver.h utils/vec3.h objects/hittable.h objects/sphere.cpp objects/sphere.h objects/hittable_list.cpp objects/hittable_list.h utils/util.h utils/util.cpp core/camera.cpp core/camera.h utils/sampler.cpp utils/sampler.h materials/material.h materials/lambertian.cpp materials/lambertian.h materials/metal.cpp materials/metal.h materials/dielectric.cpp materials/dielectric.h objects/moving_sphere.cpp objects/moving_sphere.h core/aabb.cpp core/aabb.h objects/bvh_node.cpp objects/bvh_node.h textures/texture.cpp textures/texture.h textures/checker_texture.cpp textures/checker_texture.h utils/perlin.cpp utils/perlin.h textures/noise_texture.cpp textures/noise_texture.h textures/image_texture.cpp textures/image_texture.h)
target_link_libraries(raytracer jpeg Eigen3::Eigen)