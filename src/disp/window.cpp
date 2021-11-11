#include "disp/window.hpp"

Window::Window()
    : m_renderer(this->m_window)
    , m_ev_mngr(this->m_window, true)
{
    sf::ContextSettings options;
    options.antialiasingLevel = 0;

    this->m_window.create(sf::VideoMode(Conf::WIN_W, Conf::WIN_H, 32), Conf::NAME, sf::Style::Default, options);
    this->m_window.setVerticalSyncEnabled(false);

    this->m_window.setFramerateLimit(Conf::FRAMERATE);
}

void Window::setup()
{
    this->ctrlSetup();
    this->viewSetup();
}

void Window::loop()
{
    while(this->m_window.isOpen()){
        this->m_ev_mngr.processEvents();

        this->ctrlLoop();

        this->m_window.clear(sf::Color(Conf::BG_COL[0], Conf::BG_COL[1], Conf::BG_COL[2]));
        this->viewLoop();
        this->m_window.display();
    }
}

void Window::waitExit()
{
    while(this->m_window.isOpen()){
        sf::Event event;
        while(this->m_window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                this->m_window.close();
        }
    }
}
