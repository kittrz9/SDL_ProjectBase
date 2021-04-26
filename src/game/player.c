#include "player.h"

#include <SDL2/SDL_image.h>

#include "defines.h"
#include "animation.h"

#define playerObj ((playerStruct*)(ent->object))


animationFrame testAnimation[] = {
	{
		.rect={
			.x=0,
			.y=0,
			.w=326,
			.h=379,
		},
		.delay=0.1f,
	},
	{
		.rect={
			.x=326,
			.y=0,
			.w=326,
			.h=379,
		},
		.delay=0.1f,
	}
};

struct entity* createPlayer(SDL_Renderer* renderer, float x, float y, float w, float h){
	// Create player entity
	struct entity* ent = malloc(sizeof(struct entity));
	ent->object = malloc(sizeof(playerStruct));
	playerObj->animation = malloc(sizeof(animationStruct));
	playerObj->pos.x = x;
	playerObj->pos.y = y;
	playerObj->size.x = w;
	playerObj->size.y = h;
	
	playerObj->animation->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("res/test.png"));
	playerObj->animation->timer = 0.0f;
	playerObj->animation->index = 0;
	playerObj->animation->frames = testAnimation;
	playerObj->animation->length = sizeof(testAnimation)/sizeof(animationFrame);
	
	//playerObj->animationTimer = 0.0f;
	//playerObj->animationIndex = 0;
	//playerObj->animationTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("res/test.png"));
	
	ent->draw = drawPlayer;
	ent->update = updatePlayer;
	pushToEntityList(ent);
	return ent;
}

void drawPlayer(struct entity* ent, SDL_Renderer* renderer){
	SDL_Rect drawRect;
	drawRect.x = playerObj->pos.x;
	drawRect.y = playerObj->pos.y;
	drawRect.w = playerObj->size.x;
	drawRect.h = playerObj->size.y;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(renderer, &drawRect);
	// REALLY need to change this so I don't have to have this massive line of code just because I'm accessing pointers to structs in pointers from structs from pointers lmao
	SDL_RenderCopyEx(renderer, playerObj->animation->texture, &playerObj->animation->frames[playerObj->animation->index].rect, &drawRect, 0, NULL, (playerObj->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void updatePlayer(struct entity* ent, double deltaTime){
	playerObj->pos.x += playerObj->vel.x * deltaTime;
	playerObj->pos.y += playerObj->vel.y * deltaTime;
	
	bool moving = false;

#define GRAVITY 0.001f
	if(playerObj->pos.y < HEIGHT - playerObj->size.y){
		playerObj->vel.y += GRAVITY;
	}
	
	// i really dont care enough to make it check if you're on the ground, it's funny being able to constantly jump
	if(keys[UP].pressedTimer > 0.0){
		playerObj->vel.y = -2;
	}
	
	if(keys[LEFT].held) {
		playerObj->facingLeft = true;
		playerObj->vel.x = -1;
		moving = true;
	} else if(keys[RIGHT].held) {
		playerObj->facingLeft = false;
		playerObj->vel.x =  1;
		moving = true;
	} else {
		playerObj->vel.x =  0;
	}
	
	if(moving){
		playerObj->animation->timer += deltaTime;
		if(playerObj->animation->timer >= playerObj->animation->frames[playerObj->animation->index].delay * 1000){
			playerObj->animation->timer = 0.0f;
			if(playerObj->animation->index >= sizeof(testAnimation)/sizeof(animationFrame) - 1){
				playerObj->animation->index = 0;
			} else {
				playerObj->animation->index++;
			}
		}
	} else {
		playerObj->animation->timer = 0.0f;
		playerObj->animation->index = 0;
	}
	
	
	// Boundary check
	if(playerObj->pos.x < 0) {playerObj->pos.x = 0;}
	if(playerObj->pos.y < 0) {playerObj->pos.y = 0; playerObj->vel.y = 0;}
	if(playerObj->pos.x > WIDTH - playerObj->size.x) {playerObj->pos.x = WIDTH - playerObj->size.x;}
	if(playerObj->pos.y > HEIGHT - playerObj->size.y) {playerObj->pos.y = HEIGHT - playerObj->size.y;}
}
