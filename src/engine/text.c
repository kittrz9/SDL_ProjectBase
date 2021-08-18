#include "text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"

TTF_Font* font;

char* formatStr;

// Should probably optimize this or something
void drawText(char* str, SDL_Color col, int x, int y, float scaling){
	// This is probably what's making this really inneficient
	// There's probably a better way to draw text than just constantly creating surfaces and textures every frame
	// But I'm too stupid to figure this out
	// Maybe just having a big font texture and just SDL_BlitSurface
	// But I don't want to make a giant texture for just that right now
	SDL_Surface* surface = TTF_RenderText_Solid(font, str, col);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_Rect rect;
	TTF_SizeText(font, str, &rect.w, &rect.h);
	rect.w *= scaling;
	rect.h *= scaling;
	
	rect.x = x;
	rect.y = y;
	
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void drawTextCentered(char* str, SDL_Color col, int x, int y, float scaling){
	SDL_Surface* surface = TTF_RenderText_Solid(font, str, col);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_Rect rect;
	TTF_SizeText(font, str, &rect.w, &rect.h);
	rect.w *= scaling;
	rect.h *= scaling;
	
	rect.x = x - rect.w/2;
	rect.y = y - rect.h/2;
	
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
