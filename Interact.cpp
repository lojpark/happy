#include "stdafx.h"

void Interact(Background *back, Player *player, Object *object, Gage *gage, Fever *fever, Sound *sound){
	int i=0, j=0;
	int score = atoi((*player).score);

	// 난이도 증가
	if(score != 0){
		if(score>=300){
			(*gage).difficulty = 3;
			(*object).difficulty = 30;
		}
		else if(score>=270){
			(*gage).difficulty = 3;
			(*object).difficulty = 35;
		}
		else if(score>=240){
			(*gage).difficulty = 3;
			(*object).difficulty = 40;
		}
		else if(score>=210){
			(*gage).difficulty = 3;
			(*object).difficulty = 45;
		}
		else if(score>=180){
			(*gage).difficulty = 4;
			(*object).difficulty = 50;
		}
		else if(score>=150){
			(*gage).difficulty = 5;
			(*object).difficulty = 55;
		}
		else if(score>=120){
			(*gage).difficulty = 6;
			(*object).difficulty = 60;
		}
		else if(score>=90){
			(*gage).difficulty = 7;
			(*object).difficulty = 65;
		}
		else if(score>=60){
			(*gage).difficulty = 8;
			(*object).difficulty = 70;
		}
		else if(score>=30){
			(*gage).difficulty = 9;
			(*object).difficulty = 75;
		}
	}

	// 게이지 증가
	if((*gage).point < (*gage).dest && (*gage).point>0){
		(*gage).point++;
	}else if((*gage).point > (*gage).dest){
		(*gage).point--;
	}

	// 난이도에 따라 게이지 감소
	(*gage).time ++;
	if( (*gage).time >= (*gage).difficulty && (*player).dietime == 0){
		if( (*gage).point > 0 ){
			// 게이지가 너무 낮으면 약간 난이도 감소
			if((*gage).point<150 && rand()%10<3){
				(*gage).point++;
				(*gage).dest++;
			}
			(*gage).point--;
			(*gage).dest--;
		}
		(*gage).time = 0;
		if((*gage).point<150){
			(*back).opacity = 255;
			(*object).opacity = 255;
		}
		else if((*gage).point<250){
			(*back).opacity = (Uint8)( (double)(250 - (*gage).point) / 100 * 255 );
			(*object).opacity = (Uint8)( (double)(250 - (*gage).point) / 100 * 255 );
		}
		else{
			(*back).opacity = 0;
			(*object).opacity = 0;
		}
	}

	// 피버 끝
	if((*player).fever && ((*gage).dest<1000 || (*player).y<-5000)){
		(*back).flash = 20;
		(*player).fever = false;
		(*player).scrollY = (*player).scrollSY = 0;
		(*player).y = 440;
		(*player).jump = false;
		// 피버 후 중독
		(*gage).point = 1000;
		(*gage).dest = 750;

		for(i=1;i<=(*object).n;i++){
			if((*object).o[i].oy<=0){
				for(j=i;j<(*object).n;j++){
					(*object).o[j] = (*object).o[j+1];
				}
				(*object).n--;
				i--;
			}
		}
	}

	// 죽은 후 시간 체크
	if((*player).dietime>0){
		(*player).dietime++;
		// 중독사
		if((*gage).point<=0){
			if((*player).dietime>=1000){
				(*player).scrollSY -= 0.005;
				if((*player).scrollSY <= -1.5) (*player).scrollSY = -1.5;
				(*player).scrollY += (*player).scrollSY;
			}
		}
	}

	for(i=1;i<=(*object).n;i++){
		// 물체가 너무 멀리 떨어지면 재생성
		if( (*object).o[i].x - (*player).x + 400 < -3000 || 3000 < (*object).o[i].x - (*player).x + 400 ){
			for(j=i;j<(*object).n;j++){
				(*object).o[j] = (*object).o[j+1];
			}
			(*object).n--;
			(*object).PushObject(&(*player).x,&(*player).scrollY);
			continue;
		}
		// 별
		if((*object).o[i].type==0){
			// 충돌
			if(collisionA((*player).x,(*player).y,100,120,(*object).o[i].x,(*object).o[i].y)){
				// 별 소리
				if((*gage).point>=250)
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[0],0,&(*sound).g_Channel[0]);
				// 약 소리
				else
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[3],0,&(*sound).g_Channel[0]);

				// 피버 별
				if((*object).o[i].oy<=0){
					// 연속해서 먹으면 추가 점수
					if((*object).o[i].oy!=(*object).o[i-1].oy-150){
						(*player).AddScore(1);
					}
					// 별 지우기
					for(j=i;j<(*object).n;j++){
						(*object).o[j] = (*object).o[j+1];
					}
					(*object).n--;
					// 게이지 증가
					(*gage).dest+=10;
					// 점수
					(*player).AddScore(1);
				}
				// 일반 별
				else{
					// 별 지우기
					for(j=i;j<(*object).n;j++){
						(*object).o[j] = (*object).o[j+1];
					}
					(*object).n--;
					// 새 물체 생성
					(*object).PushObject(&(*player).x,&(*player).scrollY);
					// 더블점프 활성화
					(*player).jump = false;
					if((*player).djump){ // 더블점프로 별을 먹으면 점수 두배
						(*gage).dest+=30;
						(*player).AddScore(3);
					}
					(*player).djump = true;
					// 점수 및 게이지
					(*gage).dest+=30;
					(*player).AddScore(3);
					// 피버
					if((*gage).dest>=1000 && !(*player).fever){
						(*gage).dest = 1100;
						(*player).fever = true;
						(*object).PushStar(&(*player).x,&(*player).scrollY);
						(*back).flash = 10;
						(*fever).opacity = 255;
					}
				}
				i--;
				continue;
			}
		}
		// 장미
		if((*object).o[i].type==1){
			// 충돌
			if(collisionA((*player).x,(*player).y,100,120,(*object).o[i].x,(*object).o[i].y)){
				if((*player).dietime==0){
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[1],0,&(*sound).g_Channel[0]);
					(*player).dietype = 1;
					for(j=1;j<=100;j++)
						(*player).SetBlood(0);
					(*player).SetBody();
					if((*player).dietime == 0)
						(*player).dietime = 1;
				}
			}
		}
		// 벌
		if((*object).o[i].type==2){
			if( -100 <= (*object).o[i].x - (*player).x + 400 && (*object).o[i].x - (*player).x + 400 <= 900 && (*object).o[i].sound == false){
				// 벌 소리
				if((*gage).point>=250)
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[2],0,&(*sound).g_Channel[0]);
				// 총 소리
				else
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[4],0,&(*sound).g_Channel[0]);
				(*object).o[i].sound = true;
			}
			// 충돌
			if(collisionA((*object).o[i].x,(*object).o[i].y,60,60,(*player).x,(*player).y)){
				(*player).dietype = 2;

				if((*object).o[i].dir==1 && (*player).bn<100-(*player).dietime/7)
					(*player).SetBlood(1);
				if((*object).o[i].dir==2 && (*player).bn<100-(*player).dietime/7)
					(*player).SetBlood(2);

				(*object).o[i].die = true;
				if((*player).dietime == 0){
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[5],0,&(*sound).g_Channel[0]);
					(*player).dietime = 1;
				}
			}
		}
	}
}