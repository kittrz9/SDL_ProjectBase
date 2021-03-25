#ifndef TYPES_H
#define TYPES_H

// Hopefully will add more types than just vec2f 

// Tells GCC a variable is unused, put before the variable's declaration
// Pretty much just here because of -Wextra lmao
#define UNUSED __attribute__((unused))

typedef struct {
	float x, y;
} vec2f;

#endif
