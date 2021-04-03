#include "audio.h"

#include <SDL2/SDL.h>
#include <types.h>

#if defined(WIN32) || defined(_WIN32)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdlib.h>

Mix_Chunk* sounds[SOUNDS_LENGTH];

void loadSound(enum SOUND_ID sound, SDL_RWops* rw){
	printf("Loading sound %i\n", sound);
	
	sounds[sound] = Mix_LoadWAV_RW(rw, 1);
	
	if(sounds[sound] == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load sound: %s\n", SDL_GetError());
		return;
	}
	
	return;
}

void playSound(enum SOUND_ID sound, int loops){
	for(int i = 0; i < AUDIO_CHANNELS_AMOUNT; i++){
		if(Mix_Playing(i) == 0){
			Mix_PlayChannel(i, sounds[sound], loops);
			break;
		}
	}
	
	return;
}

#define PI  M_PI
#define PI2 PI*2

// (2^16) / 2
#define OFFSET 32768

// https://gist.github.com/amirrajan/fa6ce9fdc8918e06ca9759c3358e4cd2
Mix_Chunk* createSound(synthFunc synth, synthData* data){
	// Has to be multiplied by 16 because the audio format is U16 I think
	// Should probably make this be like larger or lower size depending on the release part of the ADSR thing or whatever
	size_t size = data->length * MIX_DEFAULT_FREQUENCY*16;
	Uint16* audioBuffer = malloc(size * sizeof(Uint16));
	
	double time = 0, freq = data->startFreq, attack = 0;
	
	for(size_t i = 0; i < size; i++){
		audioBuffer[i] = synth(time) * attack;
		
		freq += (data->endFreq - data->startFreq)/size;
		attack += (attack >= 1.0 ? 0 : (1/(data->attack))/size);
		
		// Frequency also has to be divided by 8 for some reason to get the actual frequency, idk why
		time += freq/8 * PI2 / MIX_DEFAULT_FREQUENCY;
		if(time >= PI2) { time -= PI2; }
	}
	
	Mix_Chunk* chunk = malloc(sizeof(Mix_Chunk));
	chunk->allocated = 1;
	chunk->abuf = (Uint8*)audioBuffer;
	chunk->alen = size;
	chunk->volume = data->volume;
	return chunk;
}

Uint16 synthSine(float time){
	return (Uint16)((OFFSET * sin(time)) + OFFSET);
}

Uint16 synthSquare(float time){
	return (Uint16)(time < PI ? 0 : OFFSET);
}

// Should probably find a way to make this change the pitch depending on the time
Uint16 synthNoise(UNUSED float time){
	return (Uint16)(rand());
}

Uint16 synthSaw(float time){
	return (Uint16)(OFFSET - ((time/PI2)*OFFSET));
}

Uint16 synthTriangle(float time){
	return (Uint16)((time < PI ? ((time/PI2)*OFFSET) : (OFFSET - (time/PI2)) ));
}
