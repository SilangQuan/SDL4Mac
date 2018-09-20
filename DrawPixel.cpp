#include <iostream>
#include <SDL2/SDL.h>  

using namespace std;

const int SCREEN_WIDTH = 640;  
const int SCREEN_HEIGHT =360; 

struct RenderContext
{
	int width;		
	int height;		
	int bpp;		
	uint* backBuffer; 
};

 
/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void Sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}
 
void Quit( int code )  
{  
    SDL_Quit( );  
    /* Exit program. */  
    exit( code );  
}  
 
void CheckSDLError(int line = -1)
{
#ifndef NDEBUG
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
                printf("SDL Error: %s\n", error);
                if (line != -1)
                        printf(" + line: %i\n", line);
                SDL_ClearError();
        }
#endif
}


void HandleKeyEvent( SDL_Keysym* keysym )  
{  
    switch( keysym->sym )  
    {  
    case SDLK_ESCAPE:  
        Quit( 0 );  
        break;  
    case SDLK_SPACE:  
     cout<<"Space"<<endl;
        break;  
    default:  
        break;  
    }  
} 
 
void HandleEvents()  
{  
    // Our SDL event placeholder.  
    SDL_Event event;  
    //Grab all the events off the queue.  
    while( SDL_PollEvent( &event ) ) {  
        switch( event.type ) {  
        case SDL_KEYDOWN:  
            // Handle key Event  
            HandleKeyEvent( &event.key.keysym );  
            break;  
        case SDL_QUIT:  
            // Handle Quit requests (like Ctrl-c).  
            Quit( 0 );  
            break;  
        }  
    }  
} 

 
/* Our program's entry point */
int main(int argc, char *argv[])
{
    SDL_Window *mainwindow;
	SDL_Renderer *renderer;
	SDL_Texture* mainRt;

    int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;

	SDL_RendererInfo info;
    int r = SDL_GetNumRenderDrivers();
	int i=0;
    while ( i < r )
    {
		if ( SDL_GetRenderDriverInfo(i,&info) == 0 )
		{
			printf("Driver %s\n",info.name);
		}
		i++;
	}
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		Sdldie("Unable to initialize SDL"); //Or die on error
											
	// Create our window centered at width*height resolution 
	mainwindow = SDL_CreateWindow("Draw Pixel", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	CheckSDLError(__LINE__);
	// Die if creation failed
	if (mainwindow == nullptr) 
	{
		Sdldie("Unable to create window");
	}
	
	renderer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	CheckSDLError(__LINE__);
	if (renderer == nullptr) {
		Sdldie("Unable to create renderer");
	}

	mainRt = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);

	CheckSDLError(__LINE__);


    RenderContext* renderContext = new RenderContext();
	renderContext->width = screenWidth;
	renderContext->height = screenHeight;
	renderContext->bpp = sizeof(uint);
	renderContext->backBuffer = new uint[screenWidth * screenHeight];
    int pixelPosX =100;
    int pixelPosY = 100;
	renderContext->backBuffer[pixelPosX + pixelPosY* renderContext->width] = (255 << 24) | (255 << 16) | (0 << 8) | (0 << 0);

    void* pixels;
	int pitch;

	SDL_LockTexture(mainRt, NULL, &pixels, &pitch);

	//Copy loaded/formatted surface pixels
	memcpy(pixels, renderContext->backBuffer, pitch * screenHeight);

	//Unlock texture to update
	SDL_UnlockTexture(mainRt);

	SDL_RenderCopy(renderer, mainRt, NULL, NULL);
	SDL_RenderPresent(renderer);

    getchar();
    delete renderContext;
	SDL_DestroyTexture(mainRt);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainwindow);
 
    return 0;
}
