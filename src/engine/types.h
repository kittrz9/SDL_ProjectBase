#ifndef TYPES_H
#define TYPES_H

// Tells GCC a variable is unused, put before the variable's declaration
// Pretty much just here because of -Wextra lmao
#define UNUSED __attribute__((unused))

typedef struct {
	float x, y;
} vec2f;

// Probably would be used for like SDL_GetMouseState and whatever since they make you pass a pointer to an int to be overwritten with the mouse position
typedef struct {
	int x, y;
} vec2i;

// Probably would be useful if you're doing like actual 3d rendering but I have no clue how to do like perspective projection or wh atever
typedef struct {
	float x, y, z;
} vec3f;

#endif
