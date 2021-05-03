#pragma once
#define _USE_MATH_DEFINES
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ARR 256

struct Circle {
    double x[SIZE_OF_ARR];
    double y[SIZE_OF_ARR];
    double radius[SIZE_OF_ARR];
};

struct Triangle {
    double x1[SIZE_OF_ARR];
    double x2[SIZE_OF_ARR];
    double x3[SIZE_OF_ARR];
    double y1[SIZE_OF_ARR];
    double y2[SIZE_OF_ARR];
    double y3[SIZE_OF_ARR];
};

bool prepare_input(
        char* array, int* circumflex_counter, char** first, char** second);
int parse_circle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter,
        struct Circle* var_circle);
int parse_triangle(
        int* circumflex_counter,
        char** curs,
        char** end,
        unsigned int* record_counter,
        struct Triangle* var_triangle);
double calculate_area_circle(double radius);
double calculate_perimeter_circle(double radius);
double calculate_perimeter_triangle(
        double x1, double y1, double x2, double y2, double x3, double y3);
double calculate_area_triangle(
        double x1, double y1, double x2, double y2, double x3, double y3);
bool is_intersection(
        unsigned int circle_record_counter,
        unsigned int triangle_record_counter,
        struct Circle var_circle,
        struct Triangle var_triangle,
        char* figure_name,
        int* ind_cir,
        int* ind_tri,
        int* j,
        int* g);
void print_errormsg(int* circumflex_counter);