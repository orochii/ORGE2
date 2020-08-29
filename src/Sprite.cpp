#include "Sprite.h"

Sprite::Sprite() {}

Sprite::~Sprite() {}

void Sprite::SetTexture(SDL_Texture* t) {
    texture = t;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = w;
    srcRect.h = h;
    //SDL_Texture* c = Game::Instance().GetCache()->LoadTexture("selectionSquare.png");
}
void Sprite::Update() {
    //
}
void Sprite::UpdateDstRect() {
    dstRect.x = X + (offsetX * zoomX);
    dstRect.y = Y + (offsetY * zoomY);
    dstRect.w = srcRect.w * zoomX;
    dstRect.h = srcRect.h * zoomY;
}
void Sprite::Render(SDL_Renderer* r) {
    UpdateDstRect();
    SDL_RenderCopy(r, texture, &srcRect, &dstRect);
}
