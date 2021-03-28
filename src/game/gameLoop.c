#include <SDL2/SDL.h>
#include <stdbool.h>

#include "gameLoop.h"
#include "gameStates.h"
#include "entity.h"
#include "controls.h"
#include "player.h"
#include "text.h"
#include "audio.h"

// I don't really remember exactly why I have the gameloop seperate from the main function besides like having the SDL initialization stuff being seperate from everything else
int gameLoop(UNUSED SDL_Window* screen, SDL_Renderer* renderer) {
	SDL_Event event;
	unsigned int lastTime = 0, currentTime = SDL_GetPerformanceCounter();
	double deltaTime = 0;

	initControls();
	
	// Should probably change this from just a basic sine wave but it's just for testing so whatever
	loadSound(SOUND_TEST, SDL_RWFromFile("res/sounds/test.mp3", "rb"));
    
	// Create player entity
	// Returns a pointer to the player but does nothing with it lmao
	createPlayer(50, 50, 100, 100);
	
	while(running){
		// Event handling
		while(SDL_PollEvent(&event)){
			switch(event.type){
				// Check if the key that has either been pressed or released corresponds to any of the controls that have been set up
				case SDL_KEYDOWN:
					for(int i = 0; i < CONTROLS_LENGTH; i++){
						if(event.key.keysym.sym == keys[i].keycode){
							keys[i].held = true;
							keys[i].pressedTimer = 0.2;
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
		
		// Could/should probably be moved to the gamestates in case there's points where you wouldn't want to be able to just like accidentally press the exit key (Like when saving or something idk)
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
		
		// Run the current game state
		if((*gameState)(screen, renderer, deltaTime)) {running = false;}

		// Render everything to the screen
		SDL_RenderPresent(renderer);

		// Deltatime stuff
		lastTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();

		// Deltatime is in milliseconds, not seconds
		deltaTime = (double)((currentTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency());
		// I think there's something wrong with how I'm calculating the delta time since when the framerate is really low and deltatime should be really high it says it's something like 4 milliseconds
		//printf("%f\n", deltaTime);
	}

	destroyEntityList();

	return 0;
}
