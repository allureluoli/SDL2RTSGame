#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "main.h"

//此Demo用于实现摄像机画面的问题


#include "init.h"
#include "media.h"

//Starts up SDL and creates window
bool init();


//The window we'll be rendering to
SDL_Window* gWindow;



//Frees media and shuts down SDL
void close()
{

    SDL_DestroyTexture( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



// 使用路径读取图片的方法
std::pair<SDL_Texture*, SDL_Renderer*> loadSurface( std::string path )// 接受path 返回SDL_Surface* 指针
//
{
    // 两个指针变量

    SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == NULL) {
    // 处理渲染器创建失败的情况
    std::cout << "wwwwww" <<  SDL_GetError()<<std::endl;
    }


	SDL_Texture* optimizedSurface;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );


	if( loadedSurface == NULL )// 如果 IMG_Load读取失败则返回空 以此抛出错误
	{
		std::cout << "Unable to load image ! SDL_image Error: " << path.c_str() << IMG_GetError() << std::endl;
	}
	else
	{
		//Convert surface to screen format

		//optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        // 使用SDL_ConvertSurface处理

        SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if( optimizedSurface == NULL )
            {
                std::cout << "Unable to optimize image %s! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;
            }
        else{


            //释放内存
            SDL_FreeSurface(loadedSurface);

            return std::make_pair(optimizedSurface, renderer);

        }

	}


	return std::make_pair(optimizedSurface, renderer);// 返回 SDL_Texture*类型指针
}

int pos1, pos2 = 0;

bool posmode1,posmode2;


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	std::cout << "欢迎来到sdl2" << std::endl;
    init();
    PlayMusic(); // 音频播放



		//Load media
		//加载图像
		if( !loadBackground() )
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
					if (e.type == SDL_KEYDOWN) {
					//if ( e.key.keysym.sym == SDLK_a){
                           // pos1+=100; 键盘输入
					}
				}
                // 0 > x > -730
                // 0> y > -1300

                // 那么一共有四个移动模式，向右动，向下动，向左动，向上动
                // pos1是X pos2是Y
				if (pos1 == -1300){//证明碰到了最下侧，则需要向上动
                    posmode1=true;
				}
				if (pos1 == 0){// 证明碰到最上侧，需要向下动
                    posmode1=false;
				}
				if (pos2 == -730){// 证明碰到最右侧，需要向左动
                    posmode2=true;
				}
				if (pos2 == 0){// 证明碰到最左侧，需要向右动
                    posmode2=false;
				}
                if (posmode1){
                    pos1++;
                }
                else{
                    pos1--;
                }
                if (posmode2){
                    pos2++;
                }
                else{
                    pos2--;
                }


                // 设置目标矩形，放大1.5倍
                SDL_Rect srcrect = {0, 0, 1920, 1080}; // 调整位置      后两个参数是裁剪图像的像素
                SDL_Rect destinationRect = {pos2, pos1, 2000,2000};
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, gPNGSurface, &srcrect, &destinationRect);
                SDL_RenderPresent(renderer);
				SDL_UpdateWindowSurface( gWindow );


			}

	}

	//Free resources and close SDL
	close();

	return 0;
}
