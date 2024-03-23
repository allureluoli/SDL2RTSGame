#include <iostream>
#include <SDL_image.h>
#include <utility>
#include <tuple>
#include <SDL_mixer.h>

#include "main.h"
#include "init.h"


//Current displayed PNG image
SDL_Texture* gPNGSurface;


// 加载背景
bool loadBackground()
{
	//Loading success flag

	bool success = true;


	gPNGSurface = loadSurface( "res/image/loaded.png" );
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


// 播放音乐
// 后面改成自动读取文件夹内音乐的
void PlayMusic()
{
    Mix_Music *music = Mix_LoadMUS("res/music/ww.ogg");

    // 加载音乐文件失败
    if (!music) {
        std::cout <<  "音频加载失败" <<   Mix_GetError() << std::endl;
    }
    else{
        std::cout <<  "ww.ogg 读取成功" << std::endl;
    }

    Mix_PlayMusic(music, -1);
}


