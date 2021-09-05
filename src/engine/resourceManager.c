#include "resourceManager.h" 

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"

typedef struct {
	//char name[30*sizeof(char)];
	char* name;
	resource* resPointer;
} resourceListEntry;

resourceListEntry* resourceList;
unsigned int loadedResources = 0;


// loaded resource is freed from memory in the destroy resource function
void destroyTexture(resource* res){
	SDL_DestroyTexture(res->pointer);
	
	return;
}

// resource is going to have the type assigned in the load resource function
resource* loadTexture(const char* filePath){
	resource* res = malloc(sizeof(resource));
	
	SDL_Surface* tempSurface = IMG_Load(filePath);
	res->pointer = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	if(res->pointer == NULL) { return NULL; }
	
	return res;
}

void destroyFont(resource* res){
	TTF_CloseFont(res->pointer);
	
	return;
}

resource* loadFont(const char* filePath){
	resource* res = malloc(sizeof(resource));
	
	res->pointer = TT F_OpenFont("res/TerminusTTF-4.47.0.ttf", 24);
	if(res->pointer == NULL) { return NULL; }
	
	return res;
}

// array of function pointers for destroying and creating resources
// has to be in the same order as the enum of resource types
void (*resourceDestroyingFunctions[RES_TYPE_ENUM_LENGTH]) (resource* res) = {
	destroyTexture,
	destroyFont,
};
resource* (*resourceLoadingFunctions[RES_TYPE_ENUM_LENGTH]) (const char* filePath) = {
	loadTexture,
	loadFont,
};

void destroyResource(resource* res) {
	for(unsigned int i = 0; i < loadedResources; i++){
		if(resourceList[i].resPointer == res){
			(resourceDestroyingFunctions[res->type])(res);
			// to have empty entries in the resource list so you don't have to reallocate the array constantly
			resourceList[i].resPointer = NULL;
			free(resourceList[i].name);
			resourceList[i].name = NULL;
			free(res);
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
	res->type = type;
	
	if(res->pointer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open resource with file path %s: %s\n", filePath, SDL_GetError());
		return -1;
	}
	
	if(resourceIndex == -1){
		resourceIndex = loadedResources;
		// loading resources isn't something that happens a lot during the game so it being reallocated shouldn't be too bad and wouldn't really benefit from the fast insertion/deletion with a linked list
		resourceList = realloc(resourceList, sizeof(resourceListEntry)*(loadedResources+1));
		loadedResources++;
	}
	
	resourceList[resourceIndex].resPointer = res;
	resourceList[resourceIndex].name = malloc(strlen(filePath) * sizeof(char));
	strcpy(resourceList[resourceIndex].name, filePath);
	
	return res;
}

void clearResourceList(){
	if(loadedResources < 1){
		printf("no resources loaded\n");
		return;
	}
	
	for(unsigned int i = 0; i < loadedResources; i++){
		if(resourceList[i].resPointer == NULL){
			continue;
		}
		
		(resourceDestroyingFunctions[resourceList[i].resPointer->type])(resourceList[i].resPointer);
		
		free(resourceList[i].name);
	}
	
	free(resourceList);
	
	return;
}
