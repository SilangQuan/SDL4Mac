#include <iostream>
#include <SDL2/SDL.h> 
using namespace std;
const int SCREEN_WIDTH = 640;  
const int SCREEN_HEIGHT =360; 
int main()
{
 	//Start SDL  
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	SDL_Surface *bmp = SDL_LoadBMP("a.bmp");
	if (bmp == nullptr)
	{
		cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
		return 1;
	}
	
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
	
	//SDL_Delay(2000);
	getchar();
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
    //Quit SDL  
	SDL_Quit(); 
	
	return 1;
}
