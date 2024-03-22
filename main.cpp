#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

#include "main.h"
#include "init.h"
#include "media.h"
#include "drawui.h"

Uint32 frameStart;
Uint32 frameEnd;
int currentFPS;
int seconds;

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
	TTF_Quit();;
}

// 使用路径读取图片的方法
SDL_Texture* loadSurface( std::string path )// 接受path 返回SDL_Surface* 指针
//
{

    // 两个指针变量
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )// 如果 IMG_Load读取失败则返回空 以此抛出错误
	{
		std::cout << "Unable to load image ! SDL_image Error: " << path.c_str() << IMG_GetError() << std::endl;
	}
	else
	{
        SDL_Texture* optimizedSurface;
		//Convert surface to screen format

		//optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        // 使用SDL_ConvertSurface处理

        optimizedSurface = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if( optimizedSurface == NULL )
            {
                std::cout << "Unable to optimize image %s! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;
            }
        else{

            //释放内存
            SDL_FreeSurface(loadedSurface);

            return optimizedSurface;
        }
	}
	return 0;// 寄了哦
}

int pos1, pos2 = 0;
float ddpi, hdpi, vdpi;
bool posmode1,posmode2;

int displayIndex;// 显示器索引，通常为0
SDL_DisplayMode DM;

std::string  text;

int main( int argc, char* args[] )
{

    init();
    displayIndex = 0;
    if (SDL_GetCurrentDisplayMode(displayIndex, &DM) != 0) {
        SDL_Log("无法获取显示模式信息: %s\n", SDL_GetError());
        return 1;
    }

    text = " ";

    if (renderer == NULL) {
    // 处理渲染器创建失败的情况
    std::cout << "渲染器创建失败" <<  SDL_GetError()<<std::endl;
    }

	//Start up SDL and create window
	std::cout << "欢迎来到sdl2" << std::endl;

    PlayMusic(); // 音频播放

		//加载图像
		if( !loadBackground() )
		{
			std::cout << "Failed to load Background!\n" << std::endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			//事件处理
			SDL_Event e;

			//While application is running

			while(!quit)
			{

                frameStart = SDL_GetTicks(); // 记录每帧开始时间

                // 计算并显示游戏运行时间

                seconds = (frameStart / 1000) % 60;

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
				    if(e.type == SDL_TEXTINPUT){
                        if (TextInputFlag){

                            text += e.edit.text;
                        }
				    }
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}else if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            int mouseX = e.button.x;
                            int mouseY = e.button.y;

                            TextInput(mouseX, mouseY);
                            }
                        }
                if (e.key.keysym.sym == SDLK_BACKSPACE && TextInputFlag && !text.empty()) {
                    // 在这里处理按下退格键的逻辑
                    // 例如，删除字符串中的最后一个字符
                    text.pop_back();
                }
				}
                // 那么一共有四个移动模式，向右动，向下动，向左动，向上动
                // pos1是X pos2是Y
				if (pos1 == -DM.w){//证明碰到了最下侧，则需要向上动
                    posmode1=true;
				}
				if (pos1 == 0){// 证明碰到最上侧，需要向下动
                    posmode1=false;
				}
				if (pos2 == -DM.h){// 证明碰到最右侧，需要向左动
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

                SDL_Rect destinationRect = {pos2, pos1, 2000,2000};
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, gPNGSurface, NULL, &destinationRect);


                DrawUI();
                if(seconds%2 != 0 && TextInputFlag){
                    int len = text.size();
                    if (len > 5){
                        len --;
                    }
                    if (len > 10){
                        len --;
                    }
                    if (len > 15){
                        len --;
                    }
                    if (len > 20){
                        len --;
                    }

                    SDL_RenderDrawLine(renderer, 30+len*10, 120, 30+len*10, 136);// 设置默认坐标 然后根据字符长度来判断坐标位置
                }
                InputInText();

                SDL_RenderPresent(renderer);


                frameEnd = SDL_GetTicks();
                int frameTime = frameEnd - frameStart;
                currentFPS = 1000 / frameTime;
                SDL_UpdateWindowSurface(gWindow);

			}

	}

	//Free resources and close SDL
	close();

	return 0;
}
