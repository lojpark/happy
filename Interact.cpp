#include "stdafx.h"

void Interact(Background *back, Player *player, Object *object, Gage *gage, Fever *fever, Sound *sound){
	int i=0, j=0;
	int score = atoi((*player).score);

	// ���̵� ����
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

	// ������ ����
	if((*gage).point < (*gage).dest && (*gage).point>0){
		(*gage).point++;
	}else if((*gage).point > (*gage).dest){
		(*gage).point--;
	}

	// ���̵��� ���� ������ ����
	(*gage).time ++;
	if( (*gage).time >= (*gage).difficulty && (*player).dietime == 0){
		if( (*gage).point > 0 ){
			// �������� �ʹ� ������ �ణ ���̵� ����
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

	// �ǹ� ��
	if((*player).fever && ((*gage).dest<1000 || (*player).y<-5000)){
		(*back).flash = 20;
		(*player).fever = false;
		(*player).scrollY = (*player).scrollSY = 0;
		(*player).y = 440;
		(*player).jump = false;
		// �ǹ� �� �ߵ�
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

	// ���� �� �ð� üũ
	if((*player).dietime>0){
		(*player).dietime++;
		// �ߵ���
		if((*gage).point<=0){
			if((*player).dietime>=1000){
				(*player).scrollSY -= 0.005;
				if((*player).scrollSY <= -1.5) (*player).scrollSY = -1.5;
				(*player).scrollY += (*player).scrollSY;
			}
		}
	}

	for(i=1;i<=(*object).n;i++){
		// ��ü�� �ʹ� �ָ� �������� �����
		if( (*object).o[i].x - (*player).x + 400 < -3000 || 3000 < (*object).o[i].x - (*player).x + 400 ){
			for(j=i;j<(*object).n;j++){
				(*object).o[j] = (*object).o[j+1];
			}
			(*object).n--;
			(*object).PushObject(&(*player).x,&(*player).scrollY);
			continue;
		}
		// ��
		if((*object).o[i].type==0){
			// �浹
			if(collisionA((*player).x,(*player).y,100,120,(*object).o[i].x,(*object).o[i].y)){
				// �� �Ҹ�
				if((*gage).point>=250)
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[0],0,&(*sound).g_Channel[0]);
				// �� �Ҹ�
				else
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[3],0,&(*sound).g_Channel[0]);

				// �ǹ� ��
				if((*object).o[i].oy<=0){
					// �����ؼ� ������ �߰� ����
					if((*object).o[i].oy!=(*object).o[i-1].oy-150){
						(*player).AddScore(1);
					}
					// �� �����
					for(j=i;j<(*object).n;j++){
						(*object).o[j] = (*object).o[j+1];
					}
					(*object).n--;
					// ������ ����
					(*gage).dest+=10;
					// ����
					(*player).AddScore(1);
				}
				// �Ϲ� ��
				else{
					// �� �����
					for(j=i;j<(*object).n;j++){
						(*object).o[j] = (*object).o[j+1];
					}
					(*object).n--;
					// �� ��ü ����
					(*object).PushObject(&(*player).x,&(*player).scrollY);
					// �������� Ȱ��ȭ
					(*player).jump = false;
					if((*player).djump){ // ���������� ���� ������ ���� �ι�
						(*gage).dest+=30;
						(*player).AddScore(3);
					}
					(*player).djump = true;
					// ���� �� ������
					(*gage).dest+=30;
					(*player).AddScore(3);
					// �ǹ�
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
		// ���
		if((*object).o[i].type==1){
			// �浹
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
		// ��
		if((*object).o[i].type==2){
			if( -100 <= (*object).o[i].x - (*player).x + 400 && (*object).o[i].x - (*player).x + 400 <= 900 && (*object).o[i].sound == false){
				// �� �Ҹ�
				if((*gage).point>=250)
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[2],0,&(*sound).g_Channel[0]);
				// �� �Ҹ�
				else
					FMOD_System_PlaySound((*sound).g_System,FMOD_CHANNEL_FREE,(*sound).g_Effect[4],0,&(*sound).g_Channel[0]);
				(*object).o[i].sound = true;
			}
			// �浹
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