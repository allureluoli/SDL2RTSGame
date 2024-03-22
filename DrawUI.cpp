#include <iostream>
#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "main.h"
#include "init.h"

SDL_Texture* UI;
SDL_Rect destinationRect;

SDL_Color textColor = {255, 255, 255};

SDL_Surface* textSurface;
SDL_Texture* textTexture;


// 先画菜单的UI
void DrawUI()
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

    destinationRect = {53, 78, 27, 13};
    UI = loadSurface("res/image/power.png" );
    SDL_RenderCopy(renderer, UI, NULL, &destinationRect);
    SDL_DestroyTexture(UI);

    destinationRect = {30, 78, 20, 13};
    UI = loadSurface("res/image/single.png" );
    SDL_RenderCopy(renderer, UI, NULL, &destinationRect);
    SDL_DestroyTexture(UI);

    destinationRect = {40, 600, 75, 75};
    UI = loadSurface("res/image/Logo2.png" );
    SDL_RenderCopy(renderer, UI, NULL, &destinationRect);
    SDL_DestroyTexture(UI);

    destinationRect = {40, 570, 75, 45};
    UI = loadSurface("res/image/gamelogo2.png" );
    SDL_RenderCopy(renderer, UI, NULL, &destinationRect);
    SDL_DestroyTexture(UI);

    UI = nullptr;


    std::stringstream ss1;
    ss1 << "Time: " << seconds;
    std::string str1 = ss1.str();
    const char* charValue1 = str1.c_str();

    std::stringstream ss2;
    ss2 << "Fps: " << currentFPS;
    std::string str2 = ss2.str();
    const char* charValue2 = str2.c_str();


    textSurface = TTF_RenderText_Solid(font, charValue1, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect dstRect = {30, 30, textSurface->w/2, textSurface->h/2}; // 文字显示位置
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect); // 渲染纹理
    SDL_DestroyTexture(textTexture);

    textSurface = TTF_RenderText_Solid(font, charValue2, textColor);
    dstRect = {33, 45, textSurface->w/2, textSurface->h/2}; // 文字显示位置
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect); // 渲染纹理
    SDL_DestroyTexture(textTexture);




}

bool TextInputFlag = false;

void TextInput(int pos1, int pos2){

    SDL_Rect rect = {25, 115, 255, 140};


    if (pos1 > rect.x && pos1 < rect.x + rect.w && pos2 > rect.y && pos2 < rect.y + rect.h){
        TextInputFlag = true;
    }
    else{
        TextInputFlag = false; // 设置Flag来确定文本框的状态
    }
}

void InputInText(){



    if (!text.empty()){
    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Rect dstRect = {33, 120, textSurface->w/1.7, textSurface->h/1.7}; // 文字显示位置
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect); // 渲染纹理
    SDL_DestroyTexture(textTexture);



    }


}
