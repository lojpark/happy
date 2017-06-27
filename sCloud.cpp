#include "stdafx.h"

void Background::Cloud::Set(SDL_Renderer *screen, double *px, double *scrollY){
	this->screen = screen;

	imgW[0] = load_image(screen,"image\\cloud1W.png");
	imgW[1] = load_image(screen,"image\\cloud2W.png");
	imgB[0] = load_image(screen,"image\\cloud1B.png");
	imgB[1] = load_image(screen,"image\\cloud2B.png");

	n = 5;
	int i=0, j=0;
	for(i=1;i<=n;i++){
		// 중복 체크
		while(1){
			c[i].Set(screen, px, scrollY);
			for(j=1;j<i;j++){
				if(collisionB(c[i].x,150,c[j].x,150)){
					j=-1;
					break;
				}
			}
			if(j!=-1) break;
		}
	}
}

void Background::Cloud::Print(){
	int i=0;
	for(i=1;i<=n;i++){
		c[i].Print(imgW[c[i].type]);
		if(opacity!=0){
			SDL_SetTextureAlphaMod(imgB[c[i].type],(*opacity));
			c[i].Print(imgB[c[i].type]);
		}
	}
}