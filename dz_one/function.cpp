#include "function.h"

int radius = 1;
int side_length = 1;
float coord_x = 0;  
float coord_y = 0; 

float calculate_distance_squared(float* x, float* y)
{
    return (*x * *x) + (*y * *y);
}

bool is_in_circle(float* x, float* y, float radius)
{
    return calculate_distance_squared(x, y) <= (radius * radius);
}

bool is_in_square(float* x, float* y, float side_length)
{
    return (abs(*x) <= (side_length / 2)) && (abs(*y) <= (side_length / 2));
}
