#include <ctest.h>
#include <libgeometry/geometry.h>
#include <stdlib.h>

CTEST(cals_circle, Perimeter)
{
    double radius = 3;

    double real = calculate_perimeter_circle(radius);

    double exp = 18.84956;

    ASSERT_DBL_NEAR(exp, real);
}