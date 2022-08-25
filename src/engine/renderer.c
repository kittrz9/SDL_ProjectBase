#include "renderer.h"
 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

color screenClearColor;

void setScreenClearColor(uint8_t r, uint8_t g, uint8_t b) {
	screenClearColor = (color){
		.r = r,
		.g = g,
		.b = b
	};
}
