#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../headers/entity.hpp"
#include "../headers/renderWindows.hpp"
#include "../headers/utils.hpp"

// conway game
#include "../headers/space.hpp"
#include "../headers/coo.hpp"
#include "../headers/other.hpp"
#include "../headers/check.hpp"

using namespace std;
using namespace this_thread;

const int Largeur = 1024;
const int Longueur = 1920;
const int NumberOfCelulle = 7;

int nombreItteration(-1);
int tps(-1);
int borderlen(-1);

bool HighLow = false;

vector<vector<int>> simulation()
{
    cout << "choice the number of itteration" << endl;
    cin >> nombreItteration;
    cin.ignore();

    cout << "choice the latence without two generation (ms)" << endl;
    cin >> tps;
    cin.ignore();

    cout << "choice the length of border" << endl;
    cin >> borderlen;
    cin.ignore();

    if (borderlen > 32)
    {
        HighLow = true;
    }

    if (tps < 0 || NumberOfCelulle < 0 || borderlen < 5)
    {
        cout << "invalide tps or numberItteration or border" << endl;
        exit(1);
    }
    vector<vector<int>> t = CreateSpaceCelulle(borderlen, borderlen);
    // ViewSpace(t);

    return t;
}

int main(int argc, char *argv[])
{

    vector<vector<int>> t = simulation();

    if(borderlen>32) {
        cout << "error borderlen is too length :(" << endl;
        exit(0); 
    }

    // sdl_init renvoie 0 ou sup si tout va bien
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "Hello there, sdl init has failed: " << SDL_GetError() << endl;
    }

    // img init est quelque chose si tout va bien
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        cout << "Hello there, img init has failed: " << SDL_GetError() << endl;
    }

    // crée la fenertre avec un nom et les dimension longueur hauteur
    renderWindows windows("gaïa v0.1", Longueur, Largeur);

    // créate texture

    SDL_Texture *_black = windows.loadTexture("C:\\Code\\Cpp\\gui\\ConwayGame\\src\\ressource\\black.png");
    SDL_Texture *_white = windows.loadTexture("C:\\Code\\Cpp\\gui\\ConwayGame\\src\\ressource\\white.png");
    SDL_Texture *_rebord = windows.loadTexture("C:\\Code\\Cpp\\gui\\ConwayGame\\src\\ressource\\rebord.png");

    // create entity
    // entity entityes[4] = {
    //     entity(0, 0, _tricetops),
    //     entity(32, 0, _tricetops),
    //     entity(0, 32, _tricetops),
    //     entity(32, 32, _tricetops)
    // };

    /*vector<entity> entitys = {
        entity(vectors(0, 0), _tricetops),
        entity(vectors(32, 0), _tricetops),
        entity(vectors(0, 32), _tricetops),
        entity(vectors(32, 32), _tricetops)};

    entity tricetops(vectors(100, 100), _tricetops);
    */
    bool gameOn(1);

    // on crée un evenement X
    SDL_Event event;

    const float fps = 0.01f; // < = > 100 fps;
    float accumulator = 0.0f;
    float currentTime = util::timeLocationInSeconds();

    int n(0);

    // crée une boucle while pour laisse le jeu ouvert, sinon il se ferme tout seul
    while (gameOn)
    {

        int startTick = SDL_GetTicks();

        float newTime = util::timeLocationInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= fps)
        {

            while (SDL_PollEvent(&event))
            {
                // si le type de l'evenement est de fermer la fenetre (sdl_quit)
                // on met gameOn a false se qui arrete la boucle principal
                if (event.type == SDL_QUIT)
                {
                    gameOn = false;
                }
            }

            accumulator -= fps;
        }

        const float alpha = accumulator / fps;

        vector<entity> floor; // = makeSky();

        for (int i(0); i < borderlen; i += 1)
        {
            for (int y(0); y < borderlen; y += 1)
            {
                // cout << "Longueur: " << (Longueur/borderlen) * i << " Largeur: " << (y * (Largeur/borderlen)) << endl;
                // cout << "i: " << i << " y: " << y << endl;

                if (t[i][y] == -1)
                {
                    floor.push_back(entity(vectors((Largeur / borderlen) * i, y * (Largeur / borderlen)), _black));
                }
                else if (t[i][y] == 0)
                {
                    floor.push_back(entity(vectors((Largeur / borderlen) * i, y * (Largeur / borderlen)), _white));
                }
                else
                {
                    floor.push_back(entity(vectors(i * (Largeur / borderlen), y * (Largeur / borderlen)), _rebord));
                }
            }
        }

        windows.clear();

    
            for (int i(0); i < floor.size(); i += 1)
            {
                windows.render(floor[i], (Largeur / (borderlen * 32)));
            }

        windows.display();

        if (n < nombreItteration)
        {
            vector<int> Deces = checkingDeces(t);
            vector<int> Naissance = chekingNaissance(t);
            t = nextSpaceCelulle(borderlen, borderlen, Deces, Naissance, t);
            sleep_for(chrono::milliseconds(tps));
            system("cls");
            // ViewSpace(t);
            cout << "round " << n << endl;
            n += 1;
        }

        int frameTicks = SDL_GetTicks() - startTick;

        if (frameTicks < 1000 / windows.getRefreshTx())
        {
            SDL_Delay(1000 / windows.getRefreshTx() - frameTicks);
            // cout << "FrameRate: " << windows.getRefreshTx() << endl;
        }
    }

    // ferme la fenetre ouverte
    windows.cleanup();
    // leave sdl
    SDL_Quit();

    return 0;
}