#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define TARGET_FPS 60

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2test.lib")
#pragma comment(lib,"SDL2_image.lib")

struct Player{
	double x, y; // 좌표
	double sx, sy; // 속도
	double ax, ay; // 가속도
	bool state[4]; // 상태

	enum eState{UP, DOWN, LEFT, RIGHT};

	SDL_Texture *img;

	void Set(SDL_Renderer *screen);
	void Get();
	void Move();
	void Print(SDL_Renderer *screen);
};

struct Background{
	SDL_Texture *img;
	
	void Set(SDL_Renderer *screen);
	void Print(SDL_Renderer *screen);
};

// SDL_Setting
SDL_Texture *load_image(SDL_Renderer *renderer,char *filename);
void apply_surface(int x, int y, SDL_Texture *source, SDL_Renderer *destination, double scale, double angle, bool flip, bool center, SDL_Rect *clip = NULL);
Uint32 Set_Frame(Uint32 curTicks);