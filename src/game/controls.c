#include "controls.h" 

// I need this for some reason to have the extern thing work
key keys[CONTROLS_LENGTH]; 

void initControls() {
	// Really need to figure out how to do like a config file or something instead of hardcoding this stuff lmao
	keys[UP].keycode = SDLK_UP;
	keys[DOWN].keycode = SDLK_DOWN;
	keys[LEFT].keycode = SDLK_LEFT;
	keys[RIGHT].keycode = SDLK_RIGHT;
	keys[EXIT].keycode = SDLK_ESCAPE;
	keys[PLAY_SOUND].keycode = SDLK_SPACE;
	// Also I guess I need this because it isn't always just initialized to false(?)
	for(int i = 0; i < CONTROLS_LENGTH; i++){
		keys[i].held = false;
		keys[i].pressedTimer = 0.0;
	}
}
