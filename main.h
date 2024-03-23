#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

extern SDL_Surface* gScreenSurface;

extern int currentFPS;
extern int seconds;
extern std::string  text;
extern float hdpi, vdpi;
SDL_Texture* loadSurface(std::string path);

#endif // MAIN_H_INCLUDED
