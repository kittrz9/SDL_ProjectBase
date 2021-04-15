#ifndef DEFINES_H
#define DEFINES_H

#define UNUSED __attribute__((unused))

#define WIDTH 800
#define HEIGHT 600


// math defines
#if defined(WIN32) || defined(_WIN32)
#define _USE_MATH_DEFINES
#endif

#define PI  M_PI
#define PI2 PI*2

#endif
