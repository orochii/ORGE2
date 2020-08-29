#include "Game.h"

int main( int argc, char* args[] ) {
    Uint32 frameStart;
    int frameTime;
    Game::Instance().Init("Drekirokr");
    Game::Instance().SetScene(new SceneTitle());
    while(Game::Instance().Running()) {
        frameStart = SDL_GetTicks();
        Game::Instance().HandleEvents();
        Game::Instance().Update();
        Game::Instance().Render();
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
    Game::Instance().Shutdown();
    return 0;
}
