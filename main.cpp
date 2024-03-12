#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>//奇怪


//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;


//此Demo用于实现摄像机画面的问题

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

bool loadMedia()
{
	//Loading success flag
	//加载成功标志
	bool success = true;

	//加载PNG图像 surface怎么翻译呢
	gPNGSurface = loadSurface( "loaded.png" );
	// loadSurface方法加载图像，加载失败就返回空。
	if( gPNGSurface == NULL )
	{
		std::cout <<  "Failed to load PNG image!\n" << std::endl;
		success = false;
	}

	return success;// 返回成功
}

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
