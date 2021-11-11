#ifndef _APP_HPP
#define _APP_HPP

#include <SFML/Graphics.hpp>

#include "utils/config.hpp"
#include "utils/events.hpp"

#include "disp/window.hpp"

#include "impl/snake.hpp"
#include "impl/agent.hpp"

struct EventState
{
    int  speed = 0;
    bool debug = false;

    Conf::Action action = Conf::NOOP;
};

class Application: public Window
{
    private:
        typedef Window Super;

        EventState m_ev_state;

        Agent m_agent;
        Apple m_apple;
        Snake m_snake;

    private:
        void eventAdd() override;

        void drawInit() override;

        void drawLoop() override;

        void mainInit() override;
        
        void mainLoop() override;

        int getAction();

    public:
        Application();
};

#endif