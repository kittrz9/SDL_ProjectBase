#include <SDL2/SDL.h>
#include <stdbool.h>

#include "gameLoop.h"

int gameLoop(SDL_Window* screen, SDL_Renderer* renderer) {
	bool running = true;
	SDL_Event event;
	unsigned int frames = 0;
	unsigned int lastTime = 0, currentTime;
	while(running){
		// Event handling
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							running = false;
							break;

						default: break;
					}
					break;

				case SDL_QUIT:
					running = false;
					break;

				default:break;
			}
		}
		// Other stuff to do goes here lmao
		

		// Clear the screen/renderer
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		frames++;

		currentTime = SDL_GetTicks();
		if(currentTime > lastTime + 1000) {
			printf("FRAMES: %i\nTIME (milliseconds): %i\n\n", frames, currentTime);
			frames = 0;
			lastTime = currentTime;
		}
	}

	return 0;
}
