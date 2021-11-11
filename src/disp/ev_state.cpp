#include "disp/ev_state.hpp"

EventState::EventState()
{}

void EventState::initEventCallbacks(sfev::EventManager& ev_manager)
{
    ev_manager.addEventCallback(sf::Event::Closed, [&](sfev::CstEv){
        ev_manager.getWindow().close();
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::Escape, [&](sfev::CstEv){
        ev_manager.getWindow().close();
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::S, [&](sfev::CstEv){
        this->m_speed = (this->m_speed + 1) % 3;
        switch(this->m_speed){
            case 0:
                ev_manager.getWindow().setFramerateLimit(Conf::FRAMERATE);
                break;
            case 1:
                ev_manager.getWindow().setFramerateLimit(0);
                ev_manager.getWindow().setVerticalSyncEnabled(true);
                break;
            case 2:
                ev_manager.getWindow().setVerticalSyncEnabled(false);
            default:
                break;
        }
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::D, [&](sfev::CstEv){
        this->m_is_debug = !this->m_is_debug;
    });

    ev_manager.addKeyPressedCallback(sf::Keyboard::Left, [&](sfev::CstEv){
        this->m_action = Conf::LEFT;
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::Left, [&](sfev::CstEv){
        this->m_action = Conf::NOOP;
    });

    ev_manager.addKeyPressedCallback(sf::Keyboard::Right, [&](sfev::CstEv){
        this->m_action = Conf::RIGHT;
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::Right, [&](sfev::CstEv){
        this->m_action = Conf::NOOP;
    });

    ev_manager.addKeyPressedCallback(sf::Keyboard::Up, [&](sfev::CstEv){
        this->m_action = Conf::UP;
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::Up, [&](sfev::CstEv){
        this->m_action = Conf::NOOP;
    });

    ev_manager.addKeyPressedCallback(sf::Keyboard::Down, [&](sfev::CstEv){
        this->m_action = Conf::DOWN;
    });

    ev_manager.addKeyReleasedCallback(sf::Keyboard::Down, [&](sfev::CstEv){
        this->m_action = Conf::NOOP;
    });
}

bool EventState::getIsDebug() const
{
    return this->m_is_debug;
}

Conf::Action EventState::getActionPlay() const
{
    return this->m_action;
}