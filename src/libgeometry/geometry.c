#include <ctype.h>
#include <libgeometry/geometry.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool skip_space(int* circumflex_counter, char** first, char** second)
{
    while (isspace(**first)) {
        *first = *first + 1;
        *second = *second + 1;
        *circumflex_counter = *circumflex_counter + 1;
    }
    return true;
}

static bool
is_sign(char token, int* circumflex_counter, char** first, char** second)
{
    if (**first != token) {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '%c'\n\n",
               *circumflex_counter,
               token);
        return false;
    } else {
        *first = *first + 1;
        *second = *second + 1;
        *circumflex_counter = *circumflex_counter + 1;
    }
    return true;
}

static bool
add_word_length(int* circumflex_counter, char** first, char** second)
{
    *circumflex_counter = *circumflex_counter + (*second - *first);
    *first = *second;
    return true;
}

static bool is_EOF(int* circumflex_counter, char** first)
{
    if (**first != '\0') {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("unexpected token\n\n");
        return false;
    }
    return true;
}

static bool is_letter(char** second)
{
    if ((**second >= '\x61') && (**second <= '\x7a')) {
        while (isalpha(**second) != 0) {
            *second = *second + 1;
        }
    } else {
        printf("Input completed\n");
        return false;
    }
    return true;
}

static bool to_lower_all_str(char* array)
{
    for (int i = 0; i < SIZE_OF_ARR; i++) {
        array[i] = tolower(array[i]);
    }
    return true;
}

bool prepare_input(
        char* array, int* circumflex_counter, char** first, char** second)
{
    bool res1, res2, res3;
    res1 = to_lower_all_str(array);
    res2 = skip_space(circumflex_counter, first, second);
    res3 = is_letter(second);
    if ((res1 && res2 && res3) == true)
        return true;
    else
        return false;
}

static bool
parse_value(double* var, int* circumflex_counter, char*** curs, char*** end)
{
    *var = strtod(**curs, *end);
    if ((*var == 0) && (**curs == **end)) {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '<double>'\n",
               *circumflex_counter);
        return false;
    }
    add_word_length(circumflex_counter, *curs, *end);
    skip_space(circumflex_counter, *curs, *end);
    return true;
}

double calculate_perimeter_circle(double radius)
{
    return 2 * M_PI * radius;
}

double calculate_area_circle(double radius)
{
    return M_PI * pow(radius, 2);
}

static bool check_radius(double* radius)
{
    if (*radius < 0) {
        printf("Radius can not be negative\n\n");
        return false;
    } else {
        return true;
    }
}

int parse_circle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter,
        struct Circle* var_circle)
{
    bool error = true;
    for (;;) {
        double x, y, radius;
        add_word_length(circumflex_counter, curs, end);
        skip_space(circumflex_counter, curs, end);
        error = is_sign('(', circumflex_counter, curs, end);
        if (!error)
            return -1;
        skip_space(circumflex_counter, curs, end);
        error = parse_value(&x, circumflex_counter, &curs, &end);
        if (!error)
            return -2;
        error = parse_value(&y, circumflex_counter, &curs, &end);
        if (!error)
            return -3;
        error = is_sign(',', circumflex_counter, curs, end);
        if (!error)
            return -4;
        skip_space(circumflex_counter, curs, end);
        error = parse_value(&radius, circumflex_counter, &curs, &end);
        if (!error)
            return -5;
        error = check_radius(&radius);
        if (!error)
            return -6;
        error = is_sign(')', circumflex_counter, curs, end);
        if (!error)
            return -7;
        skip_space(circumflex_counter, curs, end);
        error = is_EOF(circumflex_counter, curs);
        if (error == true) {
            var_circle->x[*record_counter] = x;
            var_circle->y[*record_counter] = y;
            var_circle->radius[*record_counter] = radius;
            printf("The circle has been added successfully!\n");
            printf("Your figure - circle(%.1lf %.1lf, %.1lf)\n",
                   var_circle->x[*record_counter],
                   var_circle->y[*record_counter],
                   var_circle->radius[*record_counter]);
            return 0;
        } else {
            printf("The circle has NOT been added !\n\n");
            return -8;
        }
    }
}

static double calculate_side(double x1, double y1, double x2, double y2)
{
    return sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
}

double calculate_perimeter_triangle(
        double x1, double y1, double x2, double y2, double x3, double y3)
{
    double first_side = calculate_side(x1, y1, x2, y2);
    double second_side = calculate_side(x2, y2, x3, y3);
    double third_side = calculate_side(x3, y3, x1, y1);
    return first_side + second_side + third_side;
}

double calculate_area_triangle(
        double x1, double y1, double x2, double y2, double x3, double y3)
{
    double result = fabs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2);
    return result;
}

int parse_triangle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter,
        struct Triangle* var_triangle)
{
    bool error = true;
    for (;;) {
        double x1, x2, x3, x4, y1, y2, y3, y4;
        add_word_length(circumflex_counter, curs, end);
        skip_space(circumflex_counter, curs, end);
        for (int i = 0; i < 2; i++) {
            error = is_sign('(', circumflex_counter, curs, end);
            if (!error) {
                return -1;
            }
            skip_space(circumflex_counter, curs, end);
        }
        for (int i = 0; i < 3; i++) {
            double varx, vary;
            error = parse_value(&varx, circumflex_counter, &curs, &end);
            if (!error) {
                return -2;
            }
            error = parse_value(&vary, circumflex_counter, &curs, &end);
            if (!error) {
                return -3;
            }
            error = is_sign(',', circumflex_counter, curs, end);
            if (!error) {
                return -4;
            }
            if (i == 0) {
                x1 = varx;
                y1 = vary;
            }
            if (i == 1) {
                x2 = varx;
                y2 = vary;
            }
            if (i == 2) {
                x3 = varx;
                y3 = vary;
            }
            skip_space(circumflex_counter, curs, end);
        }
        error = parse_value(&x4, circumflex_counter, &curs, &end);
        if (!error)
            return -2;
        error = parse_value(&y4, circumflex_counter, &curs, &end);
        if (!error)
            return -3;
        for (int i = 0; i < 2; i++) {
            error = is_sign(')', circumflex_counter, curs, end);
            if (!error) {
                return -5;
            }
            skip_space(circumflex_counter, curs, end);
        }
        error = is_EOF(circumflex_counter, curs);
        if (!error) {
            return -6;
        }
        if ((error == true) && (x1 == x4) && (y1 == y4)) {
            var_triangle->x1[*record_counter] = x1;
            var_triangle->x2[*record_counter] = x2;
            var_triangle->x3[*record_counter] = x3;
            var_triangle->y1[*record_counter] = y1;
            var_triangle->y2[*record_counter] = y2;
            var_triangle->y3[*record_counter] = y3;
            printf("The triangle has been added successfully!\n");
            printf("Your figure - triangle((%.1f %.1f, %.1f %.1f, %.1f %.1f, "
                   "%.1f %.1f))\n",
                   var_triangle->x1[*record_counter],
                   var_triangle->y1[*record_counter],
                   var_triangle->x2[*record_counter],
                   var_triangle->y2[*record_counter],
                   var_triangle->x3[*record_counter],
                   var_triangle->y3[*record_counter],
                   var_triangle->x1[*record_counter],
                   var_triangle->y1[*record_counter]);
            return 0;
        } else {
            printf("The triangle has NOT been added !\n\n");
            return -7;
        }
    }
}

static double mult_vectors(double ax, double ay, double bx, double by)
{
    return (ax * by - bx * ay);
}

static void swap_sides(
        double* x1,
        double* y1,
        double* x2,
        double* y2,
        double* x3,
        double* y3,
        double* x4,
        double* y4,
        int point_counter,
        struct Triangle var_triangle,
        unsigned int triangle_record_counter,
        int i)
{
    double xi[] = {var_triangle.x1[i], var_triangle.x2[i], var_triangle.x3[i]};
    double yi[] = {var_triangle.y1[i], var_triangle.y2[i], var_triangle.y3[i]};
    double xtrc[]
            = {var_triangle.x1[triangle_record_counter],
               var_triangle.x2[triangle_record_counter],
               var_triangle.x3[triangle_record_counter]};
    double ytrc[]
            = {var_triangle.y1[triangle_record_counter],
               var_triangle.y2[triangle_record_counter],
               var_triangle.y3[triangle_record_counter]};
    int k = 0;
    int g = 1;
    int h = 0;
    int l = 1;
    for (int t = 0; t < point_counter; t++) {
        if ((t == 3) || (t == 6)) {
            if (g < 2)
                g++;
            else if (k < 1)
                k++;
        }
        *x1 = xtrc[k];
        *y1 = ytrc[k];
        *x2 = xtrc[g];
        *y2 = ytrc[g];
    }
    for (int p = 0; p < point_counter; p++) {
        if (((p == 3) || (p == 6))) {
            h = 0;
            l = 1;
        }
        *x3 = xi[h];
        *y3 = yi[h];
        *x4 = xi[l];
        *y4 = yi[l];
        if (l < 2)
            l++;
        else if (h < 1)
            h++;
    }
}

static void triangle_cross_circle(
        double* x_1,
        double* x_2,
        double radius,
        double x1,
        double x2,
        double x3,
        double y1,
        double y2,
        double y3)
{
    double a = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    double b = 2 * ((x2 - x1) * (x1 - x3) + (y2 - y1) * (y1 - y3));
    double c = pow(x3, 2) + pow(y3, 2) + x1 * x1 + y1 * y1
            - 2 * (x3 * x1 + y3 * y1) - pow(radius, 2);
    double discriminant = pow(b, 2) - (4 * a * c);
    *x_1 = (-b + sqrt(discriminant)) / (2 * a);
    *x_2 = (-b - sqrt(discriminant)) / (2 * a);
}

static bool is_lines_cross(
        double x1,
        double y1,
        double x2,
        double y2,
        double x3,
        double y3,
        double x4,
        double y4)
{
    double v1, v2, v3, v4;
    v1 = mult_vectors(x4 - x3, y4 - y3, x1 - x3, y1 - y3);
    v2 = mult_vectors(x4 - x3, y4 - y3, x2 - x3, y2 - y3);
    v3 = mult_vectors(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
    v4 = mult_vectors(x2 - x1, y2 - y1, x4 - x1, y4 - y1);
    if ((v1 * v2 <= 0) && (v3 * v4 <= 0)) {
        return true;
    }
    return false;
}

bool is_intersection(
        unsigned int circle_record_counter,
        unsigned int triangle_record_counter,
        struct Circle var_circle,
        struct Triangle var_triangle,
        char* figure_name)
{
    double x1, x2, y1, y2, x3, y3, x_1, x_2, radius;
    int i;
    bool intersects = false;
    int side_counter = 1;
    if (strcmp(figure_name, "circle") == 0) {
        if (circle_record_counter > 0) {
            for (i = circle_record_counter - 1; i != -1; i--) {
                if ((var_circle.radius[circle_record_counter]
                     + var_circle.radius[i])
                    >= calculate_side(
                            var_circle.x[circle_record_counter],
                            var_circle.y[circle_record_counter],
                            var_circle.x[i],
                            var_circle.y[i])) {
                    if (intersects == false) {
                        intersects = true;
                        printf("intersects:\n");
                    }
                    printf("    circle( %.1lf %.1lf , %.1lf )\n\n",
                           var_circle.x[i],
                           var_circle.y[i],
                           var_circle.radius[i]);
                }
            }
        }
        if (triangle_record_counter >= 1) {
            radius = var_circle.radius[circle_record_counter];
            side_counter = 1;
            for (i = triangle_record_counter - 1; i != -1; i--) {
                if (side_counter == 1) {
                    x2 = var_triangle.x2[i];
                    x1 = var_triangle.x1[i];
                    y2 = var_triangle.y2[i];
                    y1 = var_triangle.y1[i];
                }
                if (side_counter == 2) {
                    x2 = var_triangle.x2[i];
                    x1 = var_triangle.x3[i];
                    y2 = var_triangle.y2[i];
                    y1 = var_triangle.y3[i];
                }
                if (side_counter == 3) {
                    x2 = var_triangle.x3[i];
                    x1 = var_triangle.x1[i];
                    y2 = var_triangle.y3[i];
                    y1 = var_triangle.y1[i];
                }
                x3 = var_circle.x[circle_record_counter];
                y3 = var_circle.y[circle_record_counter];
                side_counter++;
                triangle_cross_circle(
                        &x_1, &x_2, radius, x1, x2, x3, y1, y2, y3);
                if ((x_1 < 0) || (x_2 < 0)) {
                    if (intersects == false) {
                        intersects = true;
                        printf("intersects:\n");
                    }
                    printf("triangle (( %.1lf %.1lf, %.1lf %.1lf, %.1lf %.1lf "
                           "))\n\n",
                           var_triangle.x1[i],
                           var_triangle.y1[i],
                           var_triangle.x2[i],
                           var_triangle.y2[i],
                           var_triangle.x3[i],
                           var_triangle.y3[i]);
                }
            }
        }
    }
    if (strcmp(figure_name, "triangle") == 0) {
        if (triangle_record_counter > 0) {
            intersects = false;
            bool cross;
            int point_counter = 1;
            side_counter = 1;
            double x4, y4;
            for (i = triangle_record_counter - 1; i != -1; i--) {
                for (point_counter = 1; point_counter <= 9; point_counter++) {
                    swap_sides(
                            &x1,
                            &y1,
                            &x2,
                            &y2,
                            &x3,
                            &y3,
                            &x4,
                            &y4,
                            point_counter,
                            var_triangle,
                            triangle_record_counter,
                            i);
                    cross = is_lines_cross(x1, y1, x2, y2, x3, y3, x4, y4);
                    if (cross == true) {
                        if (intersects == false) {
                            intersects = true;
                            printf("intersects:\n");
                        }
                        printf("triangle (( %.1lf %.1lf, %.1lf %.1lf, %.1lf "
                               "%.1lf ))\n\n",
                               var_triangle.x1[i],
                               var_triangle.y1[i],
                               var_triangle.x2[i],
                               var_triangle.y2[i],
                               var_triangle.x3[i],
                               var_triangle.y3[i]);
                        break;
                    }
                }
            }
        }
        if (circle_record_counter >= 1) {
            side_counter = 1;
            x2 = var_triangle.x2[triangle_record_counter];
            x1 = var_triangle.x1[triangle_record_counter];
            y2 = var_triangle.y2[triangle_record_counter];
            y1 = var_triangle.y1[triangle_record_counter];
            for (i = circle_record_counter - 1; i != -1; i--) {
                x3 = var_circle.x[i];
                y3 = var_circle.y[i];
                radius = var_circle.radius[i];
                side_counter++;
                triangle_cross_circle(
                        &x_1, &x_2, radius, x1, x2, x3, y1, y2, y3);
                if ((x_1 < 0) || (x_2 < 0)) {
                    if (intersects == false) {
                        intersects = true;
                        printf("intersects:\n");
                    }
                    printf("circle ( %.1lf %.1lf , %.1lf )\n",
                           var_circle.x[i],
                           var_circle.y[i],
                           var_circle.radius[i]);
                }
            }
        }
    }
    if (intersects == true)
        return true;
    else
        return false;
}