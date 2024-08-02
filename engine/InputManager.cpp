//
// Created by kirut on 11/6/2023.
//

#include "InputManager.h"

InputManager::InputManager() {
    keyMap["w"] = SDL_SCANCODE_W;
    keyMap["a"] = SDL_SCANCODE_A;
    keyMap["s"] = SDL_SCANCODE_S;
    keyMap["d"] = SDL_SCANCODE_D;
    keyMap["up"] = SDL_SCANCODE_UP;
    keyMap["down"] = SDL_SCANCODE_DOWN;
    keyMap["left"] = SDL_SCANCODE_LEFT;
    keyMap["right"] = SDL_SCANCODE_RIGHT;
    keyMap["space"] = SDL_SCANCODE_SPACE;
    keyMap["right shift"] = SDL_SCANCODE_RSHIFT;
    keyMap["right ctrl"] = SDL_SCANCODE_RCTRL;
    keyMap["tab"] = SDL_SCANCODE_TAB;
}

bool InputManager::getKeyDown(const std::string& key) {
    auto foundKey = keyMap.find(key);
    if (foundKey != keyMap.end()) {
        return keys[foundKey->second];
    }
    return false;
}


