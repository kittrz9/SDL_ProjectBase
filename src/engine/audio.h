#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "types.h"
#include "sounds.h"

#define AUDIO_CHANNELS_AMOUNT 8

// Loading from SDL_RWops in case I want to like read from something in RAM or something from like uncompressing something idk
// Should probably just use audio synthesis or something instead of samples so it's easier to do stuff like pitch them and manipulate the audio or whatever
//void loadSound(enum SOUND_ID sound, SDL_RWops* rw);
void playSound(enum SOUND_ID sound, int loops);
void freeAudioChannelChunk(int channel);

// Returns the value of the synth at the time provided (like sine(pi) would be 0)
// Compiler gives a bunch of warnings because of this function pointer typedef that I can't figure out how to fix
typedef Uint16 (*synthFunc)(float);

// There's probably a better solution to this but I feel like having this struct makes it easier to have a sort of sequencer if I ever add that eventually, since I could just have a file be all of the elements of the data struct to make the song or whatever
// Though would probably be really inefficient to recalculate every like waveform or whatever for every note so idk
typedef struct {
	float startFreq, endFreq; // Should probably make it so that if endFreq is like 0 or something it would just not do the sweep t hing
	float length; // Length of the sound in seconds
	Uint8 volume;
	// decay sustain and release are unused for now since I haven't gotten around to making them work yet
	// attack is like 0 through 1.0 where if you put 1.0 it goes for the whole sample/sound, though you could put higher values but it will end up lower volume than the input volume so like why would you do that when you could just change the volume in the data struct itself
	float attack, decay, sustain, release;
} synthData;

Mix_Chunk* createSound(synthFunc synth, synthData* data);
// Should probably make a way to make a sound from a sample instead of using only synths
// Something like "Mix_chunk* createSoundFromSample(Uint16* sample, synthData)" would probably work but would probably be better to just have them both be the same function and have it all just be determined by the synthData struct


// Should probably use like a wave table or something so you don't need to calculate the entire wave every time you play the sound
synthFunc synthSine(float time);
synthFunc synthSquare(float time);
synthFunc synthNoise(UNUSED float time);
synthFunc synthSaw(float time);
synthFunc synthTriangle(float time);

// Could probably have music be played using samples but idk
// I'd have to either seperate the sound and music channels or increase the number of channels
// I'd probably also need to make either my own sort of file format or like sequencer unless I somehow find a way to just use MIDI lmao

#endif
