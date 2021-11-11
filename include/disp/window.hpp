#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/config.hpp"

#include "ev_mngr.hpp"
#include "ev_state.hpp"
#include "renderer.hpp"

class Window
{
    protected:
        sf::RenderWindow m_window;
        Renderer m_renderer;

        sfev::EventManager m_ev_mngr;
        EventState m_ev_state;

    protected:
        void setup();

        void loop();

        virtual void viewSetup() = 0;
        
        virtual void viewLoop() = 0;

        virtual void ctrlSetup() = 0;
        
        virtual void ctrlLoop() = 0;

        void waitExit();

    public:
        Window();
};

#endif