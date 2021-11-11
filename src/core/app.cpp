#include "core/app.hpp"

Application::Application()
{
    this->run();
}

/***
 * EVENTS
 *
 */

void Application::eventAdd()
{
    this->Super::m_ev_manager.addEventCallback(sf::Event::Closed, [&](sfev::CstEv){
        this->Super::m_window.close();
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::Escape, [&](sfev::CstEv){
        this->Super::m_window.close();
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::S, [&](sfev::CstEv){
        this->m_ev_state.speed = (this->m_ev_state.speed + 1) % 3;
        switch(this->m_ev_state.speed){
            case 0:
                this->Super::m_window.setFramerateLimit(Conf::FRAMERATE);
                break;
            case 1:
                this->Super::m_window.setFramerateLimit(0);
                this->Super::m_window.setVerticalSyncEnabled(true);
                break;
            case 2:
                this->Super::m_window.setVerticalSyncEnabled(false);
            default:
                break;
        }
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::D, [&](sfev::CstEv){
        this->m_ev_state.debug = !this->m_ev_state.debug;
    });

    this->Super::m_ev_manager.addKeyPressedCallback(sf::Keyboard::Left, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::LEFT;
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::Left, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::NOOP;
    });

    this->Super::m_ev_manager.addKeyPressedCallback(sf::Keyboard::Right, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::RIGHT;
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::Right, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::NOOP;
    });

    this->Super::m_ev_manager.addKeyPressedCallback(sf::Keyboard::Up, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::UP;
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::Up, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::NOOP;
    });

    this->Super::m_ev_manager.addKeyPressedCallback(sf::Keyboard::Down, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::DOWN;
    });

    this->Super::m_ev_manager.addKeyReleasedCallback(sf::Keyboard::Down, [&](sfev::CstEv){
        this->m_ev_state.action = Conf::NOOP;
    });
}

/***
 * DRAW
 *
 */

void Application::drawInit()
{
    this->Super::m_renderer.initHCycle(this->m_agent.getHCycle());
}

void Application::drawLoop()
{
    this->Super::m_renderer.renderHCycle(this->m_ev_state.debug);
    this->Super::m_renderer.renderApple(this->m_apple.getPos());
    this->Super::m_renderer.renderSnake(this->m_snake.getBody());
}

/***
 * MAIN
 *
 */

int Application::getAction()
{
    switch (Conf::MODE){
        case Conf::Mode::AGENT_PHC:
            return this->m_agent.getActionPHC(this->m_snake.getBody()[0],
                                                this->m_snake.getBody()[this->m_snake.getBody().size() - 1],
                                                this->m_apple.getPos()
            );
        case Conf::Mode::AGENT_HC:
            return this->m_agent.getActionHC(this->m_snake.getBody()[0]);
        case Conf::Mode::PLAYER:
            return this->m_ev_state.action;
        default:
            return 0;
    }
}

void Application::mainInit()
{
}

void Application::mainLoop()
{
    this->m_snake.act(this->getAction());

    this->m_snake.updatePos();
    if(this->m_snake.isEat(this->m_apple.getPos())){
        this->m_snake.updateSize();
        this->m_apple.updatePos(this->m_snake.getBody());
    }
    this->m_snake.updateBody();

    if(this->m_snake.isHit()){
        this->Super::waitExit();
    }
}