#include "stdafx.h"

void Background::Cloud::Clouds::Set(SDL_Renderer *screen, double *px, double *scrollY){
	this->screen = screen;
	this->px = px;
	this->scrollY = scrollY;

	type = rand()%2;
	x = rand()%2000-1000;
	y = rand()%300+100;
}

void Background::Cloud::Clouds::Print(SDL_Texture *img){
	// 반복 스크롤
	if( x - (*px)/10 >= 1000){
		type = rand()%2;
		x -= 2000;
		y = rand()%300+100;
	}
	else if( x - (*px)/10 <= -1000){
		type = rand()%2;
		x += 2000;
		y = rand()%300+100;
	}
	// 출력
	apply_surface((int)(x - (*px)/10 + 400), (int)(y - (*scrollY)/10), img, screen, 1.0, 0.0, false, true);
}