//
//  main.cpp
//  TMXLoader
//
//  Created by Marty on 06/09/2015.
//  Copyright (c) 2015 Midnight Pacific. All rights reserved.
//

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "TMXLoader.h"
#include "Levels/TMXMap.h"


SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture* tex1;
SDL_Texture* spriteSheet;

TMXLoader* loader;

bool update(SDL_Event &events)
{
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
            case SDL_WINDOWEVENT:
                switch (events.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    return false;
                    break;
                }
                break;
            case SDL_QUIT:
                return false;
                break;
        }
    }
    
    return true;
}


void renderRectOutline(SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_TRANSPARENT);
    SDL_RenderDrawRect(renderer, &rect);
}


void renderRectFilled(SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(renderer, &rect);
}


void renderTexture(SDL_Texture* texture, SDL_Rect& destRect)
{
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}


void renderSpriteSheet()
{
    int tileWidth = 25;
    int sheetWidth = 75;
    int numberOfTiles = sheetWidth / tileWidth;
    
    for (int i = 0; i < numberOfTiles; ++i)
    {
        SDL_Rect srcrect = { tileWidth * i, 0, 25, 25 };
        SDL_Rect dstrect = { i * 100, 100, 25, 25 };
        
        SDL_RenderCopy(renderer, spriteSheet, &srcrect, &dstrect);
    }
}


void testRenderMap()
{
    static unsigned int map[10][10];
   
    char tileID = 0;
    
    int width = 25;
    int height = 25;

    int row = 0;
    int column = 0;
    
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            // get the tile at current position
            //tileID = map[i][j];
            tileID = loader->getMap().getLayer().getTileLayer()[0][i][j];
            
            // only render if it is an actual tile (1, 2 or 3)
            if (tileID > 0)
            {
                SDL_Rect srcrect = { (tileID - 1) * 25, 0, width, height };
                SDL_Rect dstrect = { column, row, width, height };
                SDL_RenderCopy(renderer, spriteSheet, &srcrect, &dstrect);
            }
            column += 25;
        }
        row += 25;
        column = 0;
    }
}


void render()
{
    SDL_SetRenderDrawColor(renderer, 10, 255, 255, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.x = 50;
    rect.y = 50;
    rect.w = 100;
    rect.h = 100;
    
    //renderRectOutline(rect, 255, 50, 50);
    
    SDL_Rect rect2;
    rect2.x = 200;
    rect2.y = 50;
    rect2.w = 100;
    rect2.h = 100;
    
    //renderRectFilled(rect2, 50, 50, 255);
    
    //renderTexture(tex1, rect2);
    
    //renderSpriteSheet();
    
    testRenderMap();
    
    SDL_RenderPresent(renderer);
}


int main(int argc, const char * argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    
    Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("TMXLoader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, windowFlags);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawColor(renderer, 10, 255, 255, SDL_ALPHA_TRANSPARENT);
    
    tex1 = IMG_LoadTexture(renderer, "Assets/button.png");
    
    spriteSheet = IMG_LoadTexture(renderer, "Assets/spritesheet1.png");
    
    

    
    
    loader = new TMXLoader();
    
    loader->loadLevel("Assets/testlevel.tmx");
    
    
    
    
    
    
    
    bool running = true;
    SDL_Event events;
    while (running == true)
    {
        running = update(events);
        render();
    }
    
    return 0;
}
