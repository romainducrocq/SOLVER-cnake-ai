#ifndef _EV_STATE_HPP
#define _EV_STATE_HPP

#include "../utils/config.hpp"

#include "ev_mngr.hpp"

class EventState
{
    private:
        int m_speed = 0;
        bool m_is_debug = false;
        Conf::Action m_action = Conf::NOOP;

    public:
        EventState();

        void initEventCallbacks(sfev::EventManager& ev_manager);

        bool getIsDebug() const;

        Conf::Action getActionPlay() const;
};

#endif