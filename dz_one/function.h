#ifndef FUNCTION_H
#define FUNCTION_H

#include <cmath>


float calculate_distance_squared(float* x, float* y);
bool is_in_circle(float* x, float* y, float radius);
bool is_in_square(float* x, float* y, float side_length);

extern int radius;
extern int side_length;
extern float coord_x;
extern float coord_y;

#endif