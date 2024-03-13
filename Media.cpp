#include <iostream>
#include <SDL_image.h>

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL; //

bool loadMedia()
{
	//Loading success flag
	//加载成功标志
	bool success = true;

	//加载PNG图像 surface怎么翻译呢
	gPNGSurface = loadSurface( "res/image/loaded.png" );
	// loadSurface方法加载图像，加载失败就返回空。
	if( gPNGSurface == NULL )
	{
		std::cout <<  "Failed to load PNG image!\n" << std::endl;
		success = false;
	}

	return success;// 返回成功
}
