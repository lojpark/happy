#include "stdafx.h"

void Opening::Set(SDL_Renderer *screen){
	this->screen = screen;

	img[0] = load_image(screen,"image\\1.png");
	img[1] = load_image(screen,"image\\2.png");
	img[2] = load_image(screen,"image\\3.png");
	img[3] = load_image(screen,"image\\2.png");
}

void Opening::Print(int index){
	apply_surface(0, 0, img[index], screen, 1.0, 0.0, false, false);
}