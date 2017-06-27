#include "stdafx.h"
#define MAX_SPEED_X 3
#define MAX_SPEED_Y 9
#define ACCELATION 0.15
#define FRI_FORCE 0.15

void Object::Objects::Set(SDL_Renderer *screen, double *px, double *scrollY, int difficulty){
	this->screen = screen;
	this->px = px;
	this->scrollY = scrollY;

	// 초기화
	motion = rand()%1000;
	dir = 0;
	sound = false;

	// 물체 종류 랜덤 설정
	type = rand()%4;
	// 난이도에 따라 별 갯수 추가 증가
	if(rand()%100<=difficulty) type=0;
	// 벌 개채수 감소
	if(type==2){
		if(rand()%100<=50) type = rand()%4;
	}

	switch(type){
	// 별
	case 0:
		if(rand()%2==0) x += rand()%3000 + 500;
		else x += (-1*rand()%3000 - 500);
		y = 400;
		break;
	// 장미
	case 1:
		if(rand()%2==0) x += rand()%3000 + 500;
		else x += (-1*rand()%3000 - 500);
		y = 600-60;
		break;
	// 벌
	case 2:
		if(rand()%2==0) x += rand()%3000 + 500;
		else x += (-1*rand()%3000 - 500);
		y = 540;
		break;
	// 돌
	case 3:
		if(rand()%2==0) x += rand()%3000 + 500;
		else x += (-1*rand()%3000 - 500);
		y = 600-50;
		break;
	}

	oy = y;
}

void Object::Objects::SetStar(SDL_Renderer *screen, double *px, double *scrollY, double y){
	this->screen = screen;
	this->px = px;
	this->scrollY = scrollY;

	// 초기화
	motion = rand()%1000;
	dir = 0;

	// 별
	type = 0;
	x += rand()%250-125;
	this->y = y;
	oy = this->y;
}

void Object::Objects::Motion(){
	if(die) return;

	motion ++;
	switch(type){
	// 별
	case 0:
		// 흔들흔들
		y = oy + 15*sin(motion/80) - 15;
		break;
	// 벌
	case 2:
		// 방향 지정
		if(dir==0 && (-25 <= x-(*px)+400 && x-(*px)+400 <= 825) ){
			if(x>(*px)) dir=1;
			if(x<(*px)) dir=2;
		}
		// 움직여
		else if(dir==1){
			x-=4;
		}
		else if(dir==2){
			x+=4;
		}
		// 흔들흔들
		y = oy + 15*sin(motion/50) - 15;
		break;
		break;
	}
}

void Object::Objects::Print(SDL_Texture *img){
	if(die) return;
	if(dir==2) apply_surface((int)(x - (*px) + 400), (int)(y - (*scrollY)), img, screen, 1.0, 0.0, true, true);
	else apply_surface((int)(x - (*px) + 400), (int)(y - (*scrollY)), img, screen, 1.0, 0.0, false, true);
}