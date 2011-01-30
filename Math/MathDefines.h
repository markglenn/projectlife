#pragma once

#include <math.h>

#define EPSILON 0.0001f

#define PI 3.1415926535898f

#define SQR(x) ((x) * (x))
#define DEG2RAD(x) ((x) / 180.f * (PI))

#define MAX(x, y) (((x) < (y)) ? (y) : (x))
#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define ABS(x) (((x) < 0) ? (-(x)) : (x))

