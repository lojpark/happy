#include "stdafx.h"

void Background::Set(SDL_Renderer *screen){
	img = load_image(screen,"image\\background.png");
}

void Background::Print(SDL_Renderer *screen){
	apply_surface(0, 0, img, screen, 1.0, 0.0, false, false);
}