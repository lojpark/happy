#include "stdafx.h"

/*����*/
SDL_Window *window;
SDL_Renderer *screen;
SDL_Event event;

Background back;
Player player;

int main(int argc, char *argv[]) 
{
	bool quit = false;
	Uint32 curTicks = SDL_GetTicks();

	ShowWindow( GetConsoleWindow(), SW_HIDE );

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Happy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
	screen = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
	back.Set(screen);
	player.Set(screen);

	while(!quit){
		curTicks += Set_Frame(curTicks);

		// Ű �Է�
		player.Get();

		// ����
		player.Move();

		// ���
		back.Print(screen);
		player.Print(screen);
		SDL_RenderPresent(screen);

		// ���α׷��� �̺�Ʈ�� ���� ��
		if( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT ){
				quit = true;
			}
		}
	}

	SDL_Quit();
	return 0;
}