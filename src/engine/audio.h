#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

#define AUDIO_CHANNELS_AMOUNT 8

enum SOUND_ID{ SOUND_TEST, SOUNDS_LENGTH };

extern Mix_Chunk* sounds[SOUNDS_LENGTH];

// Loading from SDL_RWops in case I want to like read from something in RAM or something from like uncompressing something idk
// Should probably just use audio synthesis or something instead of samples so it's easier to do stuff like pitch them and manipulate the audio or whatever
void loadSound(enum SOUND_ID sound, SDL_RWops* rw);
void playSound(enum SOUND_ID sound, int loops);

Mix_Chunk* sineWaveSound(float freq, float length);
Mix_Chunk* squareWaveSound(float freq, float length);

// Could probably have music be played using samples but idk
// I'd have to either seperate the sound and music channels or increase the number of channels
// I'd probably also need to make either a proprietary sort of file format or like sequencer unless I somehow find a way to just use MIDI lmao


#endif
