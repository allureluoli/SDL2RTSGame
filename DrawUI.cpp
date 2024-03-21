#include <iostream>
#include <SDL.h>
#include "main.h"

// 先画菜单的UI
bool DrawUI(SDL_Renderer* renderer)
{
    //std::tie(gPNGSurface, renderer) = loadSurface( "res/image/loaded.png" );


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // 设置为白色

    // 外框
    SDL_RenderDrawLine(renderer, 20, 25, 300, 25);  // 从(20, 20)到(500, 20)画一条线
    SDL_RenderDrawLine(renderer, 20, 25, 20, 400);
    SDL_RenderDrawLine(renderer, 300, 25, 300, 370);
    SDL_RenderDrawLine(renderer, 20, 400, 270, 400);
    SDL_RenderDrawLine(renderer, 300, 370, 270, 400);

    // 上部小框
    SDL_RenderDrawLine(renderer, 25, 30, 295, 30); // 左上角 - 右上角
    SDL_RenderDrawLine(renderer, 25, 30, 25, 100); // 左上角 左下角
    SDL_RenderDrawLine(renderer, 25, 100, 295, 100); //
    SDL_RenderDrawLine(renderer, 295, 30, 295, 100); //右上角 - 右下角

    // 输入框
    SDL_RenderDrawLine(renderer, 25, 115, 255, 115);
    SDL_RenderDrawLine(renderer, 25, 115, 25, 140);
    SDL_RenderDrawLine(renderer, 25, 140, 255, 140);
    SDL_RenderDrawLine(renderer, 255, 115, 255, 140);

    SDL_Rect srcrect = {0, 0, 1920, 1080};

}
