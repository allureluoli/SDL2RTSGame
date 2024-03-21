#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include "main.h"
SDL_Renderer* renderer;
SDL_Window* gWindow;
TTF_Font* font;

// 音频初始化
int sound_init()
{

   #define TMP_FREQ  MIX_DEFAULT_FREQUENCY

   #define TMP_FORMAT   MIX_DEFAULT_FORMAT

   #define TMP_CHAN 2

   #define TMP_CHUNK_SIZE 512

  return Mix_OpenAudio(TMP_FREQ,TMP_FORMAT,TMP_CHAN,TMP_CHUNK_SIZE);

}

// 因为这些是第三方库，所以需要再次 include

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )// 初始化全部系统
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
        std::cout << "成功初始化所有内容\n" <<std::endl;


		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
        // SDL_WINDOW_FULLSCREEN
        // SDL_WINDOW_SHOW 原常量

        renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);


		if( gWindow == NULL ) // 判断一下窗口返回值是不是Null
		{
			std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
			success = false;// 初始化失败
		}
		else
		{

		    std::cout << "Window can be created!\n" << std::endl;

			int imgFlags = IMG_INIT_PNG;
			//将IMG_Init的返回值与imgFlags进行按位与操作。
			//检查初始化是否包含了imgFlags所代表的标志位。如果包含了，结果值将等于imgFlags；否则将不等于imgFlags。
			if( !( IMG_Init( imgFlags ) & imgFlags ) )

			{
				std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				success = false;
			}
			else
			{
                    std::cout << "SDL_image 初始化成功 \n" << IMG_GetError() << std::endl;
			}

             // 音频初始化
            if (sound_init() == 0){
                 std::cout << "SDL_mixer 初始化成功 \n" << std::endl;
            }else{
                 std::cout << "SDL_mixer 初始化成功 \n" << IMG_GetError() << std::endl;
            }


            // 字体初始化
            if (TTF_Init() == 0){
                 font = TTF_OpenFont("res/font/milknolri-rp4zo.ttf", 24); //加载字体
                 std::cout << "SDL_ttf 初始化成功 \n"  << std::endl;
            }else{
                 std::cout << "SDL_ttf 初始化失败 \n" << IMG_GetError() << std::endl;
            }






		}
	}

	return success;
}
