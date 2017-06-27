#include "stdafx.h"

void Background::Mountain::Set(SDL_Renderer *screen, double *px, double *scrollY){
	this->screen = screen;
	this->px = px;
	this->scrollY = scrollY;

	imgW = load_image(screen,"image\\mountainW.png");
	imgB = load_image(screen,"image\\mountainB.png");

	x1 = 0;
	x2 = 800;
	check = 0;
}

void Background::Mountain::Print(){
	// 반복 스크롤
	if( x1 - (*px)/20 >= 800) x1 -= 1600;
	else if( x1 - (*px)/20 <= -800) x1 += 1600;
	if( x2 - (*px)/20 >= 800) x2 -= 1600;
	else if( x2 - (*px)/20 <= -800) x2 += 1600;

	if((*opacity)!=0) SDL_SetTextureAlphaMod(imgW,255-(*opacity));
	apply_surface( (int)(x1 - (*px)/20), (int)(400 - (*scrollY)/20), imgW, screen, 1.0, 0.0, false, false);
	apply_surface( (int)(x2 - (*px)/20), (int)(400 - (*scrollY)/20), imgW, screen, 1.0, 0.0, false, false);
	if((*opacity)!=0){
		SDL_SetTextureAlphaMod(imgB,(*opacity));
		apply_surface( (int)(x1 - (*px)/20), (int)(400 - (*scrollY)/20), imgB, screen, 1.0, 0.0, false, false);
		apply_surface( (int)(x2 - (*px)/20), (int)(400 - (*scrollY)/20), imgB, screen, 1.0, 0.0, false, false);
	}
}