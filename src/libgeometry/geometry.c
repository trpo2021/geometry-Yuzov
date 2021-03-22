#include <ctype.h>
#include <libgeometry/geometry.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool skip_space(int* circumflex_counter, char** first, char** second)
{
    while (isspace(**first)) {
        *first = *first + 1;
        *second = *second + 1;
        *circumflex_counter = *circumflex_counter + 1;
    }
    return true;
}

bool is_sign(char token, int* circumflex_counter, char** first, char** second)
{
    if (**first != token) {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '%c'\n",
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

bool add_word_length(int* circumflex_counter, char** first, char** second)
{
    *circumflex_counter = *circumflex_counter + (*second - *first);
    *first = *second;
    return true;
}

bool is_number(int* circumflex_counter, char** first)
{
    if (isdigit(**first) == 0) {
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
    return true;
}

bool is_EOF(int* circumflex_counter, char** first)
{
    if (**first != '\0') {
        for (int exit_anticipatorily = 0;
             exit_anticipatorily < *circumflex_counter;
             exit_anticipatorily++) {
            printf(" ");
        }
        printf("^\n");
        printf("unexpected token\n");
        return false;
    }
    return true;
}

bool is_letter(char** second)
{
    if ((**second >= '\x61') && (**second <= '\x7a')) {
        while (**second != ' ') {
            *second = *second + 1;
        }
    } else {
        printf("Input completed");
        exit(0);
    }
    return true;
}

bool to_lower_all_str(char* array)
{
    for (int i = 0; i < SIZE_OF_ARR; i++) {
        array[i] = tolower(array[i]);
    }
    return true;
}

bool parse_value(
        double* var, int* circumflex_counter, char*** curs, char*** end)
{
    bool error = is_number(circumflex_counter, *curs);
    if (!error)
        return false;
    *var = strtod(**curs, *end);
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

bool parse_circle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter)
{
    struct Circle var_circle;
    bool error = true;
    for (;;) {
        double x, y, radius;
        add_word_length(circumflex_counter, curs, end);
        skip_space(circumflex_counter, curs, end);
        error = is_sign('(', circumflex_counter, curs, end);
        if (!error)
            break;
        skip_space(circumflex_counter, curs, end);
        error = parse_value(&x, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = parse_value(&y, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = is_sign(',', circumflex_counter, curs, end);
        if (!error)
            break;
        skip_space(circumflex_counter, curs, end);
        error = parse_value(&radius, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = is_sign(')', circumflex_counter, curs, end);
        if (!error)
            break;
        skip_space(circumflex_counter, curs, end);
        error = is_EOF(circumflex_counter, curs);
        if (error == true) {
            var_circle.x[*record_counter] = x;
            var_circle.y[*record_counter] = y;
            var_circle.radius[*record_counter] = radius;
            printf("The circle has been added successfully!\n");
            printf("Your figure - circle(%.1f %.1f, %.1f)\n",
                   var_circle.x[*record_counter],
                   var_circle.y[*record_counter],
                   var_circle.radius[*record_counter]);
            *record_counter = *record_counter + 1;
            printf("perimeter = %lf\n", calculate_perimeter_circle(radius));
            printf("area = %lf\n", calculate_area_circle(radius));
            break;
        } else {
            printf("The circle has NOT been added !\n");
            break;
        }
    }
    return true;
}

double calculate_side(double x1, double y1, double x2, double y2)
{
    return sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
}

double calculate_perimeter_triangle(
        struct Triangle var_triangle, int unsigned record_counter)
{
    double first_side = calculate_side(
            var_triangle.x1[record_counter],
            var_triangle.y1[record_counter],
            var_triangle.x2[record_counter],
            var_triangle.y2[record_counter]);
    double second_side = calculate_side(
            var_triangle.x2[record_counter],
            var_triangle.y2[record_counter],
            var_triangle.x3[record_counter],
            var_triangle.y3[record_counter]);
    double third_side = calculate_side(
            var_triangle.x3[record_counter],
            var_triangle.y3[record_counter],
            var_triangle.x1[record_counter],
            var_triangle.y1[record_counter]);
    return first_side + second_side + third_side;
}

double calculate_area_triangle(
        struct Triangle var_triangle, int unsigned record_counter)
{
    double x1 = var_triangle.x1[record_counter];
    double x2 = var_triangle.x2[record_counter];
    double x3 = var_triangle.x3[record_counter];
    double y1 = var_triangle.y1[record_counter];
    double y2 = var_triangle.y2[record_counter];
    double y3 = var_triangle.y3[record_counter];
    double result = fabs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2);
    return result;
}

bool parse_triangle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter)
{
    struct Triangle var_triangle;
    bool error = true;
    for (;;) {
        double x1, x2, x3, x4, y1, y2, y3, y4;
        bool exit_anticipatorily = false;
        add_word_length(circumflex_counter, curs, end);
        skip_space(circumflex_counter, curs, end);
        for (int i = 0; i < 2; i++) {
            error = is_sign('(', circumflex_counter, curs, end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            skip_space(circumflex_counter, curs, end);
        }
        if (exit_anticipatorily == true)
            break;
        for (int i = 0; i < 3; i++) {
            double varx, vary;
            error = parse_value(&varx, circumflex_counter, &curs, &end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            error = parse_value(&vary, circumflex_counter, &curs, &end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            error = is_sign(',', circumflex_counter, curs, end);
            if (!error) {
                exit_anticipatorily = true;
                break;
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
        if (exit_anticipatorily == true)
            break;
        error = parse_value(&x4, circumflex_counter, &curs, &end);
        if (!error)
            break;
        error = parse_value(&y4, circumflex_counter, &curs, &end);
        if (!error)
            break;
        for (int i = 0; i < 2; i++) {
            error = is_sign(')', circumflex_counter, curs, end);
            if (!error) {
                exit_anticipatorily = true;
                break;
            }
            skip_space(circumflex_counter, curs, end);
        }
        if (exit_anticipatorily == true)
            break;
        error = is_EOF(circumflex_counter, curs);
        if ((error == true) && (x1 == x4) && (y1 == y4)) {
            var_triangle.x1[*record_counter] = x1;
            var_triangle.x2[*record_counter] = x2;
            var_triangle.x3[*record_counter] = x3;
            var_triangle.x4[*record_counter] = x4;
            var_triangle.y1[*record_counter] = y1;
            var_triangle.y2[*record_counter] = y2;
            var_triangle.y3[*record_counter] = y3;
            var_triangle.y4[*record_counter] = y4;
            printf("The triangle has been added successfully!\n");
            printf("Your figure - triangle((%.1f %.1f, %.1f %.1f, %.1f %.1f, "
                   "%.1f %.1f))\n",
                   var_triangle.x1[*record_counter],
                   var_triangle.y1[*record_counter],
                   var_triangle.x2[*record_counter],
                   var_triangle.y2[*record_counter],
                   var_triangle.x3[*record_counter],
                   var_triangle.y3[*record_counter],
                   var_triangle.x4[*record_counter],
                   var_triangle.y4[*record_counter]);
            printf("perimeter = %lf\n",
                   calculate_perimeter_triangle(var_triangle, *record_counter));
            printf("area = %lf\n",
                   calculate_area_triangle(var_triangle, *record_counter));
            *record_counter = *record_counter + 1;
            break;
        } else {
            printf("The triangle has NOT been added !\n");
            break;
        }
    }
    return true;
}