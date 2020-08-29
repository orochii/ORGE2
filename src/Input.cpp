#include "Input.h"

Input::Input() {
}

Input::~Input() {
}

void Input::Init() {
    memset(lastKeystates, 0, sizeof(Uint8)*SDL_NUM_SCANCODES);
    memcpy(currentKeystates, SDL_GetKeyboardState(NULL), sizeof(Uint8)*SDL_NUM_SCANCODES);
    //
    memset(mouseState, 0, sizeof(bool)*MOUSE_BUTTON_SIZE);
    memset(lastMouseStates, 0, sizeof(bool)*MOUSE_BUTTON_SIZE);
    memcpy(currentMouseStates, mouseState, sizeof(bool)*MOUSE_BUTTON_SIZE);
}

void Input::Update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    // Update keyboard button states
    memcpy(lastKeystates, currentKeystates, sizeof(Uint8)*SDL_NUM_SCANCODES);
    memcpy(currentKeystates, SDL_GetKeyboardState(NULL), sizeof(Uint8)*SDL_NUM_SCANCODES);
    // Update mouse button states
    memcpy(lastMouseStates, currentMouseStates, sizeof(bool)*MOUSE_BUTTON_SIZE);
    memcpy(currentMouseStates, mouseState, sizeof(bool)*MOUSE_BUTTON_SIZE);
}

void Input::UpdateMouseButton(Uint8 buttonId, bool state) {
    mouseState[buttonId] = state;
}
void Input::UpdateGamepadAxis() {
    //
}
void Input::UpdateGamepadButton() {
    //
}

void Input::Close() {
    //
}

bool Input::KeyPressed(int scancode) {
    return currentKeystates[scancode];
}

bool Input::KeyTrigger(int scancode) {
    return currentKeystates[scancode] && !lastKeystates[scancode];
}

bool Input::KeyRelease(int scancode) {
    return !currentKeystates[scancode] && lastKeystates[scancode];
}

bool Input::MousePressed(Uint8 buttonId) {
    return currentMouseStates[buttonId];
}

bool Input::MouseTrigger(Uint8 buttonId) {
    return currentMouseStates[buttonId] && !lastMouseStates[buttonId];
}

bool Input::MouseRelease(Uint8 buttonId) {
    return !currentMouseStates[buttonId] && lastMouseStates[buttonId];
}

int Input::Horizontal() {
    bool left = KeyPressed(SDL_SCANCODE_LEFT);
    bool right= KeyPressed(SDL_SCANCODE_RIGHT);
    return (right - left);
}
int Input::Vertical() {
    bool up   = KeyPressed(SDL_SCANCODE_UP);
    bool down = KeyPressed(SDL_SCANCODE_DOWN);
    return (down - up);
}
