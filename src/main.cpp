#include "../include/controller.h"

Game::Game() 
    : m_model(COLS, ROWS), m_view(NAME, COLS, ROWS, ZOOM, WAIT) {} 

int Game::get_action(){
    return this->m_view.get_input();
}

void Game::act(int action){
    switch(action){
    case 1: //left
        this->m_model.snake.update_dir(Vector2i(-1, 0));
        break;
    case 2: //right
        this->m_model.snake.update_dir(Vector2i(1, 0));        
        break;
    case 3: //up
        this->m_model.snake.update_dir(Vector2i(0, -1));
        break;
    case 4: //down
        this->m_model.snake.update_dir(Vector2i(0, 1));
        break;
    default:
        break;
    }
}

void Game::loop(){
    do{
        if(this->m_model.snake.is_hit()){
            this->m_model.snake = Snake(COLS, ROWS);
        }
        this->act(this->get_action());
        this->m_model.snake.update_body();
        this->m_model.snake.update_pos();
        if(this->m_model.snake.is_eat(this->m_model.apple.get_pos())){
            this->m_model.apple.update_pos();
            this->m_model.snake.update_size();
        }
    }while(this->m_view.loop(this->m_model));
}

int main(){

    Game game;
    game.loop();

}