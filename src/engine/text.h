#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define MAX_STR_LEN 256 // This is probably dumb since I can just realloc but whatever
static const SDL_Color SDL_Color_White = {255, 255, 255, 255}; // RGBA format

extern char* formatStr; // This is very dumb

void drawText(char* str, SDL_Color col, int x, int y, float scaling, TTF_Font* font);
void drawTextCentered(char* str, SDL_Color col, int x, int y, float scaling, TTF_Font* font);

#endif
