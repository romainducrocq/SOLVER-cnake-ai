#include "../include/controller.h"

Game::Game(Mode mode) 
    : Super(NAME, WAIT, COLS, ROWS, ZOOM), m_model(COLS, ROWS), m_mode(mode){
        this->setup();
        this->loop();
    } 

void Game::act(int action){
    switch(action){
    case 1: //left
        this->m_model.m_snake.update_dir(Vector2i(-1, 0));
        break;
    case 2: //right
        this->m_model.m_snake.update_dir(Vector2i(1, 0));        
        break;
    case 3: //up
        this->m_model.m_snake.update_dir(Vector2i(0, -1));
        break;
    case 4: //down
        this->m_model.m_snake.update_dir(Vector2i(0, 1));
        break;
    default:
        break;
    }
}

int Game::get_action(){
    switch (this->m_mode){
    case Mode::AGENT:
        return 0;
    case Mode::PLAYER:
        return this->Super::get_ctrl_input();
    default:
        return 0;
    }
}

/***
 * VIEW
 * 
 */

void Game::view_setup(){
    this->Super::circle_shape_apple = sf::CircleShape(Super::m_zoom / 2);
    this->Super::rectangle_shapes_snake.push_back(sf::RectangleShape(sf::Vector2f(Super::m_zoom, Super::m_zoom)));
}

void Game::view_loop(){
    this->Super::draw_circle_shape(this->Super::circle_shape_apple, 
                                   this->m_model.m_apple.get_pos().x * Super::m_zoom, 
                                   this->m_model.m_apple.get_pos().y * Super::m_zoom, 
                                   1, sf::Color(255, 0, 100), sf::Color(0, 0, 0));

    while(this->m_model.m_snake.get_body().size() > this->Super::rectangle_shapes_snake.size()){
        this->Super::rectangle_shapes_snake.push_back(sf::RectangleShape(sf::Vector2f(Super::m_zoom, Super::m_zoom)));
    }

    for(size_t i = 0; i < this->m_model.m_snake.get_body().size(); i++){
            this->draw_rectangle_shape(this->Super::rectangle_shapes_snake[i], 
                                       this->m_model.m_snake.get_body()[i].x * Super::m_zoom, 
                                       this->m_model.m_snake.get_body()[i].y * Super::m_zoom,
                                       1, sf::Color(58, 191, 39), sf::Color(0, 0, 0));
    }
}

/***
 * CONTROLLER
 * 
 */

void Game::ctrl_setup(){

}

void Game::ctrl_loop(){
    this->act(this->get_action());

    this->m_model.m_snake.update_pos();
    if(this->m_model.m_snake.is_eat(
        this->m_model.m_apple.get_pos()
    )){
        this->m_model.m_snake.update_size();
        this->m_model.m_apple.update_pos(
            this->m_model.m_snake.get_body()
        );
    }
    this->m_model.m_snake.update_body();
    
    if(this->m_model.m_snake.is_hit()){
        this->Super::wait_exit();
    }
}

/***
 * 
 */

int main(){
    std::srand(time(nullptr));

    /***
     * 
     * 
     */

    HamiltonianCycle hc(COLS, ROWS);
    hc.debug();
    return 0;

    /***
     * 
     * 
     */

    Game game(Mode::PLAYER);
}