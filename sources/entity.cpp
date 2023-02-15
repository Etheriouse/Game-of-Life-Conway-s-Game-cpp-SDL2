#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include "../headers/maths.hpp"
#include "../headers/entity.hpp"

using namespace std;

entity::entity(vectors _pos, SDL_Texture* _texture) : vect(_pos), texture(_texture) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32; 
}

SDL_Texture* entity::getTexture() {
    return texture;
}

SDL_Rect entity::getCurrentFrame() {
    return currentFrame;
}