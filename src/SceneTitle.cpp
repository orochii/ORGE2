#include "SceneTitle.h"
#include <algorithm>
#include <vector>
#include "tmx/tmx.h"

Sprite* playerSprite;
bool mapLoaded;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;
tmx_map* mapData;

void SceneTitle::Init() {
    // TMX test
    mapLoaded = true;
    std::string location = "title.tmx";
    mapData = tmx_load(location.c_str());
    if (mapData == NULL) mapLoaded = false;
    //
    playerSprite = new Sprite();
    playerSprite->SetTexture(Game::GetCache()->LoadTexture("Characters/alice_charset.png"));
    playerSprite->srcRect.w = playerSprite->Width() / 4;
    playerSprite->srcRect.h = playerSprite->Height() / 4;
    // Play Music
    Mix_Music* msc = Game::GetCache()->LoadMusic("undefined-place.ogg");
    Game::GetAudio()->PlayMusic(msc, 128, 0);
    // Create text
    SDL_Color White = {255,255,255};
    // Draw line on screen for map load state
    if (mapLoaded) surfaceMessage = TTF_RenderText_Solid(Game::GetCache()->gFont, "Map Loaded", White);
    else surfaceMessage = TTF_RenderText_Solid(Game::GetCache()->gFont, "Map wasn't loaded", White);
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
    // Render player
    playerSprite->Render(renderer);
    // Render map loaded text
    if (Message == NULL) {
        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    int w,h;
    SDL_QueryTexture(Message, NULL, NULL, &w, &h);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 4;
    Message_rect.y = SCREEN_HEIGHT - h - 4;
    Message_rect.w = w;
    Message_rect.h = h;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

void SceneTitle::Close() {
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
