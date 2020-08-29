#ifndef SCENE_H
#define SCENE_H


class Scene
{
    public:
        virtual void Init() {}
        virtual void Update() {}
        virtual void Render(SDL_Renderer* renderer) {}
        virtual void Close() {}
    protected:

    private:
};

#endif // SCENE_H
