#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Constants.h"
#include "Cache.h"
#include "Audio.h"
#include "Input.h"
#include "Sprite.h"
#include "Scene.h"
#include "SceneTitle.h"

class Game
{
    public:
        // Singleton
        static Game& Instance() {
            static Game instance;
            return instance;
        }
        Game() {}
        Game(Game const&)           = delete;
        void operator=(Game const&) = delete;
        // Modules access
        static Cache* GetCache() { return Instance().cache; }
        static Audio* GetAudio() { return Instance().audio; }
        static Input* GetInput() { return Instance().input; }
        // Engine specific
        void Init(const char* title);
        void HandleEvents();
        void Update();
        void Render();
        void Shutdown();
        // Functions
        bool Running() { return isRunning; }
        void Exit();
        void SetScene(Scene *newScene);
        SDL_Surface* CreateScreensnap();
        void SaveScreenshot();
        void ColorFreeze(int r, int g, int b);
        void Freeze();
        void Transition();
        bool Frozen();
    private:
        // Graphics state
        bool isRunning = false;
        bool renderFreeze = false;
        int frameCount = 0;
        // Rendering
        SDL_Window* window;
        SDL_Renderer* renderer;
        // Fading
        SDL_Surface *lastFrame = nullptr;
        SDL_Texture *lastFrameTex = nullptr;
        double fadeState = 0;
        // Modules
        Cache* cache;
        Audio* audio;
        Input* input;
        // Scene
        Scene *currentScene = nullptr;
};

#endif // GAME_H
