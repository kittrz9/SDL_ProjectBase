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

typedef struct {
    bool held;
    float pressedTimer; // Timer for how long the key is considered "pressed" instead of "held"
    SDL_Keycode keycode;
} key;

// I don't really remember exactly why I have the gameloop seperate from the main function besides like having the SDL initialization stuff being seperate from everything else
int gameLoop(SDL_Window* screen, SDL_Renderer* renderer) {
	bool running = true;
	SDL_Event event;
	unsigned int lastTime = 0, currentTime = SDL_GetPerformanceCounter();
	double deltaTime = 0;

    // Controls stuff
    enum CONTROLS{UP, DOWN, LEFT, RIGHT, EXIT, CONTROLS_LENGTH};
    key keys[CONTROLS_LENGTH]; 
    // Really need to figure out how to do like a config file or something instead of hardcoding this stuff lmao
    keys[UP].keycode = SDLK_UP;
    keys[DOWN].keycode = SDLK_DOWN;
    keys[LEFT].keycode = SDLK_LEFT;
    keys[RIGHT].keycode = SDLK_RIGHT;
    keys[EXIT].keycode = SDLK_ESCAPE;
    // Also I guess I need this because it isn't always just initialized to false(?)
    for(int i = 0; i < CONTROLS_LENGTH; i++){
        keys[i].held = false;
    }
    
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
		// Check if keys are held
        if(keys[UP].held) {
            player->vel.y = -2;
        } else if(keys[DOWN].held) {
            player->vel.y =  2;
        } else {
            player->vel.y =  0;
        }
        
        if(keys[LEFT].held) {
            player->vel.x = -2;
        } else if(keys[RIGHT].held) {
            player->vel.x =  2;
        } else {
            player->vel.x =  0;
        }
        
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

		// Entity stuff
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
