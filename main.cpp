#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>//奇怪

#include "init.h"
#include "media.h"

//Starts up SDL and creates window
bool init();

//Loads media

//Frees media and shuts down SDL
void close();



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;




//此Demo用于实现摄像机画面的问题


void close()
{
	//自由加载的图像
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )// 接受path 返回SDL_Surface* 指针
// 我删除了include <string> 依然能用 string类型
//
{
	//The final optimized image
	// 最终图像
	SDL_Surface* optimizedSurface = NULL;

	//读取在指定路径的图像
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )//经典如果是空的
	{
		std::cout << "Unable to load image %s! SDL_image Error: " << path.c_str() << IMG_GetError() << std::endl;
	}
	else
	{
		//Convert surface to screen format
		//将屏幕转换成图像
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			std::cout << "Unable to optimize image %s! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;
		}

		//Get rid of old loaded surface
		//去除旧屏幕
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	std::cout << "欢迎来到sdl2" << std::endl;
	if( !init() )
	{
		std::cout << "Failed to initialize!\n" << std::endl;
	}
	else
	{
		//Load media
		//加载图像
		if( !loadMedia() )
		{
			std::cout << "Failed to load media!\n" << std::endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			//事件处理
			SDL_Event e;

			//While application is running
			//运行循环
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Apply the PNG image
				//应用图像

				SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL);

				//Update the surface
				//刷新屏幕
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
