#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "utils.h"
#include "model.h"
#include "view.h"

class Game{
    private:
        Model m_model;
        View m_view;

    public:
        Game();

        int get_action_play();

        void act(int action);

        void loop();
};

#endif