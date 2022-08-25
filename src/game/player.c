#include "player.h"

#include <SDL2/SDL_image.h>

#include "defines.h"
#include "animation.h"
#include "audio.h"
#include "renderer.h"
#include "resourceManager.h"

#define playerObj ((playerStruct*)(ent->object))

// should probably make a sort of file format for animations instead of making them have to be hardcoded
animationFrame runAnimation[] = {
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

animationFrame idleAnimation[] = {
	{
		.rect={
			.x=0,
			.y=0,
			.w=326,
			.h=379,
		},
		.delay=-1.0f,
	}
};

struct entity* createPlayer(float x, float y, float w, float h){
	// Create player entity
	struct entity* ent = malloc(sizeof(struct entity));
	ent->object = malloc(sizeof(playerStruct));
	playerObj->animation = malloc(sizeof(animationStruct));
	playerObj->pos.x = x;
	playerObj->pos.y = y;
	playerObj->size.x = w;
	playerObj->size.y = h;
	playerObj->vel.x = 0;
	playerObj->vel.y = 0;
	
	playerObj->jumpTimer = 0.0f;
	
	playerObj->animation->textureResource = loadResource(RES_TYPE_TEXTURE, "test.png");
	playerObj->animation->timer = 0.0f;
	playerObj->animation->index = 0;
	playerObj->animation->frames = idleAnimation;
	playerObj->animation->length = sizeof(idleAnimation)/sizeof(animationFrame);
	playerObj->animation->nextAnim = NULL;
	
	playerObj->moving = false;
	playerObj->facingLeft = false;
	
	ent->draw = drawPlayer;
	ent->update = updatePlayerInAir;
	
	ent->destructor = destroyPlayer;
	pushToEntityList(ent);
	return ent;
}

void destroyPlayer(struct entity* ent){
	free(playerObj->animation);
	
	return;
}

void drawPlayer(struct entity* ent){
	SDL_Rect drawRect = {
		.x = playerObj->pos.x,
		.y = playerObj->pos.y,
		.w = playerObj->size.x,
		.h = playerObj->size.y,
	};

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// REALLY need to change this so I don't have to have this massive line of code just because I'm accessing pointers to structs in pointers from structs from pointers lmao
	SDL_RenderCopyEx(renderer, playerObj->animation->textureResource->pointer, &playerObj->animation->frames[playerObj->animation->index].rect, &drawRect, 0, NULL, (playerObj->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
	
	return;
}

// jump sound data
// having these as const gives the "disregards const qualifier" warning
synthInstrument jumpSndInstr = {
	.envelope = {
		.attack = 0.01,
		.decay = 0.05f,
		.sustain = 0.8f,
		
		.release = 0.2f,
	},
	.synth = synthSine,
};
synthData jumpSndData = {
	.startFreq = 220.0,
	.endFreq = 440.0,
	.volume = 1.0,
	.length = 0.05f,
	.instrument = &jumpSndInstr,
};


void playerBoundaryCheck(struct entity* ent){
	if(playerObj->pos.x < 0) {playerObj->pos.x = 0;}
	if(playerObj->pos.y < 0) {playerObj->pos.y = 0; playerObj->vel.y = 0;}
	if(playerObj->pos.x > WIDTH - playerObj->size.x) {playerObj->pos.x = WIDTH - playerObj->size.x;}
	if(playerObj->pos.y > HEIGHT - playerObj->size.y) {playerObj->pos.y = HEIGHT - playerObj->size.y;}
}


#define MAX_RUN_SPEED 0.8
#define PLAYER_RUN_ACCEL 0.008

// the physics stuff done for both states
void commonPhysicsCheck(struct entity* ent, double deltaTime){		
	playerObj->pos.x += playerObj->vel.x * deltaTime;
	playerObj->pos.y += playerObj->vel.y * deltaTime;
	
	playerBoundaryCheck(ent);
	
	if(keys[LEFT].held) {
		playerObj->facingLeft = true;
		if(playerObj->vel.x > -MAX_RUN_SPEED){
			playerObj->vel.x -= PLAYER_RUN_ACCEL * deltaTime;
		} else {
			playerObj->vel.x = -MAX_RUN_SPEED;
		}
		playerObj->moving = true;
	} else if(keys[RIGHT].held) {
		playerObj->facingLeft = false;
		if(playerObj->vel.x < MAX_RUN_SPEED){
			playerObj->vel.x += PLAYER_RUN_ACCEL * deltaTime;
		} else {
			playerObj->vel.x = MAX_RUN_SPEED;
		}
		playerObj->moving = true;
	} else {
		playerObj->vel.x =  0;
		playerObj->moving = false;
	}
}

void updatePlayerOnGround(struct entity* ent, double deltaTime){
	commonPhysicsCheck(ent, deltaTime);
	
	if(keys[UP].pressedTimer > 0.0){
		jumpSndData.panning = (((playerObj->pos.x + playerObj->size.x/2) / WIDTH)*2) - 1;
		playSynth(&jumpSndData);
		playerObj->vel.y = -2;
		ent->update = updatePlayerInAir;
	}
	
	if(playerObj->moving && playerObj->animation->frames != runAnimation){
		setAnimation(playerObj->animation, runAnimation, sizeof(runAnimation)/sizeof(animationFrame));
	} else if(!playerObj->moving){
		setAnimation(playerObj->animation, idleAnimation, sizeof(idleAnimation)/sizeof(animationFrame));
	}
	
	updateAnimation(playerObj->animation, deltaTime);
	
	// Boundary check
	playerBoundaryCheck(ent);
}

void updatePlayerInAir(struct entity* ent, double deltaTime){
	commonPhysicsCheck(ent, deltaTime);
	
	if(playerObj->jumpTimer > 0.0){
		playerObj->jumpTimer -= deltaTime * 0.001; // converting milliseconds to seconds
	}
	
	if(keys[UP].pressedTimer > 0.0 && playerObj->jumpTimer <= 0.0){
		playerObj->jumpTimer = 0.05; // in seconds
	}
	
	if(playerObj->moving && playerObj->animation->frames != runAnimation){
		setAnimation(playerObj->animation, runAnimation, sizeof(runAnimation)/sizeof(animationFrame));
	} else if(!playerObj->moving){
		setAnimation(playerObj->animation, idleAnimation, sizeof(idleAnimation)/sizeof(animationFrame));
	}
	
	updateAnimation(playerObj->animation, deltaTime);
	
	// apply gravity and check for jump 
#define GRAVITY 0.01f
	if(playerObj->pos.y < HEIGHT - playerObj->size.y){
		playerObj->vel.y += GRAVITY * deltaTime;
	} else if(playerObj->jumpTimer > 0.0) {
		playSynth(&jumpSndData);
		playerObj->pos.y = HEIGHT - playerObj->size.y;
		playerObj->vel.y = -2;
	} else {
		ent->update = updatePlayerOnGround;
	}
	
	playerBoundaryCheck(ent);
}
