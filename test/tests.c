#include <ctest.h>
#include <libgeometry/geometry.h>
#include <stdlib.h>

CTEST(CircleCal, perimeter)
{
    double radius = 5;

    double real = calculate_perimeter_circle(radius);

    double exp = 31.41592;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(CircleCal, area)
{
    double radius = 5;

    double real = calculate_area_circle(radius);

    double exp = 78.53981;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(TriangleCal, perimeter)
{
    double x1 = 0, x2 = 5, x3 = 0, y1 = 0, y2 = 0, y3 = 5;

    double real = calculate_perimeter_triangle(x1, y1, x2, y2, x3, y3);

    double exp = 17.071068;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(TriangleCal, area)
{
    double x1 = 5, x2 = -6, x3 = -1, y1 = 3, y2 = -9, y3 = 4;

    double real = calculate_area_triangle(x1, y1, x2, y2, x3, y3);

    double exp = 41.5;

    ASSERT_DBL_NEAR(exp, real);
}

CTEST(InputPrep, lowercase)
{
    char str[256] = "TRIANGLE";
    int circumflex_counter = 0;
    char* curs = str;
    char* end = str;

    bool real = prepare_input(str, &circumflex_counter, &curs, &end);

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(InputPrep, completion_of_input)
{
    char str[256] = {'\0'};
    int circumflex_counter = 0;
    char* curs = str;
    char* end = str;

    bool real = prepare_input(str, &circumflex_counter, &curs, &end);

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectCirc, one_in_the_other)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 1;
    unsigned int triangle_record_counter = 0;
    var_circle.x[0] = 0;
    var_circle.y[0] = 0;
    var_circle.radius[0] = 1;
    var_circle.x[1] = 0;
    var_circle.y[1] = 0;
    var_circle.radius[1] = 5;
    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "circle");

    bool exp = true;

    ASSERT_EQUAL(real, exp);
}

CTEST(IntersectCirc, one_crosses_the_other)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 1;
    unsigned int triangle_record_counter = 0;
    var_circle.x[0] = 0;
    var_circle.y[0] = 0;
    var_circle.radius[0] = 1;
    var_circle.x[1] = 1;
    var_circle.y[1] = 0;
    var_circle.radius[1] = 1;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "circle");

    bool exp = true;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectCirc, one_doesnot_crosses_the_other)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 1;
    unsigned int triangle_record_counter = 0;
    var_circle.x[0] = 0;
    var_circle.y[0] = 0;
    var_circle.radius[0] = 1;
    var_circle.x[1] = 100;
    var_circle.y[1] = 0;
    var_circle.radius[1] = 1;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "circle");

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrian, one_side_coincides_with_the_other)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 1;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_triangle.x1[1] = 0;
    var_triangle.x2[1] = 10;
    var_triangle.x3[1] = 0;
    var_triangle.y1[1] = 0;
    var_triangle.y2[1] = 0;
    var_triangle.y3[1] = -10;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = true;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrian, common_vertex)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 1;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_triangle.x1[1] = 0;
    var_triangle.x2[1] = -10;
    var_triangle.x3[1] = 0;
    var_triangle.y1[1] = 0;
    var_triangle.y2[1] = 0;
    var_triangle.y3[1] = -10;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = true;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrian, intersection_at_multiple_points)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 1;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_triangle.x1[1] = 1;
    var_triangle.x2[1] = 13;
    var_triangle.x3[1] = 2;
    var_triangle.y1[1] = 1;
    var_triangle.y2[1] = 2;
    var_triangle.y3[1] = 13;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = true;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrian, triangles_do_not_intersect)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 1;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_triangle.x1[1] = 100;
    var_triangle.x2[1] = 130;
    var_triangle.x3[1] = 200;
    var_triangle.y1[1] = 100;
    var_triangle.y2[1] = 200;
    var_triangle.y3[1] = 130;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrianAndCircle, triangle_within_triangle)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 1;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_triangle.x1[1] = 1;
    var_triangle.x2[1] = 6;
    var_triangle.x3[1] = 1;
    var_triangle.y1[1] = 1;
    var_triangle.y2[1] = 1;
    var_triangle.y3[1] = 6;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrianAndCircle, circle_in_triangle)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 1;
    unsigned int triangle_record_counter = 0;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 100;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 100;
    var_circle.x[0] = 3;
    var_circle.y[0] = 3;
    var_circle.radius[0] = 1;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrianAndCircle, triangle_in_circle)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 0;
    unsigned int triangle_record_counter = 1;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_circle.x[0] = 0;
    var_circle.y[0] = 0;
    var_circle.radius[0] = 100;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "circle");

    bool exp = false;

    ASSERT_EQUAL(exp, real);
}

CTEST(IntersectTrianAndCircle, intersection_at_multiple_points)
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    unsigned int circle_record_counter = 1;
    unsigned int triangle_record_counter = 0;
    var_triangle.x1[0] = 0;
    var_triangle.x2[0] = 10;
    var_triangle.x3[0] = 0;
    var_triangle.y1[0] = 0;
    var_triangle.y2[0] = 0;
    var_triangle.y3[0] = 10;
    var_circle.x[0] = 1;
    var_circle.y[0] = 1;
    var_circle.radius[0] = 2;

    bool real = is_intersection(
            circle_record_counter,
            triangle_record_counter,
            var_circle,
            var_triangle,
            "triangle");

    bool exp = true;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, aright)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 2 , 0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = 0;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, character_before_parenthesis)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   с( -1 2 , 0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -1;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, not_a_number_after_the_parenthesis)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   (с -1 2 , 0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -2;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, not_a_number_after_the_first_number)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 с2 , 0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -3;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, not_a_comma_after_the_second_number)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 2 c, 0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -4;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, not_a_number_after_the_comma)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 2 , c0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -5;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, negative_radius)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 2 , -0.4)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -6;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, not_a_parenthesis_after_the_radius)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 2 , 0.4c)"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -7;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseCircle, input_after_parenthesis)
{
    struct Circle var_circle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"circle   ( -1 2 , 0.4)  c"};
    char* curs = str;
    char* end = str + 6;
    unsigned int circle_record_counter = 0;

    int real = parse_circle(
            &circumflex_counter,
            &curs,
            &end,
            &circle_record_counter,
            &var_circle);

    int exp = -8;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, alright)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( 1 1, 1 6, 6 1, 1 1)  )"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = 0;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, character_before_parenthesis)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle c( ( 1 1, 1 6, 6 1, 1 1)  )"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -1;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, character_before_Xnumber)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( c1 1, 1 6, 6 1, 1 1)  )"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -2;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, character_before_Ynumber)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( 1 c1, 1 6, 6 1, 1 1)  )"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -3;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, character_before_comma)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( 1 1c, 1 6, 6 1, 1 1)  )"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -4;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, character_before_parenth)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( 1 1, 1 6, 6 1, 1 1 с)  )"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -5;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, input_after_parenthesis)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( 1 1, 1 6, 6 1, 1 1)  )  с"};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -6;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseTriangle, mismatch_of_beginning_and_end)
{
    struct Triangle var_triangle;
    int circumflex_counter = 0;
    char str[SIZE_OF_ARR] = {"triangle ( ( 1 1, 1 6, 6 1, 9 12)  )  "};
    char* curs = str;
    char* end = str + 8;
    unsigned int triangle_record_counter = 0;

    int real = parse_triangle(
            &circumflex_counter,
            &curs,
            &end,
            &triangle_record_counter,
            &var_triangle);

    int exp = -7;

    ASSERT_EQUAL(exp, real);
}