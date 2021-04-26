#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

// for like animation using like texture rects

// actual animation should be like an array of these or something
typedef struct {
	SDL_Rect rect;
	float delay; // time until next frame 
} animationFrame;

typedef struct {
	SDL_Texture* texture;
	animationFrame* frames;
	Uint16 length; // length in frames
	Uint16 index; // where the animation is at now
	float timer; // to check if enough time has passed to go to the next frame
} animationStruct;

#endif
