#include"snake.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include <ctime>
#include <fstream>
#include <SDL_image.h>
#include"function.h"
using namespace std;



int main(int argc, char* args[])
{
    // create window
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    srand(time(NULL));
        SDL_Texture* menuTexture = loadTexture("menu.jpg",renderer);
        SDL_Texture* playTexture = loadTexture("play.png",renderer);
        SDL_Texture* p1winTexture = loadTexture("P1.png",renderer);
        SDL_Texture* p2winTexture = loadTexture("P2.png",renderer);
        SDL_RenderCopy (renderer, menuTexture, NULL, NULL);
        SDL_Rect play ;
        SDL_QueryTexture(playTexture, NULL, NULL, &play.w, &play.h);
        play.x = 200;
        play.y = 200;
        play.h /= 8;
        play.w /= 8;
        SDL_RenderCopy(renderer, playTexture,NULL, &play);
        SDL_RenderPresent(renderer);
        SDL_Event e;
        bool quit = false;
    bool win =true;

    while(!quit)
    {
        while( SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit=true;
            }
            int x,y;
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&x,&y);

                    if(inside(x,y, play))
                    {
                        SDL_Texture* backgroundTexture = loadTexture("backgr.jpg", renderer);
                        SDL_Texture* appleTexture = loadTexture("food.png", renderer);
                        //chen anh qua tao

                        snake SNAKE;
                        snake2 SNAKE2;
//                        bool quit = false;


                        while (!quit)
                        {
                            SDL_RenderClear(renderer); // Clear the renderer
                            if (backgroundTexture != nullptr)
                                SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);           // load anh backgr

                            process_apple_p1(SNAKE,appleTexture);
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

                            process_snake_p2(SNAKE2,quit,SNAKE);


                            win = HITENEMY(quit, SNAKE, SNAKE2);


                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);

                        }
                            SDL_DestroyTexture(backgroundTexture);

                    }
                }
            }
        }
    }
    quit = false;
    while (!quit) {
    // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // User presses spacebar to quit manually
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                quit = true;
            }
        }

        if (win) {
            SDL_RenderCopy(renderer, p1winTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
            //SDL_Delay(3000);
            //cout << "PLAYER 1 WIN";
        }
        else {
            SDL_RenderCopy(renderer, p2winTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
            //SDL_Delay(3000);
            //cout << "PLAYER 2 WIN";
        }
        // Update screen
        SDL_RenderPresent(renderer);
    }
    if (win) {
        SDL_DestroyTexture(p1winTexture);
    }
    else {
        SDL_DestroyTexture(p2winTexture);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();




    return 0;
}
