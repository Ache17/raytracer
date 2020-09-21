#include <iostream>
#include "core/renderer.h"
#include "core/ray.h"
#include "utils/util.h"
#include "time.h"
#include <chrono>
#include <fstream>
#include "core/fileSaver.h"

using namespace std::chrono;

/* Bibliography
 * [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
 * [Ray Tracing From the Ground Up by Kevin Suffern]
 * [Ray Tracing: The Next Week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
 * [Ray Tracing: The Rest of Your Life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)
 */

int main()
{
    renderer r;
    auto start = high_resolution_clock::now();
    r.render_test(1600  , 16. / 9., 100);
    auto stop = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(stop - start).count() / 1000.;
    return 0;
}
