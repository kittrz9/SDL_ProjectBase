#include "audio.h"

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "defines.h"

typedef struct {
	Mix_Chunk* chunk;
	bool reserved; // Used so that if you're playing a sound through a Mix_Chunk from like an mp3 file or something it doesn't free the Mix_Chunk
} sound;

// Needed for freeing Mix_Chunks
sound audioChannelChunks[AUDIO_CHANNELS_AMOUNT];

// Callback function for Mix_ChannelFinished 
// I think I finally actually got the memory leak to not be as bad? It still goes up a bit for the first few times the synth is played but then settles at about 13 MB of RAM usage for me
void freeAudioChannelChunk(int channel){
	if(!audioChannelChunks[channel].reserved){
		free(audioChannelChunks[channel].chunk->abuf);
		free(audioChannelChunks[channel].chunk);
	}
	return;
}

// Half of UINT16_MAX so it works
#define OFFSET INT16_MAX

// https://gist.github.com/amirrajan/fa6ce9fdc8918e06ca9759c3358e4cd2
#define envelope (data->instrument->envelope)
bool playSynth(synthData* data){
	// Check if there are any free sound channels
	int freeChannel = -1;
	for(int i = 0; i < AUDIO_CHANNELS_AMOUNT; i++){
		if(Mix_Playing(i) == 0){
			freeChannel = i;
			break;
		}
	}
	if(freeChannel == -1){
		return false;
	}
	
	
	// has to be multiplied by 4 for some reason, I don't fully understand why
	size_t size = (data->length + envelope.release) * MIX_DEFAULT_FREQUENCY*4;
	Uint16* audioBuffer = malloc(size * sizeof(Uint16));
	
	// Having 2 variables with time in their name is probably bad and confusing but I can't think of something better for either of them. funcTime is what gets passed to the synth function
	double funcTime = 0;
	double time = 0.0;
	double freq = data->startFreq, amplitude = 0.0;
	
	for(size_t i = 0; i < size; i++){
		audioBuffer[i] = data->instrument->synth(funcTime) * amplitude * data->volume;
		if(data->endFreq != 0 && time < data->length){
			// Really ugly code, dividing by what the size would be without taking into account release time since I don't want to have the frequency sweep during that time
			freq += (data->endFreq - data->startFreq)/(data->length * MIX_DEFAULT_FREQUENCY*4);
		}
		
		if(time <= envelope.attack){
			amplitude = time/envelope.attack;
		} else if(time <= envelope.attack + envelope.decay){
			amplitude = (((envelope.sustain-1.0)*(time - envelope.attack)))/(envelope.decay) + 1.0;
		} else if(time <= data->length){
			amplitude = envelope.sustain;
		} else {
			amplitude = (((0 - envelope.sustain)/(envelope.release))*(time - data->length)) + envelope.sustain;
		}
		
		// changes the amplitude depending on the panning of the sound
		// calculates it for the next one in the buffer so the left one is for the amplitude of the right ear and the right one is for the amplitude of the left ear lmao
		// also converts the original range of -1 to 1 to 0 to 1 because -1 to 1 is easier to understand when programming the sound
		amplitude *= (i%2==1?1-(data->panning+1)/2 : (data->panning+1)/2);
		
		if(amplitude < 0){
			printf("%f: %f\n", time, amplitude);
			amplitude = 0;
		}
		if(amplitude > 1){
			printf("%f: %f\n", time, amplitude);
			amplitude = 1;
		}
		
		// frequency has to be divided by 2 because of the stereo sound
		// probably will mean this entire thing breaks if I need it to be mono lmao
		funcTime += (freq/2) * (PI2 / MIX_DEFAULT_FREQUENCY);
		if(funcTime >= PI2) { funcTime -= PI2; }
		
		// This feels really really stupid lmao, at least one of these has to be cast to a float so the division doesn't return an int
		time = ((double)i/(double)size)*(data->length + envelope.release);
	}
	
	Mix_Chunk* chunk = malloc(sizeof(Mix_Chunk));
	chunk->allocated = 1;
	chunk->abuf = (Uint8*)audioBuffer;
	chunk->alen = size;
	chunk->volume = 16;
	
	
	Mix_PlayChannel(freeChannel, chunk, 0);
	
	sound s = {
		.chunk = chunk,
		.reserved = false,
	};
	audioChannelChunks[freeChannel] = s;
	
	return true;
}

Uint16 synthSine(float time){
	return (Uint16)((OFFSET * sin(time)) + OFFSET);
}

Uint16 synthSquare(float time){
	return (Uint16)(time < PI ? 0 : OFFSET*2);
}

// Should probably find a way to make this change the pitch depending on the time, probably with like frequency modulation
Uint16 synthNoise(UNUSED float time){
	return (Uint16)(rand());
}

Uint16 synthSaw(float time){
	return (Uint16)(OFFSET*2 - ((time/PI)*OFFSET));
}

Uint16 synthTriangle(float time){
	return (Uint16)((time < PI ? ((time/PI)*OFFSET*2) : ((OFFSET*2) - ((time/PI)*OFFSET*2)) ));
}
