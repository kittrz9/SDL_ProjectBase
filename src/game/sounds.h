#ifndef SOUNDS_H
#define SOUNDS_H

// Enum for all the sounds used (SOUNDS_LENGTH is just there so it's easier to get how many sounds are in the enum)
enum SOUND_ID{ SOUND_TEST, SOUNDS_LENGTH };

extern Mix_Chunk* sounds[SOUNDS_LENGTH];

#endif
