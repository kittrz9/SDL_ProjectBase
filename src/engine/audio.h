#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#define AUDIO_CHANNELS_AMOUNT 8

enum SOUND_ID{ SOUND_TEST, SOUNDS_LENGTH };

extern Mix_Chunk* sounds[SOUNDS_LENGTH];

// Loading from SDL_RWops in case I want to like read from something in RAM or something from like uncompressing something idk
void loadSound(enum SOUND_ID sound, SDL_RWops* rw);
void playSound(enum SOUND_ID sound, int channel, int loops);

#endif
