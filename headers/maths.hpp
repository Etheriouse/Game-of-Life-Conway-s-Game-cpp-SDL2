#ifndef maths_hpp
#define maths_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct vectors
{
    vectors() : x(0.0f), y(0.0f){};
    vectors(float _x, float _y) : x(_x), y(_y){};

    void log() { std::cout << "x: " << x << ", y: " << y << std::endl; };
    

    float x, y;
};

#endif
