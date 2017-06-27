#include "stdafx.h"

void Fever::Set(SDL_Renderer *screen){
	this->screen = screen;

	img = load_image(screen,"image\\fever.png");

	opacity = 0;
	SDL_SetTextureAlphaMod(img,(Uint8)opacity);
}

void Fever::Motion(){
	if(opacity==0) return;
	else{
		opacity-=3;
		if(opacity<0){
			opacity = 0;
			SDL_SetTextureAlphaMod(img,(Uint8)opacity);
		}
	}
}

void Fever::Print(){
	if(opacity>0) SDL_SetTextureAlphaMod(img,(Uint8)opacity);
	apply_surface(400,300,img,screen,1.0,0.0,false,true);
}