#include "animation.h"



void setAnimation(animationStruct* anim, animationFrame* frames, Uint16 length){
	anim->frames = frames;
	anim->length = length;
	anim->index = 0;
	anim->timer = 0.0f;
}

void updateAnimation(animationStruct* anim, double deltaTime){
#define currentFrame anim->frames[anim->index]
	if(currentFrame.delay <= 0.0f){
		return;
	}
	
	anim->timer += deltaTime;
	if(anim->timer >= currentFrame.delay * 1000){
		anim->timer = 0.0f;
		if(anim->index >= anim->length){
			anim->index = 0;
			if(anim->nextAnim != NULL){
				setAnimation(anim, anim->nextAnim, anim->nextAnimLength);
			}
		} else {
			anim->index++;
		}
	}
	
	return;
}
