#include "audio.h"

#include <SDL2/SDL.h>
#include <types.h>

#if defined(WIN32) || defined(_WIN32)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdlib.h>

// Needed for freeing Mix_Chunks
Mix_Chunk* audioChannelChunks[AUDIO_CHANNELS_AMOUNT];

// Callback function for Mix_ChannelFinished 
void freeAudioChannelChunk(int channel){
	Mix_FreeChunk(audioChannelChunks[channel]);
	return;
}

#define PI  M_PI
#define PI2 PI*2

// Half of UINT16_MAX so it works
#define OFFSET INT16_MAX

// https://gist.github.com/amirrajan/fa6ce9fdc8918e06ca9759c3358e4cd2
void playSynth(synthFunc synth, synthData* data){
	// Has to be multiplied by 16 because the audio format is U16 I think
	size_t size = (data->length + data->release) * MIX_DEFAULT_FREQUENCY*16;
	Uint16* audioBuffer = malloc(size * sizeof(Uint16));

	// Having 2 variables with time in their name is probably bad and confusing but I can't think of something better for either of them. funcTime is what gets passed to the synth function
	double funcTime = 0;
	double time = 0.0;
	double freq = data->startFreq, amplitude = 0.0;
	
	for(size_t i = 0; i < size; i++){
		audioBuffer[i] = synth(funcTime) * amplitude;
		if(time < data->length && data->endFreq != 0){
			freq += (data->endFreq - data->startFreq)/size;
		}
		
		if(time <= data->attack){
			amplitude = time/data->attack;
		} else if(time <= data->attack + data->decay){
			amplitude = (((data->sustain-1.0)*(time - data->attack)))/(data->decay) + 1.0;
		} else if(time <= data->length){
			amplitude = data->sustain;
		} else {
			amplitude = (((0 - data->sustain)/(data->release))*(time - data->length)) + data->sustain;
		}
		
		if(amplitude < 0){
			printf("%f: %f\n", time, amplitude);
			amplitude = 0;
		}
		if(amplitude > 1){
			printf("%f: %f\n", time, amplitude);
			amplitude = 1;
		}
		
		// Frequency also has to be divided by 8 for some reason to get the actual frequency, idk why
		funcTime += freq/8 * PI2 / MIX_DEFAULT_FREQUENCY;
		if(funcTime >= PI2) { funcTime -= PI2; }
		
		// This feels really really stupid lmao
		time = ((float)i/(float)size)*(data->length+data->release);
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
}

Uint16 synthSine(float time){
	return (Uint16)((OFFSET * sin(time)) + OFFSET);
}

Uint16 synthSquare(float time){
	return (Uint16)(time < PI ? 0 : OFFSET*2);
}

// Should probably find a way to make this change the pitch depending on the time
Uint16 synthNoise(UNUSED float time){
	return (Uint16)(rand());
}

// These suddenly just kinda broke after the merge, and changing the PI2 to just PI worked somehow????
Uint16 synthSaw(float time){
	return (Uint16)(OFFSET*2 - ((time/PI)*OFFSET));
}

Uint16 synthTriangle(float time){
	return (Uint16)((time < PI ? ((time/PI)*OFFSET*2) : (OFFSET*2 - (time/PI)) ));
}
