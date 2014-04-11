#include "stdafx.h"

typedef unsigned char BYTE;

#define WIDTH 800
#define HEIGHT 600

#define BUFLEN WIDTH*HEIGHT*2 

#define FF_QUIT_EVENT  (SDL_USEREVENT + 2)

SDL_Surface *screen;

BYTE buf[BUFLEN];


int thread1( void* data )
{
	while(1)
	{
       int arg = *(int*)data;
       printf( "arg: %d \n", arg );

       SDL_Overlay *yuv_overlay = SDL_CreateYUVOverlay(WIDTH/2, HEIGHT/2, SDL_YUY2_OVERLAY, screen);

       if (yuv_overlay == NULL ) 
      {
             fprintf(stderr,"SDL: Couldn't create SDL_yuv_overlay: %sn",SDL_GetError());
             return 0;
      }

     #if 0

      if (SDL_MUSTLOCK(screen2)) {
            SDL_UnlockSurface(screen2);
      }
     #endif

    if (SDL_LockYUVOverlay(yuv_overlay) < 0)
    return 0;

    //copy data to overlay
    //memcpy( yuv_overlay->pixels[0], buf, BUFLEN/4 );
    if ( 1 == arg ){
            memset( yuv_overlay->pixels[0], 0, BUFLEN/4 );
     }else if( 2 == arg ){
            memset( yuv_overlay->pixels[0], 80, BUFLEN/4 );
     }else if( 3 == arg ){
            memset( yuv_overlay->pixels[0], 160, BUFLEN/4 );
     }else if( 4 == arg ){
            memset( yuv_overlay->pixels[0], 240, BUFLEN/4 );
     }
	 
     #if 0

     if (SDL_MUSTLOCK(screen)) {  
          SDL_UnlockSurface(screen);
     }
     #endif
     SDL_UnlockYUVOverlay(yuv_overlay);

     SDL_Rect rect;
     if ( 1 == arg ){
          rect.x = 0;
          rect.y = 0;
          rect.w = WIDTH/2;
          rect.h = HEIGHT/2;
     }else if ( 2 == arg ){
          rect.x = WIDTH/2;
          rect.y = 0;
          rect.w = WIDTH/2;
          rect.h = HEIGHT/2;
	 }else if( 3 == arg){
		  rect.x = 0;
          rect.y = HEIGHT/2;
          rect.w = WIDTH/2;
          rect.h = HEIGHT/2;
	 }else if( 4 == arg){
		  rect.x = WIDTH/2;
          rect.y = HEIGHT/2;
          rect.w = WIDTH/2;
          rect.h = HEIGHT/2;
	 }

	 for(int i = 0; i<100; i++)
	 {
		SDL_DisplayYUVOverlay(yuv_overlay, &rect);
        SDL_Delay( 30 );
	 }
	}
     return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SDL_Event event;

memset( buf, 255, BUFLEN );

//SDL_Thread t1,t2;
//Uint32 t1,t2;

printf( "sdl beginn" );
//XInitThreads();
SDL_Init(SDL_INIT_VIDEO);

atexit(SDL_Quit);

putenv( "SDL_VIDEO_WINDOW_POS = 0,0" );
screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_HWSURFACE | SDL_ASYNCBLIT);

for(int i = 1; i < 5; i++)   //创建4个线程
{
	int arg = i;
	SDL_CreateThread( thread1, (void*)&arg );
	SDL_Delay(1);
}

for(;;)
{
	SDL_WaitEvent(&event);
	switch(event.type)
	{
	case FF_QUIT_EVENT:
	case SDL_QUIT:
		SDL_Quit();
		exit(0);
		break;
	default:
		break;
	}
}

int status;
//SDL_WaitThread( t1, &status );
//SDL_WaitThread( t2, &status );

return 0;
}