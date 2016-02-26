#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "Character.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*junk,*junk2,*poo;
SDL_Rect rect_background,rect_junk,rect_junk2,rect_poo,rect_character;



int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    background = IMG_LoadTexture(renderer,"assets/background.jpg");
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;



    junk = IMG_LoadTexture(renderer,"assets/junk.png");
    rect_junk.x=0;
    rect_junk.y=475;
    rect_junk.w=400;
    rect_junk.h=150;

    junk2 = IMG_LoadTexture(renderer,"assets/junk.png");
    rect_junk2.x=700;
    rect_junk2.y=475;
    rect_junk2.w=400;
    rect_junk2.h=150;



    poo = IMG_LoadTexture(renderer,"assets/poo.png");
    rect_poo.x=400;
    rect_poo.y=475;
    rect_poo.w=150;
    rect_poo.h=75;

    Character* character = new Character(renderer,200,200);

    //Main Loop
    double last_frame=0;
    bool pause=false,start = false;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_p){
                    if(pause==false){
                        pause = true;
                    }else{
                        pause = false;
                    }
                }else if(Event.key.keysym.sym == SDLK_ESCAPE){
                    return 0;
                }

            }
        }

        if(pause==false){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, background, NULL, &rect_background);

            SDL_RenderCopy(renderer, poo, NULL, &rect_poo);



            SDL_RenderCopy(renderer, junk, NULL, &rect_junk);
            SDL_RenderCopy(renderer, junk2, NULL, &rect_junk2);

            character->logic();
            character->draw();


            SDL_RenderPresent(renderer);

            double last_frame_duration=SDL_GetTicks()-last_frame;
            double dif = 17-last_frame_duration;
                if(dif>0)
                {
                    SDL_Delay(dif);
                }
            last_frame=SDL_GetTicks();
        }

    }

	return 0;
}
