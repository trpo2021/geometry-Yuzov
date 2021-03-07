#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE_OF_ARR 256

bool skip_space(int *circ, char **first, char **second);          //ПРОПУСК ПРОБЕЛОВ
bool is_sign(char token, int *circ, char **first, char **second); //ОШИБКА ДЛЯ '(' , ')' и ','
bool add_word_length(int *circ, char **first, char **second);     //ПРИБАВЛЕНИЕ К КУРСОРУ ДЛИНЫ СИМВОЛОВ (+1)
bool is_number(int *circ, char **first, char **second);           //ОШИБКА ДЛЯ ЧИСЕЛ
bool is_EOF(int *circ, char **first);                             //ОШИБКА ДЛЯ КОНЦА СТРОКИ
bool is_letter(int *circ, char **first, char **second);           //ПРОВЕРКА НА CIRCLE
bool is_triangle(int *circ, char **first, char **second);         //ПРОВЕРКА НА TRIANGLE
bool to_lower_all_str(char *array);                               //ПЕРЕВОД СТРОКИ В НИЖНИЙ РЕГИСТР
bool parse_circle(int *circ, char **curs, char **end, unsigned int *record_counter);
bool parse_triangle(int *circ, char **curs, char **end, unsigned int *record_counter);

struct Circle
{
    double x[SIZE_OF_ARR]; //В МАССИВАХ ЭЛЕМЕНТЫ ПЕРВОЙ ФИГУРЫ ХРАНЯТСЯ ПО НУЛЕВОМУ ИНДЕКСУ , ВТОРОЙ ПО ПЕРВОМУ И Т.Д.
    double y[SIZE_OF_ARR];
    double radius[SIZE_OF_ARR];
};

struct Triangle
{
    double x1[SIZE_OF_ARR];
    double x2[SIZE_OF_ARR];
    double x3[SIZE_OF_ARR];
    double x4[SIZE_OF_ARR];
    double y1[SIZE_OF_ARR];
    double y2[SIZE_OF_ARR];
    double y3[SIZE_OF_ARR];
    double y4[SIZE_OF_ARR];
};

int main()
{
    char str[SIZE_OF_ARR];
    int circ; // Счетчик циркумфлекса
    char *curs;
    char *end;
    unsigned int record_counter = 0;
    printf("Enter a circle or triangle in WKT format\n");
    printf("After entering the figures, enter any non-alphabetic character or press Enter again to complete the entry\n");
    while (fgets(str, SIZE_OF_ARR, stdin))
    {
        curs = str;
        end = str;
        circ = 0;
        to_lower_all_str(str);
        skip_space(&circ, &curs, &end);
        is_letter(&circ, &curs, &end);
        if (strncmp(curs, "circle", end - curs) == 0) //ПРОВЕРКА НА CIRCLE
        {
            parse_circle(&circ, &curs, &end, &record_counter);
        }
        else
        {
            if (strncmp(curs, "triangle", end - curs) == 0) //ПРОВЕРКА НА TRIANGLE
            {
                parse_triangle(&circ, &curs, &end, &record_counter);
            }
            else
            {
                for (int flag = 0; flag < circ; flag++)
                {
                    printf(" ");
                }
                printf("^\n");
                printf("Error at column %d: expected 'circle' or 'triangle'\n", circ);
            }
        }
    }
}

bool skip_space(int *circ, char **first, char **second)
{
    while (isspace(**first))
    {
        *first = *first + 1;
        *second = *second + 1;
        *circ = *circ + 1;
    }
    return true;
}

bool is_sign(char token, int *circ, char **first, char **second)
{
    if (**first != token)
    {
        for (int flag = 0; flag < *circ; flag++)
        {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '%c'\n", *circ, token);
        return false;
    }
    else
    {
        *first = *first + 1;
        *second = *second + 1;
        *circ = *circ + 1;
    }
    return true;
}

bool add_word_length(int *circ, char **first, char **second)
{
    *circ = *circ + (*second - *first);
    *first = *second;
    return true;
}

bool is_number(int *circ, char **first, char **second)
{
    if (isdigit(**first) == 0)
    {
        for (int flag = 0; flag < *circ; flag++)
        {
            printf(" ");
        }
        printf("^\n");
        printf("Error at column %d: expected '<double>'\n", *circ);
        return false;
    }
    return true;
}

bool is_EOF(int *circ, char **first)
{
    if (**first != '\0')
    {
        for (int flag = 0; flag < *circ; flag++)
        {
            printf(" ");
        }
        printf("^\n");
        printf("unexpected token\n");
        return false;
    }
    return true;
}

bool is_letter(int *circ, char **first, char **second)
{
    if ((**second >= '\x61') && (**second <= '\x7a'))
    {
        while (**second != ' ')
        {
            *second = *second + 1;
        }
    }
    else
    {
        printf("Input completed");
        exit(0);
    }
    return true;
}

bool to_lower_all_str(char *array)
{
    for (int i = 0; i < SIZE_OF_ARR; i++)
    {
        array[i] = tolower(array[i]);
    }
    return true;
}

bool parse_circle(int *circ, char **curs, char **end, unsigned int *record_counter)
{
    struct Circle var_circle;
    bool error = true;
    for (;;)
    {
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(40, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double x = strtod(*curs, end); //ПАРСИНГ X
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double y = strtod(*curs, end); //ПАРСИНГ Y
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(44, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double radius = strtod(*curs, end); //ПАРСИНГ РАДИУСА
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(41, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_EOF(circ, curs);
        if (error == true)
        {
            var_circle.x[*record_counter] = x;
            var_circle.y[*record_counter] = y;
            var_circle.radius[*record_counter] = radius;
            printf("The circle has been added successfully!\n");
            printf("Your figure - circle(%.1f %.1f, %.1f)\n", var_circle.x[*record_counter],
                   var_circle.y[*record_counter], var_circle.radius[*record_counter]);
            *record_counter = *record_counter + 1;
            break;
        }
        else
        {
            printf("The circle has NOT been added !\n");
            break;
        }
    }
    return true;
}

bool parse_triangle(int *circ, char **curs, char **end, unsigned int *record_counter)
{
    struct Triangle var_triangle;
    bool error = true;
    for (;;)
    {
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(40, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_sign(40, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end); //
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double x1 = strtod(*curs, end); //ПАРСИНГ X
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double y1 = strtod(*curs, end); //ПАРСИНГ Y1
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(44, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end); //
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double x2 = strtod(*curs, end); //ПАРСИНГ X2
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double y2 = strtod(*curs, end); //ПАРСИНГ Y2
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(44, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end); //
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double x3 = strtod(*curs, end); //ПАРСИНГ X3
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double y3 = strtod(*curs, end); //ПАРСИНГ Y3
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(44, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double x4 = strtod(*curs, end); //ПАРСИНГ X4
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_number(circ, curs, end);
        if (error != true)
            break;
        double y4 = strtod(*curs, end); //ПАРСИНГ Y4
        add_word_length(circ, curs, end);
        skip_space(circ, curs, end);
        error = is_sign(41, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_sign(41, circ, curs, end);
        if (error != true)
            break;
        skip_space(circ, curs, end);
        error = is_EOF(circ, curs);
        if ((error == true) && (x1 == x4) && (y1 == y4))
        {
            var_triangle.x1[*record_counter] = x1;
            var_triangle.x2[*record_counter] = x2;
            var_triangle.x3[*record_counter] = x3;
            var_triangle.x4[*record_counter] = x4;
            var_triangle.y1[*record_counter] = y1;
            var_triangle.y2[*record_counter] = y2;
            var_triangle.y3[*record_counter] = y3;
            var_triangle.y4[*record_counter] = y4;
            printf("The triangle has been added successfully!\n");
            printf("Your figure - triangle((%.1f %.1f, %.1f %.1f, %.1f %.1f, %.1f %.1f))\n", var_triangle.x1[*record_counter], var_triangle.y1[*record_counter],
                   var_triangle.x2[*record_counter], var_triangle.y2[*record_counter], var_triangle.x3[*record_counter],
                   var_triangle.y3[*record_counter], var_triangle.x4[*record_counter], var_triangle.y4[*record_counter]);
            *record_counter = *record_counter + 1;
            break;
        }
        else
        {
            printf("The triangle has NOT been added !\n");
            break;
        }
    }
    return true;
}