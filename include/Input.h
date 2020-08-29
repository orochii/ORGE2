#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <cstring>
#include "Constants.h"

class Input
{
    public:
        Input();
        virtual ~Input();
        void Init();
        void Update();
        void Close();
        bool KeyPressed(int scancode);
        bool KeyTrigger(int scancode);
        bool KeyRelease(int scancode);
        bool MousePressed(Uint8 buttonId);
        bool MouseTrigger(Uint8 buttonId);
        bool MouseRelease(Uint8 buttonId);
        int Horizontal();
        int Vertical();
        int mouseX;
        int mouseY;
        void UpdateMouseButton(Uint8 buttonId, bool state);
        void UpdateGamepadAxis();
        void UpdateGamepadButton();
    private:
        Uint8 currentKeystates[SDL_NUM_SCANCODES];
        Uint8 lastKeystates[SDL_NUM_SCANCODES];
        bool mouseState[MOUSE_BUTTON_SIZE];
        bool currentMouseStates[MOUSE_BUTTON_SIZE];
        bool lastMouseStates[MOUSE_BUTTON_SIZE];
};

#endif // INPUT_H
