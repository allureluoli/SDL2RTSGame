#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
std::pair<SDL_Texture*, SDL_Renderer*> loadSurface( std::string path );

#endif // MAIN_H_INCLUDED
