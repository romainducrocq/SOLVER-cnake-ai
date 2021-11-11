#ifndef _APP_HPP
#define _APP_HPP

#include "utils/config.hpp"

#include "disp/window.hpp"

#include "snake/snake.hpp"
#include "agent/agent.hpp"

class Application: public Window
{
    private:
        typedef Window Super;

        Agent m_agent;
        Apple m_apple;
        Snake m_snake;

    private:
        void viewSetup() override;

        void viewLoop() override;

        void ctrlSetup() override;
        
        void ctrlLoop() override;

    private:
        int getAction();

    public:
        Application();
};

#endif