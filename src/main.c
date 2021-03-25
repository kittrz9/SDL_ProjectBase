#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdio.h>

#include "gameLoop.h"
#include "text.h"
#include "types.h"

// Should probably be moved away from main.c since other things need to use the screen size
#define WIDTH 800
#define HEIGHT 600

int main(UNUSED int argc, UNUSED char** argv){
// 	SDL_Init(SDL_INIT_EVERYTHING);
 	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}
	TTF_Init();
	
	// Probably shouldn't be hardcoded to check for this specific font
	font = TTF_OpenFont("res/TerminusTTF-4.47.0.ttf", 24);
	if(!font) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open font: %s\n", SDL_GetError());
		return 1;
	}
	
	formatStr = malloc(MAX_STR_LEN);
	
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

	// Window stuff
	SDL_Window* screen = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
	if(!screen) {
		//printf("Couldn't create window\n");
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s\n", SDL_GetError());
		return 1;
	}
	if(!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create renderer: %s\n", SDL_GetError());
		return 1;
	}
	SDL_SetWindowTitle(screen, "bruh");

	// Main loop
	gameLoop(screen, renderer);

	// Free resources and end
	free(formatStr);
	// Quit SDL_ttf
	TTF_CloseFont(font);
	TTF_Quit();
	// Quit SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return 0;
}
