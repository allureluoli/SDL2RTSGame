#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

bool loadBackground();
bool PlayMusic();
extern SDL_Texture* gPNGSurface; // 声明“全局”变量需要 extern，否则在main.cpp中会被认为进行了多重定义。
extern SDL_Renderer* renderer;


#endif // MEDIA_H_INCLUDED
