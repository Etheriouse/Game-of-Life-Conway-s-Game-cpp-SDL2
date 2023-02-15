//#pragma once
#ifndef renderwindows_hpp
#define renderwindows_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../headers/entity.hpp"
#include "../headers/maths.hpp"

class renderWindows {

    public:
        renderWindows(const char* _title, int _l, int _h);
        void cleanup();
        void clear();
        void render(entity& _entity, double scale);
        void display();

        int getRefreshTx();
        SDL_Texture * loadTexture(const char* _filepath);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif