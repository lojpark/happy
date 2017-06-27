#include "stdafx.h"
#define MAX_SPEED 3.0
#define ACCELATION 0.15
#define FRI_FORCE 0.12

void Player::Set(SDL_Renderer *screen){
	img = load_image(screen,"image\\char.png");
	x = y = 0;
}

void Player::Get(){
	state[UP] = state[DOWN] = state[LEFT] = state[RIGHT] = false;
	if(GetKeyState(VK_UP) < 0){
		state[UP] = true;
	}
	if(GetKeyState(VK_DOWN) < 0){
		state[DOWN] = true;
	}
	if(GetKeyState(VK_LEFT) < 0){
		state[LEFT] = true;
	}
	if(GetKeyState(VK_RIGHT) < 0){
		state[RIGHT] = true;
	}
}

void Player::Move(){
	if(sy<0){
		sy+=FRI_FORCE;
	}
	else if(sy>0){
		sy-=FRI_FORCE;
	}
	if(sx<0){
		sx+=FRI_FORCE;
	}
	else if(sx>0){
		sx-=FRI_FORCE;
	}

	if(sy>-0.01 && sy<0.01) sy = 0;
	if(sx>-0.01 && sx<0.01) sx = 0;

	if(state[UP]){
		ay-=ACCELATION;
	}
	if(state[DOWN]){
		ay+=ACCELATION;
	}
	if(state[LEFT]){
		ax-=ACCELATION;
	}
	if(state[RIGHT]){
		ax+=ACCELATION;
	}

	sx += ax;
	sy += ay;
	
	if(sy>MAX_SPEED){
		sy = MAX_SPEED;
		ay = 0;
	}
	if(sy<-MAX_SPEED){
		sy = -MAX_SPEED;
		ay = 0;
	}
	if(sx>MAX_SPEED){
		sx = MAX_SPEED;
		ax = 0;
	}
	if(sx<-MAX_SPEED){
		sx = -MAX_SPEED;
		ax = 0;
	}

	x += sx;
	y += sy;
}

void Player::Print(SDL_Renderer *screen){
	apply_surface(x, y, img, screen, 1.0, 0.0, false, true);
}