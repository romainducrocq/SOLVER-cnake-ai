#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "utils.h"
#include "model.h"
#include "view.h"

class Game: public View{
    private:
        typedef View Super;
        Model m_model;
        
        Mode m_mode;

    private:
        int get_action();

        void act(int action);

        void view_setup() override;

        void view_loop() override;

        void ctrl_setup() override;
        
        void ctrl_loop() override;

    public:
        Game(Mode mode);
};

#endif