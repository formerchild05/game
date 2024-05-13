#include"snake.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include <ctime>
#include <fstream>
#include <SDL_image.h>
#include"function.h"
#include<SDL_mixer.h>
#include "main.h"
using namespace std;

bool win_audio = false;
bool menu_audio = false;

int main(int argc, char* args[])
{
    // create window
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError();
    }

    srand(time(NULL));
    SDL_Texture* menuTexture = loadTexture("menu.jpg", renderer);
    SDL_Texture* playTexture = loadTexture("play.png", renderer);
    SDL_Texture* p1winTexture = loadTexture("P1.png", renderer);
    SDL_Texture* p2winTexture = loadTexture("P2.png", renderer);
    SDL_Texture* head1menu = loadTexture("head_p1menu.png", renderer);
    SDL_Texture* head2menu = loadTexture("head_p2menu.png", renderer);
    SDL_Texture* key1 = loadTexture("key1.png", renderer);
    SDL_Texture* key2 = loadTexture("key2.png", renderer);
    SDL_Texture* loaTexture = loadTexture("load1.png", renderer);
    SDL_Texture* loa2Texture = loadTexture("load2.png", renderer);
    SDL_Texture* loa3Texture = loadTexture("load3.png", renderer);
    SDL_Texture* space = loadTexture("space.png", renderer);
    Mix_Music* nhacnen = Mix_LoadMUS("nhacnen.mp3");
    Mix_Chunk* wingame = Mix_LoadWAV("nhaccachmang.wav");
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_Rect menukey1;
    SDL_QueryTexture(key1, NULL, NULL, &menukey1.w, &menukey1.h);
    menukey1.x = 30;
    menukey1.y = 300;
    menukey1.h /= 2;
    menukey1.w /= 2;
    SDL_Rect menukey2;
    SDL_QueryTexture(key2, NULL, NULL, &menukey2.w, &menukey2.h);
    menukey2.x = 500;
    menukey2.y = 300;
    menukey2.h /= 2;
    menukey2.w /= 2;
    SDL_Rect headm1;
    SDL_QueryTexture(head1menu, NULL, NULL, &headm1.w, &headm1.h);
    headm1.x = 30;
    headm1.y = 150;
    headm1.h /= 3.5;
    headm1.w /= 3.5;
    SDL_Rect headm2;
    SDL_QueryTexture(head2menu, NULL, NULL, &headm2.w, &headm2.h);
    headm2.x = 390;
    headm2.y = 150;
    headm2.h /= 3.5;
    headm2.w /= 3.5;
    SDL_Rect loa;
    SDL_QueryTexture(loaTexture, NULL, NULL, &loa.w, &loa.h);
    loa.x = 250;
    loa.y = 350;
    loa.h /= 2;
    loa.w /= 2;
    SDL_Rect sb;
    SDL_QueryTexture(playTexture, NULL, NULL, &sb.w, &sb.h);
    sb.x = 190;
    sb.y = 310;
    sb.h /= 10;
    sb.w /= 2;
    SDL_Rect play;
    SDL_QueryTexture(playTexture, NULL, NULL, &play.w, &play.h);
    play.x = 270;
    play.y = 280;
    play.h /= 5;
    play.w /= 5;
    SDL_RenderCopy(renderer, playTexture, NULL, &play);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_Event e;
    bool quit = false;
    bool win = true;
    bool playAgain = false;
    bool result = false;

    Mix_PlayMusic(nhacnen, -1);
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            int x, y;

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&x, &y);

                    if (inside(x, y, play))
                    {
                        Redering(menuTexture, head2menu, headm2, head1menu, headm1, key1, menukey1, key2, menukey2, loaTexture, loa, loa2Texture, loa3Texture);
                        SDL_Texture* backgroundTexture = loadTexture("backgr.jpg", renderer);
                        SDL_Texture* appleTexture = loadTexture("food.png", renderer);
                        //chen anh qua tao

                        snake SNAKE;
                        snake2 SNAKE2;
                        RunGame(quit, backgroundTexture, SNAKE, appleTexture, e, SNAKE2, win);
                        SDL_DestroyTexture(backgroundTexture);
                        Mix_HaltMusic();
                        Winner(result, e, win, p1winTexture, wingame, p2winTexture, space, sb);
                        Mix_HaltMusic();
                        SDL_RenderClear(renderer);
                        quit = false;
                        result = false;
                        win_audio = false;
                        menu_audio = false;
                        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
                        SDL_RenderCopy(renderer, playTexture, NULL, &play);
                        Mix_PlayMusic(nhacnen, -1);
                        SDL_RenderPresent(renderer);
                        //SDL_RenderClear(renderer);
                    }
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();




    return 0;
}

void Winner(bool& result, SDL_Event& e, bool win, SDL_Texture* p1winTexture, Mix_Chunk* wingame, SDL_Texture* p2winTexture, SDL_Texture* space, SDL_Rect& sb)
{
    while (!result) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                result = true;
                Mix_HaltMusic();
            }

            // User presses spacebar to quit manually
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                result = true;
                Mix_HaltMusic();
            }
        }

        if (win) {
            SDL_RenderCopy(renderer, p1winTexture, NULL, NULL);
            SDL_RenderCopy(renderer, space, NULL, &sb);
            SDL_RenderPresent(renderer);
            if (!win_audio) {
                Mix_PlayChannel(-1, wingame, 0);
                win_audio = true;
            }
            //SDL_Delay(5000);
            //cout << "PLAYER 1 WIN";
        }
        else {
            SDL_RenderCopy(renderer, p2winTexture, NULL, NULL);
            SDL_RenderCopy(renderer, space, NULL, &sb);
            SDL_RenderPresent(renderer);
            if (!win_audio) {
                Mix_PlayChannel(-1, wingame, 0);
                win_audio = true;
            }
            //SDL_Delay(5000);
            //cout << "PLAYER 2 WIN";
        }
        // Update screen
        SDL_RenderPresent(renderer);
    }
}

void RunGame(bool& quit, SDL_Texture* backgroundTexture, snake& SNAKE, SDL_Texture* appleTexture, SDL_Event& e, snake2& SNAKE2, bool& win)
{
    while (!quit)
    {
        SDL_RenderClear(renderer); // Clear the renderer
        if (backgroundTexture != nullptr)
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);           // load anh backgr

        process_apple_p1(SNAKE, appleTexture);
        process_apple_p2(SNAKE, appleTexture);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
            // quit = escape
            const Uint8* keys = SDL_GetKeyboardState(nullptr);
            if (keys[SDL_SCANCODE_ESCAPE])
                quit = true;
            SNAKE.input_dir(e);
            SNAKE2.input_dir(e);
        }

        process_snake_p1(SNAKE, quit);

        process_snake_p2(SNAKE2, quit, SNAKE);


        win = WINLOSE(quit, SNAKE, SNAKE2);


        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }
}

void Redering(SDL_Texture* menuTexture, SDL_Texture* head2menu, SDL_Rect& headm2, SDL_Texture* head1menu, SDL_Rect& headm1, SDL_Texture* key1, SDL_Rect& menukey1, SDL_Texture* key2, SDL_Rect& menukey2, SDL_Texture* loaTexture, SDL_Rect& loa, SDL_Texture* loa2Texture, SDL_Texture* loa3Texture)
{

    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_RenderCopy(renderer, head2menu, NULL, &headm2);
    SDL_RenderCopy(renderer, head1menu, NULL, &headm1);
    SDL_RenderCopy(renderer, key1, NULL, &menukey1);
    SDL_RenderCopy(renderer, key2, NULL, &menukey2);
    SDL_RenderCopy(renderer, loaTexture, NULL, &loa);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_RenderCopy(renderer, head2menu, NULL, &headm2);
    SDL_RenderCopy(renderer, head1menu, NULL, &headm1);
    SDL_RenderCopy(renderer, key1, NULL, &menukey1);
    SDL_RenderCopy(renderer, key2, NULL, &menukey2);
    SDL_RenderCopy(renderer, loa2Texture, NULL, &loa);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_RenderCopy(renderer, head2menu, NULL, &headm2);
    SDL_RenderCopy(renderer, head1menu, NULL, &headm1);
    SDL_RenderCopy(renderer, key1, NULL, &menukey1);
    SDL_RenderCopy(renderer, key2, NULL, &menukey2);
    SDL_RenderCopy(renderer, loa3Texture, NULL, &loa);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}
