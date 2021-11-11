#include "core/app.hpp"

Application::Application()
{
    this->setup();
    this->loop();
}

/***
 * VIEW
 *
 */

void Application::viewSetup()
{
    this->Super::m_ev_state.initEventCallbacks(this->Super::m_ev_mngr);
    this->Super::m_renderer.initShapeHCycle(this->m_agent.getHCycle());
}

void Application::viewLoop()
{
    this->Super::m_renderer.renderShapeHCycle(this->Super::m_ev_state.getIsDebug());
    this->Super::m_renderer.renderShapeApple(this->m_apple.getPos());
    this->Super::m_renderer.renderShapeSnake(this->m_snake.getBody());
}

/***
 * CONTROL
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
            return this->Super::m_ev_state.getActionPlay();
        default:
            return 0;
    }
}

void Application::ctrlSetup()
{

}

void Application::ctrlLoop()
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