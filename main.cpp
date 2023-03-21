#include <SDL2/SDL.h>
#include<iostream>
#include<ctime>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#include <stdio.h>
#include<cstring>
using namespace std;
// fps
float fps(){
    static int a=clock();
    float fps;
    a=clock()-a;
    fps=(float)6000/a;
    a=clock();
    return fps;
}

// Function for loading font and drawing text into SDL_Texture
static SDL_Texture *loadText(SDL_Renderer *renderer, const char *text)
{
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
		return NULL;
	}
	TTF_Font *font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 256);
	if (font == NULL)
	{
		fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
		return NULL;
	}
	SDL_Color color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (texture == NULL)
	{
		fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		return NULL;
	}
	return texture;
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("Hello SDL2-ttf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return 1;
	}
	// Better scaling quality
 	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	SDL_Texture *textTexture[] = {
	loadText(renderer, "0"),
	loadText(renderer, "1"),
	loadText(renderer, "2"),
	loadText(renderer, "3"),
	loadText(renderer, "4"),
	loadText(renderer, "5"),
	loadText(renderer, "6"),
	loadText(renderer, "7"),
	loadText(renderer, "8"),
	loadText(renderer, "9")
	};
	SDL_Texture *textTexture_a = loadText(renderer, ".");
	/*if (textTexture0 == NULL||textTexture1==NULL
	    ||textTexture2 == NULL||textTexture3 == NULL||textTexture4 == NULL||textTexture5 == NULL||textTexture6 == NULL||textTexture7 == NULL||textTexture8 == NULL||textTexture9 == NULL||textTexture_a==NULL)
	{
		fprintf(stderr, "Couldn't load text texture\n");
		return 1;
	}*/
	int tw, th;
	SDL_QueryTexture(*textTexture, NULL, NULL, &tw, &th);
	//SDL_QueryTexture(textTexture1, NULL, NULL, &tw, &th);
	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_Rect dest;
	int b;
	while(true){
	
	// Our text always has width much bigger than height, use this
	dest.x = 0;
	w=20; // my edit
	dest.w = w;
	dest.h = th * w / tw;
	//dest.y = (h - dest.h) / 2;
	dest.y=1;
	SDL_RenderClear(renderer);
	string num=to_string(fps());
	for(int i=0;i<num.size();i++){
	if (num[i]=='.'){
	  SDL_RenderCopy(renderer, textTexture_a, NULL, &dest);     dest.x+=22;
	  continue;
	  }
	SDL_RenderCopy(renderer, textTexture[num[i]-'0'], NULL, &dest);
	dest.x+=22;
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(800);
	//set up fps:
	fps();
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
