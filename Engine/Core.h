#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>


enum GameState {
    START,
    QUIT,
};

static GameState gameState = START;

void processEvent();

bool fileExist(const std::string& dirName_in);