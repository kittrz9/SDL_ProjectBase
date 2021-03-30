#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

#include "types.h"

#define AUDIO_CHANNELS_AMOUNT 8

// Should probably move this enum to like something in the game directory or whatever
enum SOUND_ID{ SOUND_TEST, SOUNDS_LENGTH };

extern Mix_Chunk* sounds[SOUNDS_LENGTH];

// Loading from SDL_RWops in case I want to like read from something in RAM or something from like uncompressing something idk
// Should probably just use audio synthesis or something instead of samples so it's easier to do stuff like pitch them and manipulate the audio or whatever
void loadSound(enum SOUND_ID sound, SDL_RWops* rw);
void playSound(enum SOUND_ID sound, int loops);

// Returns the value of the synth at the time provided (like sine(pi) would be 0)
// Compiler gives a bunch of warnings because of this function pointer typedef that I can't figure out how to fix
typedef Uint16 (*synthFunc)(float);

Mix_Chunk* createSound(float freq, float length, synthFunc synth);
synthFunc synthSine(float time);
synthFunc synthSquare(float time);
synthFunc synthNoise(UNUSED float time);
synthFunc synthSaw(float time);
synthFunc synthTriangle(float time);

// Could probably have music be played using samples but idk
// I'd have to either seperate the sound and music channels or increase the number of channels
// I'd probably also need to make either my own sort of file format or like sequencer unless I somehow find a way to just use MIDI lmao


#endif
