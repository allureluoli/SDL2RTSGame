#include <iostream>
#include <SDL_image.h>
#include <utility>
#include <tuple>
#include "main.h"
#include "media.h"


//Current displayed PNG image
SDL_Texture* gPNGSurface;
SDL_Renderer* renderer;

bool loadMedia()
{
	//Loading success flag

	bool success = true;


	std::tie(gPNGSurface, renderer) = loadSurface( "res/image/loaded.png" );
	if (renderer == NULL){


        std::cout <<  SDL_GetError()  << std::endl;
	}

	// loadSurface方法加载图像，加载失败就返回空。
	if( gPNGSurface == NULL )
	{
		std::cout <<  "Failed to load PNG image!\n" <<  SDL_GetError() << std::endl;

		success = false;
	}

	return success;// 返回成功
}
