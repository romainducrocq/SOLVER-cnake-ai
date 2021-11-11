#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "utils/config.hpp"
#include "utils/events.hpp"

#include "renderer.hpp"

class Window
{
    protected:
        sf::RenderWindow   m_window;
        sfev::EventManager m_ev_manager;

        Renderer m_renderer;

protected:
        void run();

        void init();

        void loop();

        virtual void eventAdd() = 0;

        virtual void drawInit() = 0;
        
        virtual void drawLoop() = 0;

        virtual void mainInit() = 0;
        
        virtual void mainLoop() = 0;

        void waitExit();

    public:
        Window();
};

#endif