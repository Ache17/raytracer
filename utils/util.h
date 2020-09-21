
#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H

#include <limits>

class vec3;
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double d2r(double degrees)
{
    return degrees * pi / 180.;
}

inline double r2d(double rad)
{
    return rad * 180. / pi;
}

double randomUnit();
double random(double min, double max);
int randomint(int min, int max);
double clamp(double x, double minima, double maxima);
void get_sphere_uv(vec3 const &p, double &u, double &v);

#endif //RAYTRACER_UTIL_H
