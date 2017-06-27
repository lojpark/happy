#include "stdafx.h"
#define MAX_SPEED_X 3
#define MAX_SPEED_Y 9
#define ACCELATION 0.15
#define FRI_FORCE 0.15

void Object::Set(SDL_Renderer *screen, double *px, double *scrollY){
	this->screen = screen;

	img[0][0] = load_image(screen,"image\\starW.png");
	img[0][1] = load_image(screen,"image\\roseW.png");
	img[0][2] = load_image(screen,"image\\beeW.png");
	img[0][3] = load_image(screen,"image\\stoneW.png");
	img[1][0] = load_image(screen,"image\\starB.png");
	img[1][1] = load_image(screen,"image\\roseB.png");
	img[1][2] = load_image(screen,"image\\beeB.png");
	img[1][3] = load_image(screen,"image\\stoneB.png");

	difficulty = 80;

	int i=0;
	n = 0;
	for(i=1;i<=20;i++){
		PushObject(px, scrollY);
	}
}

void Object::PushObject(double *px, double *scrollY){
	int i=0, j=0;

	n++;
	while(1){
		o[n].x = (*px);
		o[n].Set(screen, px, scrollY, difficulty);
		// 중복 체크
		for(i=1;i<n;i++){
			// 별 근처에 별이 있다면 다시 생성
			if(o[n].type==0){
				if(collisionB(o[n].x,170,o[i].x,170) && o[i].type==0){
					i=-1;
					break;
				}
			}
			// 물체 근처에 물체가 있다면 다시 생성
			else{
				if(collisionB(o[n].x,170,o[i].x,170) && o[i].type!=0){
					i=-1;
					break;
				}
			}
		}
		if(i!=-1) break;
	}

	// 공중 별
	if(o[n].type==0){
		for(i=1;i<n;i++){
			if(abs(o[n].x-o[i].x)<250 && o[i].type==0){
				if(rand()%2){
					o[n].y = 250;
					o[n].oy = 250;
				}
				else{
					o[n].y = 325;
					o[n].oy = 325;
				}
			}
		}
	}
}

void Object::PushStar(double *px, double *scrollY){
	int i=0, j=0;

	n++;
	o[n].x = (*px);
	o[n].SetStar(screen, px, scrollY, 0);

	for(i=-150;i>=-6000;i-=150){
		n++;
		o[n].x = o[n-1].x;
		o[n].SetStar(screen, px, scrollY, i);
	}
}

void Object::Motion(){
	int i=0;
	for(i=1;i<=n;i++){
		o[i].Motion();
	}
}

void Object::Print(){
	int i;
	for(i=1;i<=n;i++){
		if(opacity!=0) SDL_SetTextureAlphaMod(img[0][o[i].type], 255-(opacity));
		o[i].Print(img[0][o[i].type]);
		if(opacity!=0){
			SDL_SetTextureAlphaMod(img[1][o[i].type],opacity);
			o[i].Print(img[1][o[i].type]);
		}
	}
}