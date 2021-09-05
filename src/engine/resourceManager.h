#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

typedef enum {
	RES_TYPE_TEXTURE,
	RES_TYPE_FONT,
	RES_TYPE_ENUM_LENGTH, // length of enum
} RESOURCE_TYPE;

// should probably somehow make textures their own type or something so it's more readable idk
typedef struct {
	RESOURCE_TYPE type;
	void* pointer; // pointer to the loaded resource after you like load it with IMG_Load or whatever, probably not good for like readability since you'd need to pass the pointer to the rendering function but idk maybe I'll make a rendering function that takes a resource pointer
} resource;

void destroyResource(resource* res);

resource* loadResource(RESOURCE_TYPE type, const char* filePath);

// destroys every loaded resource
void clearResourceList();

#endif
