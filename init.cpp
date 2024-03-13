#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "main.h"


// 因为这些是第三方库，所以需要再次 include

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool init()// 初始化方法，测试屏幕和那啥
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) // 判断一下窗口返回值是不是Null
		{
			std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
			success = false;// 也就意味着初始化失败
		}
		else
		{
			//Initialize PNG loading
			//初始化PNG读取
			//IMG_INIT_PNG似乎是一个常量
			int imgFlags = IMG_INIT_PNG;
			//这里使用了按位与运算符&，将IMG_Init的返回值与imgFlags进行按位与操作。
			//这个操作可以用来检查初始化是否包含了imgFlags所代表的标志位。如果包含了，结果值将等于imgFlags；否则将不等于imgFlags。
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
                // 最后将整个值取反
                // 我也不懂为啥要这么写先这样吧
			{
				std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}
	}

	return success;
}
