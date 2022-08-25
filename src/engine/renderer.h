#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color;
extern color screenClearColor;
void setScreenClearColor(uint8_t r, uint8_t g, uint8_t b);

extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif
