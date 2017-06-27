#include "stdafx.h"

void Gage::Set(SDL_Renderer *screen){
	this->screen = screen;

	imgBar1 = load_image(screen,"image\\gageBar1.png");
	imgBar2 = load_image(screen,"image\\gageBar2.png");
	imgBar3 = load_image(screen,"image\\gageBar3.png");

	point = dest = 750;
	max = 1000;
	difficulty = 10;
	time = 0;
}

void Gage::Print(){
	int i=0;
	SDL_SetTextureColorMod(imgBar1,255,255,255);
	apply_surface(0,0,imgBar2,screen,1.0,0.0,false,false);
	// ¿¬µÎ
	if(point>=755){
		SDL_SetTextureColorMod(imgBar1,0,255,0);
		apply_surface_scale(i,0,imgBar1,screen,(double)point/max,1.0);
	}
	// ¿¬µÎ+³ë¶û
	else if(point>=500){
		SDL_SetTextureColorMod(imgBar1,755-point,255,0);
		apply_surface_scale(i,0,imgBar1,screen,(double)point/max,1.0);
	}
	// ³ë¶û
	else if(point>=450){
		SDL_SetTextureColorMod(imgBar1,255,255,0);
		apply_surface_scale(i,0,imgBar1,screen,(double)point/max,1.0);
	}
	// ³ë¶û+»¡°­
	else if(point>=250){
		SDL_SetTextureColorMod(imgBar1,255,255-(Uint8)((double)(450-point)/200*255),0);
		apply_surface_scale(i,0,imgBar1,screen,(double)point/max,1.0);
	}
	// »¡°­
	else{
		SDL_SetTextureColorMod(imgBar1,255,0,0);
		apply_surface_scale(i,0,imgBar1,screen,(double)point/max,1.0);
	}
	
	apply_surface(0,0,imgBar3,screen,1.0,0.0,false,false);
	/*
	if(point>=500) apply_surface_scale(i,0,imgGreen,screen,(double)point/max,1.0);
	else if(point>=250) apply_surface_scale(i,0,imgYellow,screen,(double)point/max,1.0);
	else apply_surface_scale(i,0,imgRed,screen,(double)point/max,1.0);
	*/
}