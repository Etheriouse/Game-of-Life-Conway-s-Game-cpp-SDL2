#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../headers/renderwindows.hpp"
#include "../headers/entity.hpp"
#include "../headers/maths.hpp"

using namespace std;

//for windows

renderWindows::renderWindows(const char* _title, int _l, int _h) : window(NULL), renderer(NULL) {
    
    window = SDL_CreateWindow(_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _l, _h, SDL_WINDOW_SHOWN);

    if(window == NULL) {
        cout << "Hello there, sdl init has failed: " << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL) {
        cout << "Hello there, renderer init has failed: " << SDL_GetError() << endl;
    }
}

void renderWindows::cleanup() {
    
    SDL_DestroyWindow(window);
}

void renderWindows::clear() {

    SDL_RenderClear(renderer);
}

void renderWindows::render(entity& _entity, double scale) {

    SDL_Rect src;
    src.x = _entity.getCurrentFrame().x*scale;
    src.y = _entity.getCurrentFrame().y*scale;
    src.w = _entity.getCurrentFrame().w*scale;
    src.h = _entity.getCurrentFrame().h*scale;

    SDL_Rect dst;
    dst.x = _entity.getPos().x;
    dst.y = _entity.getPos().y;
    dst.w = _entity.getCurrentFrame().w*scale;
    dst.h = _entity.getCurrentFrame().h*scale;
    SDL_RenderCopy(renderer, _entity.getTexture(), &src, &dst);
}

void renderWindows::display() {
    SDL_RenderPresent(renderer);
}

int renderWindows::getRefreshTx() {
    int displayTx = SDL_GetWindowDisplayIndex( window );

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayTx, 0, &mode);

    return mode.refresh_rate;
}

SDL_Texture* renderWindows::loadTexture(const char* _filepath) {
    SDL_Texture* texture = NULL;

    texture = IMG_LoadTexture(renderer, _filepath);

    if(texture == NULL) {
        cout << "Hello there, failed to load texture: " << SDL_GetError() << endl;
    }

    return texture;
}

