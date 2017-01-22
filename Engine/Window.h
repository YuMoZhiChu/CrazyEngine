#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>

namespace CrazyEngine {

    class Window 
    {
        SDL_Window* m_SDLWindow;
        SDL_GLContext m_glContext;

        SDL_DisplayMode* m_Display;

        void setOpenGL();
        void getDisplayInfo();

		static Window* m_Window;
		Window();

    public:

		static Window* getWindow();

        SDL_Window* getSDLWindow() const {
            return m_SDLWindow;
        }

        int getMonitoRefreshRate() {
            return m_Display[0].refresh_rate;
        }

        ~Window();

        SDL_Window* initSystem();
        void quitSystem();

    };
}




