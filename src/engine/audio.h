#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "types.h"

#define AUDIO_CHANNELS_AMOUNT 8

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
	// attack decay and release are all in seconds, sustain is between 0 and 1
	// attack decay and release were changed to take seconds because it seemed weird to have the values change with longer notes after thinking about it a bit
	float attack, decay, sustain, release;
} synthData;

void playSynth(synthFunc synth, synthData* data);
// Should probably make a way to make a sound from a sample instead of using only synths
// Something like "Mix_chunk* createSoundFromSample(Uint16* sample, synthData)" would probably work but would probably be better to just have them both be the same function and have it all just be determined by the synthData struct


// Should probably use like a wave table or something so you don't need to calculate the entire wave every time you play the sound
Uint16 synthSine(float time);
Uint16 synthSquare(float time);
Uint16 synthNoise(UNUSED float time);
Uint16 synthSaw(float time);
Uint16 synthTriangle(float time);

// Could probably have music be played using samples but idk
// I'd have to either seperate the sound and music channels or increase the number of channels
// I'd probably also need to make either my own sort of file format or like sequencer unless I somehow find a way to just use MIDI lmao

#endif
