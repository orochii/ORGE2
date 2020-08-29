#include "Game.h"

void Game::Init(const char* title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 64,64,96,255);
        }
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        int audioFlags=MIX_INIT_OGG;
        Mix_Init(audioFlags);
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        isRunning = true;
        // Initialize submodules
        cache = new Cache();
        cache->Init(renderer);
        input = new Input();
        input->Init();
        int numChannels = Mix_AllocateChannels(AUDIO_CHANNELS);
        audio = new Audio();
        audio->Init(numChannels);
    }
    if (!isRunning) return;
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        input->UpdateMouseButton(event.button.button, true);
        break;
    case SDL_MOUSEBUTTONUP:
        input->UpdateMouseButton(event.button.button, false);
        break;
    default:
        break;
    }
    input->Update();
    audio->Update();
}

void Game::Update() {
    frameCount++;
    if (currentScene != nullptr) currentScene->Update();
    if (input->KeyTrigger(SDL_SCANCODE_ESCAPE)) Exit();
}

void Game::Render() {
    if (renderFreeze) return;
    SDL_RenderClear(renderer);
    /** RENDER HERE */
    if (currentScene != nullptr) currentScene->Render(renderer);
    if (lastFrameTex != nullptr) {
        int fs = 255 * fadeState;
        SDL_SetTextureAlphaMod(lastFrameTex, fs);
        SDL_RenderCopy(renderer, lastFrameTex, NULL, NULL);
        // Update fading
        fadeState -= 0.05;
        if (fadeState < 0) {
            SDL_DestroyTexture(lastFrameTex);
            lastFrameTex = nullptr;
        }
    }
    // Do render
    SDL_RenderPresent(renderer);
}

void Game::SetScene(Scene *newScene) {
    if (currentScene != nullptr) currentScene->Close();
    currentScene = newScene;
    if (currentScene != nullptr) currentScene->Init();
}

void Game::Shutdown() {
    cache->Close();
    audio->Close();
    input->Close();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::ColorFreeze(int r, int g, int b) {
    renderFreeze = true;
    lastFrame = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(lastFrame, NULL, SDL_MapRGBA(lastFrame->format, r, g, b, 255));
}

void Game::Freeze() {
    renderFreeze = true;
    // Get screen snapshot
    lastFrame = CreateScreensnap();
}

void Game::Transition() {
    lastFrameTex = SDL_CreateTextureFromSurface(renderer, lastFrame);
    SDL_SetTextureBlendMode(lastFrameTex, SDL_BLENDMODE_BLEND);
    fadeState = 1;
    renderFreeze = false;
}

bool Game::Frozen() {
    return renderFreeze;
}

SDL_Surface* Game::CreateScreensnap() {
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    return sshot;
}

void Game::SaveScreenshot() {
    SDL_Surface *sshot = CreateScreensnap();
    IMG_SavePNG(sshot, "screenshot.png");
    SDL_FreeSurface(sshot);
}

void Game::Exit() {
    isRunning = false;
}
