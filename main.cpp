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
SDL_Window* gWindow = NULL;



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
    init();
    SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == NULL) {
    // 处理渲染器创建失败的情况
    std::cout << "wwwwww" <<  SDL_GetError()<<std::endl;
    }


	SDL_Texture* optimizedSurface = NULL;

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
            SDL_FreeSurface( loadedSurface );

            return std::make_pair(optimizedSurface, renderer);

        }

	}


	return std::make_pair(optimizedSurface, renderer);// 返回 SDL_Texture*类型指针
}

int pos1 = 0;
int pos2 = 0;
bool posSetting = false;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	std::cout << "欢迎来到sdl2" << std::endl;



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

				if (pos1 >500){

                    posSetting = true;

				}
				if (pos1 == 0){

                    posSetting = false;
				}

                if (posSetting){
                        pos1--;
                        pos2--;
                }
                else{

                        pos1++;
                        pos2++;
                }


				int textureWidth, textureHeight;
                SDL_QueryTexture(gPNGSurface, NULL, NULL, &textureWidth, &textureHeight);

                // 设置目标矩形，放大两倍
                SDL_Rect destinationRect = {0, 0, textureWidth * 2, textureHeight * 2};
                //SDL_RenderSetClipRect(renderer, &clipRect);
                // 清空渲染目标
                SDL_RenderClear(renderer);

                SDL_Rect srcrect = {pos1/2, pos2/2, 1920, 1080};

                SDL_RenderCopy(renderer, gPNGSurface, &srcrect, &destinationRect);
                SDL_RenderPresent(renderer);
				SDL_UpdateWindowSurface( gWindow );
			}

	}

	//Free resources and close SDL
	close();

	return 0;
}
