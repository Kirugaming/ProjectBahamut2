//
// Created by kirut on 11/6/2023.
//

#ifndef PROJECTBAHAMUT_INPUTMANAGER_H
#define PROJECTBAHAMUT_INPUTMANAGER_H

#include <string>
#include <SDL.h>
#include <unordered_map>

enum Inputs {
};

class InputManager {
public:
    std::unordered_map<std::string, SDL_Scancode> keyMap;
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);

    InputManager();

    static InputManager& getInstance() {
        static InputManager instance;
        return instance;
    }

    bool getKeyDown(const std::string& key);
};


#endif //PROJECTBAHAMUT_INPUTMANAGER_H
