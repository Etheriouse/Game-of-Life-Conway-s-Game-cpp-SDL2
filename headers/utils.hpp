#ifndef utils_hpp
#define utils_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace util
{
    inline float timeLocationInSeconds() 
    {
        float t = SDL_GetTicks();
        t*=0.001f;
        return t;
    }
}

#endif