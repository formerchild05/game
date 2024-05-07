
#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <ctime>
#include <fstream>
#include <SDL_image.h>
#include"snake.h"
using namespace std;



bool inside(int &x,int &y,SDL_Rect rect)
{
    bool Inside=true;

        // Chuột nằm bên trái nút
        if( x < rect.x )
        {
            Inside = false;
        }
        //Chuột ở bên phải nút
        else if( x > rect.x + rect.w)
        {
            Inside = false;
        }
        //Chuột lên trên nút
        else if( y < rect.y )
        {
            Inside = false;
        }
        //Chuột bên dưới nút
        else if( y > rect.y + rect.h )
        {
            Inside = false;
        }
    return Inside;
}












void HITENEMY(bool& Q, snake& SNAKE, snake2& SNAKE2)
    {
        body head = SNAKE2.BODY[0];
        body head2 = SNAKE.BODY[0];
        for(int i=1 ; i<SNAKE.BODY.size() ; i++)
        {
            if(head.Xb == SNAKE.BODY[i].Xb && head.Yb == SNAKE.BODY[i].Yb)
            {
                Q = true;
                break;
            }
        }
        for(int i=1 ; i<SNAKE2.BODY.size() ; i++)
        {
            if(head2.Xb == SNAKE2.BODY[i].Xb && head2.Yb == SNAKE2.BODY[i].Yb)
            {
                Q = true;
                break;
            }
        }

    }

void process_snake_p1(snake& SNAKE, bool &quit)
{
        SNAKE.BORDERCHECK(quit);    //border
        SNAKE.update();  //movement

            //previous coordinate
        int prex = SNAKE.BODY[SNAKE.BODY.size() - 1].Xb;
        int prey = SNAKE.BODY[SNAKE.BODY.size() - 1].Yb;
        SNAKE.EATCHECK(prex, prey);
        int rotation = 0;
        switch (SNAKE.direct) {
        case snake::UP:
            rotation = -90;
            break;
        case snake::DOWN:
            rotation = 90;
            break;
        case snake::LEFT:
            rotation = 180;
            break;
        case snake::RIGHT:
            rotation = 0;
            break;
        }
        // Render each body segment with its respective rotation
        for (int i = 1; i < SNAKE.BODY.size(); i++)
            SNAKE.BODY[i].draw_body(renderer, SNAKE.BODY[i - 1].Xb, SNAKE.BODY[i - 1].Yb, rotation, i == 0);
        SNAKE.BODY[0].draw_body(renderer, 0, 0, rotation, true);
}

void process_snake_p2(snake2& SNAKE2, bool &quit, snake& SNAKE)//tham chieu den snake de dung cho ham EATCHECK
{
        SNAKE2.BORDERCHECK(quit);
         //border
        SNAKE2.update();  //movement
        //previous coordinate
        int prex2 = SNAKE2.BODY[SNAKE2.BODY.size() - 1].Xb;
        int prey2 = SNAKE2.BODY[SNAKE2.BODY.size() - 1].Yb;
        SNAKE2.EATCHECK(prex2, prey2, SNAKE);
        int rotation2 = 0;
        switch (SNAKE2.direct)
        {
        case snake2::UP:
            rotation2 = -90;
            break;
        case snake2::DOWN:
            rotation2 = 90;
            break;
        case snake2::LEFT:
            rotation2 = 180;
            break;
        case snake2::RIGHT:
            rotation2 = 0;
            break;
        }
        // Render each body segment with its respective rotation
        for (int i = 0; i < SNAKE2.BODY.size(); i++)
            SNAKE2.BODY[i].draw_body(renderer, i == 0 ? 0 : SNAKE2.BODY[i - 1].Xb, i == 0 ? 0 : SNAKE2.BODY[i - 1].Yb, rotation2, i == 0);
            SNAKE2.BODY[0].draw_body(renderer, 0, 0, rotation2, true);
}


void process_apple_p1(snake& SNAKE, SDL_Texture* appleTexture)
{
    SDL_Rect appleRect;
        appleRect.x = SNAKE.FOOD.fX;
        appleRect.y = SNAKE.FOOD.fY;
        appleRect.w = 20;
        appleRect.h = 20;
        if (appleTexture != NULL)
            SDL_RenderCopy(renderer, appleTexture, NULL, &appleRect);
}


void process_apple_p2(snake& SNAKE, SDL_Texture* appleTexture)
{
    SDL_Rect appleRect;
        appleRect.x = SNAKE.FOOD2.fX;
        appleRect.y = SNAKE.FOOD2.fY;
        appleRect.w = 20;
        appleRect.h = 20;
        if (appleTexture != NULL)
            SDL_RenderCopy(renderer, appleTexture, NULL, &appleRect);
}