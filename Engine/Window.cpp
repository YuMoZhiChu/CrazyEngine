#include "Window.h"

#include <iostream>


namespace CrazyEngine {

	Window* Window::m_Window = nullptr;

    Window::Window()
    {
        m_Display = new SDL_DisplayMode[SDL_GetNumVideoDisplays()];
    }

	Window* Window::getWindow()
	{
		if (m_Window == nullptr) {
			m_Window = new Window;
		}
		return m_Window;
	}

    Window::~Window()
    {
    }


    SDL_Window* Window::initSystem() {

        setOpenGL();

        SDL_Init(SDL_INIT_VIDEO);

        m_SDLWindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

        if (m_SDLWindow == nullptr)
        {
            std::cout << "Could not create window, error: " << SDL_GetError() << std::endl;
        }

        // Set up our OpenGL context
        m_glContext = SDL_GL_CreateContext(m_SDLWindow);
        if (m_glContext == nullptr) {
            std::cout << "SDL_GL context could not be created" << std::endl;
        }

        GLenum error = glewInit();
        if (error != GLEW_OK) {
            // Problem: glewInit failed, something is seriously wrong.
            std::cout << "glewInit failed: " << glewGetErrorString(error) << std::endl;
        }

        // Tell SDL that we want a double buffered window so we don't get any flickering 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        glClearColor(0.0f, 0.0f, 0.0, 1.0f);

        // Set VSync
        SDL_GL_SetSwapInterval(1); // enabled
                                   //SDL_GL_SetSwapInterval(0); // disabled

        getDisplayInfo();

        //Enable alpha blend
        glEnable(GL_BLEND);
        //Pixels can be drawn using a function that blends 
        //the incoming (source, for example a png image) RGBA values with the RGBA values 
        //that are already in the frame buffer (the destination values, for example the background).
        //glBlendFunc defines the operation of blending for all draw buffers when it is enabled.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return m_SDLWindow;
    }

    void Window::quitSystem()
    {
        SDL_GL_DeleteContext(m_glContext);
        SDL_DestroyWindow(m_SDLWindow);
        SDL_Quit();
    }


    //  tell SDL that we want a forward compatible OpenGL 3.2 context:
    void Window::setOpenGL() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        // A stencil buffer is an extra buffer, in addition to the color buffer and depth buffer
        // It used to limit the area of the rendering 
    }

    void Window::getDisplayInfo()
    {
        // Get current display mode of all displays.
        for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

            int should_be_zero = SDL_GetCurrentDisplayMode(i, &m_Display[i]);

            if (should_be_zero != 0)
                // In case of error...
                SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            else {
                // On success, print the current display mode.
                SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, 
                        m_Display[i].w, m_Display[i].h, m_Display[i].refresh_rate);

            }
        }
    }

}