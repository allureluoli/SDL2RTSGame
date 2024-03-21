#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED
#include <SDL_ttf.h>// 头文件中也需要包含库啊
bool init();
extern SDL_Window* gWindow;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

#endif // INIT_H_INCLUDED
