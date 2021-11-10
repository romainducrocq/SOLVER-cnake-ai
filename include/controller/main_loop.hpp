#ifndef _MAIN_LOOP_H
#define _MAIN_LOOP_H

#include <SFML/Graphics.hpp>

#include "../view/view.hpp"

#include "../model/agent.hpp"
#include "../model/snake.hpp"

#include "../utils/config.hpp"
#include "../utils/vector.hpp"

class MainLoop: public View
{
    private:
        typedef View Super;

        Agent m_agent;
        Apple m_apple;
        Snake m_snake;

    private:
        int get_action();

        void act(int action);

        void view_setup() override;

        void view_loop() override;

        void ctrl_setup() override;
        
        void ctrl_loop() override;

    public:
        MainLoop();
};

#endif