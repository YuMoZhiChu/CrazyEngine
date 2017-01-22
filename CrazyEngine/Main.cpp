#pragma once

#define GLEW_STATIC

#include <iostream>
#include <Engine\Window.h>
#include <Engine\Core.h>
#include "Test.h"

#define NUMTEST 5

int main(int argc, char* argv[]) {

    std::cout << "Number of the test: [1-" << NUMTEST << "]" << std::endl;

	CrazyEngine::Window* window = CrazyEngine::Window::getWindow();

	window->initSystem();

    int test = 0;
    do {
        std::cin >> test;
    } while (test <= 0 && test > NUMTEST);   

    Test* currentTest = Test::chooseTest(test);

    currentTest->Init();

    while (gameState != QUIT) {
        processEvent();

        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentTest->draw();

        SDL_GL_SwapWindow(window->getSDLWindow());
    }

    window->quitSystem();

    return 0;
}