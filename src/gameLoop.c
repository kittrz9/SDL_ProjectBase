#include <SDL2/SDL.h>
#include <stdbool.h>

#include "gameLoop.h"
#include "gameStates.h"
#include "entity.h"
#include "controls.h"
#include "player.h"
#include "text.h"

// I don't really remember exactly why I have the gameloop seperate from the main function besides like having the SDL initialization stuff being seperate from everything else
int gameLoop(SDL_Window* screen, SDL_Renderer* renderer) {
	SDL_Event event;
	unsigned int lastTime = 0, currentTime = SDL_GetPerformanceCounter();
	double deltaTime = 0;

	initControls();
    
	// Create player entity
	struct entity* player = malloc(sizeof(struct entity));
	player->pos.x = 50;
	player->pos.y = 50;
	player->size.x = 100;
	player->size.y = 100;
	player->draw = drawPlayer;
	player->update = updatePlayer;
	pushToEntityList(player);

	while(running){
		// Event handling
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					for(int i = 0; i < CONTROLS_LENGTH; i++){
						if(event.key.keysym.sym == keys[i].keycode){
							keys[i].held = true;
							keys[i].pressedTimer = 0.1;
						}
					}
					break;

				case SDL_KEYUP:
					for(int i = 0; i < CONTROLS_LENGTH; i++){
						if(event.key.keysym.sym == keys[i].keycode){
							keys[i].held = false;
							keys[i].pressedTimer = 0.0;
						}
					}
					break;

				case SDL_QUIT:
					running = false;
					break;

				default:break;
			}
		}
		// Do stuff
		if(keys[EXIT].held) {
			running = false;
		}
        
		// Decrement the pressed timer for each key if they're being pressed
		for(int i = 0; i < CONTROLS_LENGTH; i++){
			if(keys[i].pressedTimer > 0.0) {
				keys[i].pressedTimer -= deltaTime;
			}
		}

		// Clear the screen/renderer
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		
		if((*gameState)(screen, renderer, deltaTime)) {running = false;}

		// Render everything to the screen
		SDL_RenderPresent(renderer);


		// Deltatime stuff
		lastTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();

		// Deltatime is in milliseconds, not seconds
		deltaTime = (double)((currentTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency());
	}

	destroyEntityList();

	return 0;
}
