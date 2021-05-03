#include <stdio.h>
#include <stdlib.h>
int Arr(char* arr, int size, int* j)
{
    arr[0] = 40;
    arr[1] = 40;
    arr[2] = 40;
    *j = 99;
    return 0;
}

int main()
{
    int j = 0;
    char arr[3];
    Arr(arr, 3, &j);
    printf("%d", j);
    puts(arr);
}