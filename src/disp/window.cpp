#include "disp/window.hpp"

Window::Window()
    : m_ev_manager(this->m_window, true)
    , m_renderer(this->m_window)
{
    sf::ContextSettings options;
    options.antialiasingLevel = Conf::ANTIALIAS;

    this->m_window.create(sf::VideoMode(Conf::WIN_W, Conf::WIN_H, 32), Conf::NAME, sf::Style::Default, options);
    this->m_window.setVerticalSyncEnabled(false);

    this->m_window.setFramerateLimit(Conf::FRAMERATE);
}

void Window::run()
{
    this->init();
    this->loop();
}

void Window::init()
{
    this->eventAdd();
    this->mainInit();
    this->drawInit();
}

void Window::loop()
{
    while(this->m_window.isOpen()){
        this->m_ev_manager.processEvents();

        this->mainLoop();

        this->m_window.clear(sf::Color(Conf::BG_COL[0], Conf::BG_COL[1], Conf::BG_COL[2]));
        this->drawLoop();
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
