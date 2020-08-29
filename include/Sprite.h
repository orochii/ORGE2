#ifndef SPRITE_H
#define SPRITE_H
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();
        void SetTexture(SDL_Texture* t);
        void Update();
        void Render(SDL_Renderer* r);
        int Width() { return w; }
        int Height() { return h; }
        // Properties
        SDL_Rect srcRect;
        int X = 0;
        int Y = 0;
        int offsetX = 0;
        int offsetY = 0;
        float zoomX = 1;
        float zoomY = 1;
    private:
        void UpdateDstRect();
        //
        SDL_Rect dstRect;
        SDL_Texture* texture;
        int w, h;
};

#endif // SPRITE_H
