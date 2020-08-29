#include "SceneTitle.h"
#include <algorithm>
#include <vector>

Sprite* playerSprite;

void SceneTitle::Init() {
    playerSprite = new Sprite();
    playerSprite->SetTexture(Game::GetCache()->LoadTexture("Characters/alice_charset.png"));
    playerSprite->srcRect.w = playerSprite->Width() / 4;
    playerSprite->srcRect.h = playerSprite->Height() / 4;
    // Play Music
    Mix_Music* msc = Game::GetCache()->LoadMusic("undefined-place.ogg");
    Game::GetAudio()->PlayMusic(msc, 128, 0);
}

void SceneTitle::Update() {
    // Move character
    int horz = Game::GetInput()->Horizontal();
    int vert = Game::GetInput()->Vertical();
    int posX = playerSprite->X + horz * 2;
    int posY = playerSprite->Y + vert * 2;
    playerSprite->X = posX;
    playerSprite->Y = posY;
    // Play sound
    if (Game::GetInput()->KeyTrigger(SDL_SCANCODE_LALT)) {
        Mix_Chunk* snd = Game::GetCache()->LoadSound("Axe_slash1.ogg");
        Game::GetAudio()->PlaySound(snd, 128);
        playerSprite->X += 32;
    }
}

void SceneTitle::Render(SDL_Renderer* renderer) {
    playerSprite->Render(renderer);
}

void SceneTitle::Close() {
    //
}
