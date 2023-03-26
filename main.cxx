#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include<iostream>
#include<ctime>
#include <stdlib.h>
#include <stdio.h>
#include<cstring>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

long long i,j;

using namespace std;
// fps
static float fps(){
    static int a=clock();
    a=clock()-a;
    float fps=(float)1000/a;
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
	SDL_Color color = {90, 90, 90};
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

static SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
	SDL_Surface *img = IMG_Load(path);
	if (img == NULL)
	{
		fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
		return NULL;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);
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
	loadText(renderer, "0"),loadText(renderer, "1"),
	loadText(renderer, "2"),loadText(renderer, "3"),
	loadText(renderer, "4"),loadText(renderer, "5"),
	loadText(renderer, "6"),loadText(renderer, "7"),
	loadText(renderer, "8"),loadText(renderer, "9")
	};
	SDL_Texture *textTexture_a = loadText(renderer, ".");
	/*if (textTexture0 == NULL||textTexture1==NULL
	    ||textTexture2 == NULL||textTexture3 == NULL||textTexture4 == NULL||textTexture5 == NULL||textTexture6 == NULL||textTexture7 == NULL||textTexture8 == NULL||textTexture9 == NULL||textTexture_a==NULL)
	{
		fprintf(stderr, "Couldn't load text texture\n");
		return 1;
	}*/
	// img
	SDL_Texture *imageTexture = loadImage(renderer, "a.png");
	if (imageTexture == NULL)
	{
		fprintf(stderr, "Couldn't load image\n");
		return 1;
	}
	int tw, th;
	SDL_QueryTexture(*textTexture, NULL, NULL, &tw, &th);
	//SDL_QueryTexture(textTexture1, NULL, NULL, &tw, &th);
	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_Rect dest;
	SDL_Event ev;
	while(true){
   //test
   
   SDL_MultiGestureEvent Event;
   if (SDL_PollEvent(&ev))
      switch(ev.type){
       // case SDL_MultiGestureEvent:
         case SDL_MULTIGESTURE:
            return 1;
      }
	//clear
	SDL_RenderClear(renderer);
	
	SDL_Rect destImg;
	destImg.w=32;
	destImg.h=32;
	for(i=0;i<=SCREEN_HEIGHT +770 ;i+=32)
	for(j=0;j<=SCREEN_WIDTH +70;j+=32 ){
	 destImg.x=j;
	 destImg.y=i;
  SDL_RenderCopy(renderer, imageTexture, NULL, &destImg);
	}
	// Our text always has width much bigger than height, use this
	dest.x = 0;
	w=20;
	dest.w = w;
	dest.h = th * w / tw;
	//dest.y = (h - dest.h) / 2;
	dest.y=1;
	string num=to_string(fps());
	for(int i=0;i<num.size();i++,dest.x+=22){
	if (num[i]=='.'){
	  SDL_RenderCopy(renderer, textTexture_a, NULL, &dest); 
	  continue;
	  }
	SDL_RenderCopy(renderer, textTexture[num[i]-'0'], NULL, &dest);
	}
	
	SDL_RenderPresent(renderer);
	//SDL_Delay(20);
	//set up fps:
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
