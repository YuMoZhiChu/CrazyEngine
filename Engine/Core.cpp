#pragma once

#include "Core.h"

#include <iostream>
#include <fstream>

void processEvent() {
    SDL_Event SDL_event;
    while (SDL_PollEvent(&SDL_event))
    {
        switch (SDL_event.type) {
        case SDL_QUIT:
            gameState = QUIT;
            break;
        }
    }
}

bool fileExist(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (file.fail()) {
        std::cout << "Failed to open " + filePath << std::endl;
        return false;
    }
    else {
        return true;
    }
}