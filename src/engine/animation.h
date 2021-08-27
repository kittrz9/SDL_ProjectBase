#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include "resourceManager.h"

// for like animation using like texture rects

// actual animation should be like an array of these or something
typedef struct {
	SDL_Rect rect;
	float delay; // time until next frame 
} animationFrame;

typedef struct {
	resource* textureResource; // pointer to the resource struct
	animationFrame* frames;
	Uint16 length; // length in frames
	Uint16 index; // where the animation is at now
	float timer; // to check if enough time has passed to go to the next frame
	
	animationFrame* nextAnim; // next animation to be played once this animation is completed, just repeat animation if NULL
	Uint16 nextAnimLength; // really stupid how I need to have the length of the next array since I can't get the size of an array from a pointer
} animationStruct;

void setAnimation(animationStruct* anim, animationFrame* frames, Uint16 length);
void updateAnimation(animationStruct* anim, double deltaTime);

#endif
