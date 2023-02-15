#ifndef entity_hpp
#define entity_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../headers/maths.hpp"

class entity {

    public:

        entity(vectors _pos, SDL_Texture* _texture);
        vectors& getPos() {
            return vect;
        };

        SDL_Texture* getTexture();
        SDL_Rect getCurrentFrame();
    private:
        vectors vect;
        SDL_Rect currentFrame;
        SDL_Texture* texture;

};

#endif