#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>
#include <stdio.h>

#include "defines.h"
#include "gameLoop.h"
#include "text.h"
#include "types.h"
#include "audio.h"
#include "renderer.h"
#include "resourceManager.h"

#define init(x) if(x < 0) {\
			printf(#x " failed: %s\n", SDL_GetError());\
			return 1;\
		}

// argc and argv are unused for now but might eventually use them later idk
int main(UNUSED int argc, char** argv){
	init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO));
	init(TTF_Init());
	// for some reason I set the channels parameter set wrong, I thought it was how many audio channels were allocated and not whether or not it was stereo or mono. the docs literally say "This has nothing to do with mixing channels." lmao why am I so stupid
	init(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_U16LSB, 2, 256)); // having the chunk size at 2048 was making the sounds seem to play later than they should, and reducing it to 256 didn't make it sound any worse. I think I put 2048 because it was half of what the SDL_mixer docs recommended
	
	formatStr = malloc(MAX_STR_LEN);
	
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
	
	// Set callback for when channel is done playing to free the chunk that was playing
	Mix_ChannelFinished(freeAudioChannelChunk);

	// Window stuff
	// window and renderer defined in renderer.h and renderer.c
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
	if(!window) {
		//printf("Couldn't create window\n");
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s\n", SDL_GetError());
		return 1;
	}
	if(!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create renderer: %s\n", SDL_GetError());
		return 1;
	}

	// assumes the path wont have "build" unless being ran in the build directory, should probably be changed but whatever
	char* c = &argv[0][0];
	const char buildstr[] = "build";
	char* c2 = &buildstr[0];
	while(*c != '\0') {
		if(*c2 == *c) {
			++c2;
		}
		if(*c2 == '\0') {
			break;
		}
		++c;
	}
	// only has "build" in the path if being ran outside of the build dir
	if(*c2 != '\0') {
		printf("in build dir\n");
		setResourceDirectory("../res/");
	} else {
		printf("not in build dir\n");
		setResourceDirectory("res/");
	}

	SDL_SetWindowTitle(window, "bruh");

	// Main loop
	gameLoop();
	
	// destroy resources
	clearResourceList();

	// Free resources and end
	free(formatStr);
	// Quit SDL_ttf
	TTF_Quit();
	// Quit SDL_mixer
	Mix_CloseAudio();
	// Quit SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

