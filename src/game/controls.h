#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
	bool held;
	float pressedTimer; // Timer for how long the key is considered "pressed" instead of "held"
	SDL_Keycode keycode;
} key;

enum CONTROLS{UP, DOWN, LEFT, RIGHT, PLAY_SOUND, EXIT, CONTROLS_LENGTH};
extern key keys[CONTROLS_LENGTH]; 

void initControls();

#endif
