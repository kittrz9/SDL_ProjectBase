#include "audio.h"

#include <SDL2/SDL.h>
#include <types.h>

#include <math.h>
#include <stdlib.h>

// Needed for freeing Mix_Chunks
Mix_Chunk* audioChannelChunks[AUDIO_CHANNELS_AMOUNT];

// Callback function for Mix_ChannelFinished 
void freeAudioChannelChunk(int channel){
	Mix_FreeChunk(audioChannelChunks[channel]);
	return;
}

#define PI  3.14159265358
#define PI2 6.28318530718

// (2^16) / 2
#define OFFSET 32768

// https://gist.github.com/amirrajan/fa6ce9fdc8918e06ca9759c3358e4cd2
void playSynth(synthFunc synth, synthData* data){
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
	
	for(int i = 0; i < AUDIO_CHANNELS_AMOUNT; i++){
		if(Mix_Playing(i) == 0){
			Mix_PlayChannel(i, chunk, 0);
			audioChannelChunks[i] = chunk;
			break;
		}
	}
	
	return chunk;
}


// Really ugly hard to read math shit
synthFunc synthSine(float time){
	return (Uint16)((OFFSET * sin(time)) + OFFSET);
}

synthFunc synthSquare(float time){
	return (Uint16)(time < PI ? 0 : (OFFSET*2)-1);
}

// Should probably find a way to make this change the pitch depending on the time
synthFunc synthNoise(UNUSED float time){
	return (Uint16)(rand());
}

synthFunc synthSaw(float time){
	return (Uint16)(OFFSET*2 - ((time/PI2)*OFFSET*2));
}

synthFunc synthTriangle(float time){
	return (Uint16)((time < PI ? ((time/PI2)*OFFSET*2) : (OFFSET*2 - (time/PI2)) ));
}
