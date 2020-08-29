#ifndef SCENETITLE_H
#define SCENETITLE_H

#include "Game.h"

class SceneTitle : public Scene {
    public:
        void Init();
        void Update();
        void Render(SDL_Renderer* renderer);
        void Close();
    protected:

    private:
};

#endif // SCENETITLE_H
