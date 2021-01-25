#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

#include "gameLoop.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_EVERYTHING);

	// Window stuff
	SDL_Window* screen = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
	if(!screen) {
		printf("Couldn't create window\n");
	}
	if(!renderer) {
		printf("Couldn't create renderer\n");
	}
	SDL_SetWindowTitle(screen, "bruh");

	// Main loop
	gameLoop(screen, renderer);

	// End
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return 0;
}
