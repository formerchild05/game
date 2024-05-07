#pragma once
#include <iostream>
#include <fstream>
#include <SDL.h>
using namespace std;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
void draw1(int x,int y)
{
    SDL_Rect box;
    box.h=20;
    box.w=20;
    box.x=x;
    box.y=y;
    SDL_SetRenderDrawColor(renderer,255,255,0,255);
    SDL_RenderFillRect(renderer,&box);
}
void draw0(int x,int y)
{
    SDL_Rect box;
    box.h=20;
    box.w=20;
    box.x=x;
    box.y=y;
    SDL_SetRenderDrawColor(renderer,0,204,0,255);
    SDL_RenderFillRect(renderer,&box);
}
void input_map(char MAP[24][32])
{
    string path="input_map.txt";
    ifstream file(path);
    for(int i=0; i<=23; i++)
        for(int j=0; j<=31; j++)
        {
            char temp;
            file>>temp;
            MAP[i][j]=temp;
        }
    for(int i=0; i<=23; i++)
    {
        for(int j=0; j<=31; j++)
            cout<<MAP[i][j]<<" ";
        cout<<endl;
    }
    file.close();
    // draw map (put in main loop)
//        for(int i=0; i<=23; i++)
//            for(int j=0; j<=31; j++)
//                if((i+j) %2 == 0)
//                    draw1(j*20,i*20);
//                else draw0(j*20,i*20);

}
