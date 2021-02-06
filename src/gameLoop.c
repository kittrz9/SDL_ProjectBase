#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "gameLoop.h"
#include "entity.h"

void drawPlayer(struct entity* ent, SDL_Renderer* renderer){
    SDL_Rect rect; // Maybe like unoptimal to have this always being created every time the player needs to be drawn but idk maybe the compiler will optimize it? I also feel like it's better than when I just had the SDL_Rect in the entity's struct
	rect.x = ent->pos.x;
	rect.y = ent->pos.y;
	rect.w = ent->size.x;
	rect.h = ent->size.y;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void updatePlayer(struct entity* ent, double deltaTime){
	ent->pos.x += ent->vel.x * deltaTime;
	ent->pos.y += ent->vel.y * deltaTime;

	if(ent->pos.x < 0) {ent->pos.x = 0;}
	if(ent->pos.y < 0) {ent->pos.y = 0;}
	// Really need to fix these numbers here but I don't really want to right now
	if(ent->pos.x > 800 - ent->size.x) {ent->pos.x = 800 - ent->size.x;}
	if(ent->pos.y > 600 - ent->size.y) {ent->pos.y = 600 - ent->size.y;}
}

int gameLoop(SDL_Window* screen, SDL_Renderer* renderer) {
	bool running = true;
	SDL_Event event;
	unsigned int lastTime = 0, currentTime = SDL_GetPerformanceCounter();
	double deltaTime = 0;

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
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							running = false;
							break;

						default: break;
					}
					break;

				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_UP:
						case SDLK_DOWN:
							player->vel.y = 0;
							break;
						case SDLK_LEFT:
						case SDLK_RIGHT:
							player->vel.x = 0;
							break;

						default:break;
					}
					break;

				case SDL_QUIT:
					running = false;
					break;

				default:break;
			}
		}
		// Do stuff
		// Check if keys are held
		// Probably would be better to somehow combine both checking if a key is held and checking if it's pressed into the same thing but whatever
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_LEFT]){
			player->vel.x = -2;
		}
		if(state[SDL_SCANCODE_RIGHT]){
			player->vel.x =  2;
		}
		if(state[SDL_SCANCODE_UP]){
			player->vel.y = -2;
		}
		if(state[SDL_SCANCODE_DOWN]){
			player->vel.y =  2;
		}

		// Clear the screen/renderer
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);

		// Draw stuff
		for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
			// Call the entity's draw function
			(*entListCurrent->ent->draw)(entListCurrent->ent, renderer);
			// Call the entity's update function
			(*entListCurrent->ent->update)(entListCurrent->ent, deltaTime);
		}

		// Render everything to the screen
		SDL_RenderPresent(renderer);


		// Deltatime stuff
		lastTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();

		deltaTime = (double)((currentTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency());
	}
	removeFromEntityList(player);

	return 0;
}
