#include "../../include/controller/main_loop.hpp"

MainLoop::MainLoop()
{
    this->setup();
    this->loop();
}

void MainLoop::act(int action)
{
    switch(action){
        case Conf::Action::LEFT:  // left
            this->m_snake.update_dir(Vector2i(-1, 0));
            break;
        case Conf::Action::RIGHT: // right
            this->m_snake.update_dir(Vector2i(1, 0));
            break;
        case Conf::Action::UP:    // up
            this->m_snake.update_dir(Vector2i(0, -1));
            break;
        case Conf::Action::DOWN:  // down
            this->m_snake.update_dir(Vector2i(0, 1));
            break;
        default:
            break;
    }
}

int MainLoop::get_action()
{
    switch (Conf::MODE){
        case Conf::Mode::AGENT_PHC:
            return this->m_agent.get_action_phc(
                    this->m_snake.get_body()[0],
                    this->m_snake.get_body()[
                            this->m_snake.get_body().size() - 1],
                    this->m_apple.get_pos()
            );
        case Conf::Mode::AGENT_HC:
            return this->m_agent.get_action_hc(
                    this->m_snake.get_body()[0]
            );
        case Conf::Mode::PLAYER:
            return this->Super::get_ctrl_input();
        default:
            return 0;
    }
}

/***
 * VIEW
 *
 */

void MainLoop::view_setup()
{
    this->Super::m_convex_shape_hcycle.setPointCount(Conf::COLS * Conf::ROWS);
    for(int i = 0; i < Conf::COLS * Conf::ROWS; i++){
        this->Super::m_convex_shape_hcycle.setPoint(i, sf::Vector2f(
                (this->m_agent.get_hcycle()[i] % Conf::COLS) * Conf::ZOOM,
                (this->m_agent.get_hcycle()[i] / Conf::COLS) * Conf::ZOOM
        ));
    }
}

void MainLoop::view_loop()
{
    if(this->Super::is_debug_view()){
        // draw hamiltonian cycle
        this->Super::draw_convex_shape(this->Super::m_convex_shape_hcycle,
                                       Conf::ZOOM / 2,
                                       Conf::ZOOM / 2,
                                       1, sf::Color::Transparent, sf::Color(220, 220, 220));
    }

    // draw apple
    this->Super::draw_circle_shape(Conf::ZOOM * 0.4f,
                                   (this->m_apple.get_pos() % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                   (this->m_apple.get_pos() / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                   0, sf::Color(255, 0, 100), sf::Color::Transparent, &this->Super::m_circle_shape);

    // draw snake
    size_t i = 1;
    while (i < this->m_snake.get_body().size()){

        size_t j = 0;
        while((i + j) < this->m_snake.get_body().size() &&
              this->m_snake.get_body()[i] - this->m_snake.get_body()[i - 1] ==
              this->m_snake.get_body()[i + j + 1] - this->m_snake.get_body()[i + j])
        { j++; }

        this->Super::draw_circle_shape(Conf::ZOOM * 0.4f,
                                       (this->m_snake.get_body()[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                       (this->m_snake.get_body()[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                       0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_circle_shape);

        if(this->m_snake.get_body()[i] - this->m_snake.get_body()[i - 1] == 1){                          // left
            this->Super::draw_rectangle_shape(((this->m_snake.get_body()[i + j] % Conf::COLS) -
                                               (this->m_snake.get_body()[i - 1] % Conf::COLS)) * Conf::ZOOM,
                                              Conf::ZOOM * 0.8f,
                                              (this->m_snake.get_body()[i - 1] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                              (this->m_snake.get_body()[i - 1] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);

        }else if(this->m_snake.get_body()[i] - this->m_snake.get_body()[i - 1] == -1){                   // right
            this->Super::draw_rectangle_shape(((this->m_snake.get_body()[i - 1] % Conf::COLS) -
                                               (this->m_snake.get_body()[i + j] % Conf::COLS)) * Conf::ZOOM,
                                              Conf::ZOOM * 0.8f,
                                              (this->m_snake.get_body()[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                              (this->m_snake.get_body()[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);

        }else if(this->m_snake.get_body()[i] - this->m_snake.get_body()[i - 1] == Conf::COLS){  // up
            this->Super::draw_rectangle_shape(Conf::ZOOM * 0.8f,
                                              ((this->m_snake.get_body()[i + j] / Conf::COLS) -
                                               (this->m_snake.get_body()[i - 1] / Conf::COLS)) * Conf::ZOOM,
                                              (this->m_snake.get_body()[i - 1] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                              (this->m_snake.get_body()[i - 1] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);

        }else if(this->m_snake.get_body()[i] - this->m_snake.get_body()[i - 1] == -Conf::COLS){ // down
            this->Super::draw_rectangle_shape(Conf::ZOOM * 0.8f,
                                              ((this->m_snake.get_body()[i - 1] / Conf::COLS) -
                                               (this->m_snake.get_body()[i + j] / Conf::COLS)) * Conf::ZOOM,
                                              (this->m_snake.get_body()[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                              (this->m_snake.get_body()[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);

        }

        i += (j + 1);
    }

    this->Super::draw_circle_shape(Conf::ZOOM * 0.4f,
                                   (this->m_snake.get_body()[0] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                   (this->m_snake.get_body()[0] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                   0, sf::Color(0, 100, 255), sf::Color::Transparent, &this->Super::m_circle_shape);
}

/***
 * CONTROLLER
 *
 */

void MainLoop::ctrl_setup()
{

}

void MainLoop::ctrl_loop()
{
    this->act(this->get_action());

    this->m_snake.update_pos();
    if(this->m_snake.is_eat(
            this->m_apple.get_pos()
    )){
        this->m_snake.update_size();
        this->m_apple.update_pos(
                this->m_snake.get_body()
        );
    }
    this->m_snake.update_body();

    if(this->m_snake.is_hit()){
        this->Super::wait_exit();
    }
}