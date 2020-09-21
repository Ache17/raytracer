#include "util.h"
#include <random>
#include <cmath>
#include "vec3.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

double randomUnit()
{
    return dis(gen);
}

double random(double min, double max) {
    return min + (max - min) * randomUnit();
}

double clamp(double x, double minima, double maxima) {
    return std::min(maxima, std::max(x, minima));
}

int randomint(int min, int max)
{
    return min + double (max - min + 0.999999) * randomUnit();
}

void get_sphere_uv(vec3 const &p, double &u, double &v)
{
    auto phi   = atan2(p.z(), p.x());
    auto theta = asin(p.y());
    u = 1 - (phi + pi) / (2 * pi);
    v = (theta + 0.5 * pi) / pi;
}
