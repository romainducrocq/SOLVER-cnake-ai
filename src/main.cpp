#include "../include/controller.h"

Game::Game(Mode mode) 
    : m_model(mode, COLS, ROWS), m_view(NAME, COLS, ROWS, ZOOM, WAIT) {
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
    switch (this->m_model.m_mode){
    case Mode::AGENT:
        return 0;
    case Mode::PLAYER:
        return this->m_view.get_input();
    default:
        return 0;
    }
}

void Game::loop(){
    while(true){
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
            this->m_view.wait_exit();
            break;
        }

        if(!(this->m_view.loop(this->m_model))){
            break;
        }
    }
}

int main(){
    std::srand(time(nullptr));
    Game game(Mode::PLAYER);
}