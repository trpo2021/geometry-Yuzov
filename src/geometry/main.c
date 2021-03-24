#include <ctype.h>
#include <libgeometry/geometry.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct Circle var_circle;
    struct Triangle var_triangle;
    char str[SIZE_OF_ARR];
    int circumflex_counter;
    char* curs;
    char* end;
    unsigned int record_counter = 0;
    printf("Enter a circle or triangle in WKT format\n");
    printf("After entering the figures, enter any non-alphabetic character or "
           "press Enter again to complete the entry\n");
    while (fgets(str, SIZE_OF_ARR, stdin)) {
        curs = str;
        end = str;
        circumflex_counter = 0;
        prepare_input(str, &circumflex_counter, &curs, &end);
        if (strncmp(curs, "circle", end - curs) == 0) {
            if (parse_circle(
                        &circumflex_counter,
                        &curs,
                        &end,
                        &record_counter,
                        &var_circle)
                == true) {
                printf("perimeter = %lf\n",
                       calculate_perimeter_circle(
                               var_circle.radius[record_counter]));
                printf("area = %lf\n",
                       calculate_area_circle(
                               var_circle.radius[record_counter]));
                record_counter++;
            }
        } else {
            if (strncmp(curs, "triangle", end - curs) == 0) {
                if (parse_triangle(
                            &circumflex_counter,
                            &curs,
                            &end,
                            &record_counter,
                            &var_triangle)
                    == true) {
                    printf("perimeter = %lf\n",
                           calculate_perimeter_triangle(
                                   var_triangle.x1[record_counter],
                                   var_triangle.y1[record_counter],
                                   var_triangle.x2[record_counter],
                                   var_triangle.y2[record_counter],
                                   var_triangle.x3[record_counter],
                                   var_triangle.y3[record_counter]));
                    printf("area = %lf\n",
                           calculate_area_triangle(
                                   var_triangle.x1[record_counter],
                                   var_triangle.y1[record_counter],
                                   var_triangle.x2[record_counter],
                                   var_triangle.y2[record_counter],
                                   var_triangle.x3[record_counter],
                                   var_triangle.y3[record_counter]));
                    record_counter++;
                }
            } else {
                for (int exit_anticipatorily = 0;
                     exit_anticipatorily < circumflex_counter;
                     exit_anticipatorily++) {
                    printf(" ");
                }
                printf("^\n");
                printf("Error at column %d: expected 'circle' or 'triangle'\n",
                       circumflex_counter);
            }
        }
    }
}
