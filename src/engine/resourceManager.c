#include "resourceManager.h" 

#include <SDL2/SDL_image.h>

#include "renderer.h"

typedef struct {
	char name[30*sizeof(char)];
	resource* resPointer;
} resourceListEntry;

resourceListEntry* resourceList;
unsigned int loadedResources = 0;


void destroyTexture(resource* res){
	SDL_DestroyTexture(res->pointer);
	free(res);
	return;
}

resource* loadTexture(const char* filePath){
	resource* res = malloc(sizeof(resource));
	
	res->type = RES_TYPE_TEXTURE;
	
	SDL_Surface* tempSurface = IMG_Load(filePath);
	res->pointer = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return res;
}

// array of function pointers for destroying and creating resources
void (*resourceDestroyingFunctions[RES_TYPE_ENUM_LENGTH]) (resource* res) = {
	destroyTexture,
};
resource* (*resourceLoadingFunctions[RES_TYPE_ENUM_LENGTH]) (const char* filePath) = {
	loadTexture,
};

void destroyResource(resource* res) {
	for(int i = 0; i < loadedResources; i++){
		if(resourceList[i].resPointer == res){
			(resourceDestroyingFunctions[res->type])(res);
			// to have empty entries in the resource list so you don't have to reallocate the array constantly
			resourceList[i].resPointer = NULL;
			return;
		}
	}
	
	printf("could not find resource %p in resource list to destroy\n", (void*)res);
	
	return;
}

resource* loadResource(RESOURCE_TYPE type, const char* filePath){
	int resourceIndex = -1; // used for if an entry in the list can be overwritten
	for(unsigned int i = 0; i < loadedResources; i++){
		if(resourceList[i].resPointer == NULL){
			resourceIndex = i;
			continue;
		}
		if(strcmp(resourceList[i].name, filePath) == 0){
			return resourceList[i].resPointer;
		}
	}
	resource* res = (*resourceLoadingFunctions[type])(filePath);
	if(resourceIndex != -1){
		resourceList[resourceIndex].resPointer = res;
		strcpy(resourceList[resourceIndex].name, filePath);
	} else {
		resourceList = realloc(resourceList, sizeof(resourceListEntry)*(loadedResources+1));
		resourceList[loadedResources].resPointer = res;
		strcpy(resourceList[loadedResources].name, filePath);
		loadedResources++;
	}
	
	return res;
}

