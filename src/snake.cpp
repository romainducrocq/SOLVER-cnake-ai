#include "../include/snake.h"

Apple::Apple(int cols, int rows)
    : m_mat(Vector2i(cols, rows)){
    this->update_pos();
}

Vector2i Apple::get_pos() const { return this->m_pos; }

void Apple::update_pos(){
    this->m_pos.x = std::rand() % this->m_mat.x;
    this->m_pos.y = std::rand() % this->m_mat.y;
}

Snake::Snake(int cols, int rows)
    : m_mat(Vector2i(cols, rows)){
    this->update_size();
}

Vector2i Snake::get_pos(int i) const { return this->m_body[i]; }

size_t Snake::get_size() const{ return this->m_body.size(); }

void Snake::update_size(){
    this->m_body.push_back(Vector2i(this->m_pos.x, this->m_pos.y));
}

void Snake::update_body(){
    for(size_t i = 0; i < this->m_body.size() - 1; i++){
        this->m_body[i] = this->m_body[i+1];
    }
    this->m_body[this->m_body.size() - 1] = Vector2i(this->m_pos.x, this->m_pos.y);
}

void Snake::update_pos(){
    this->m_pos.x += this->m_dir.x;
    this->m_pos.y += this->m_dir.y;
}

void Snake::update_dir(Vector2i dir){
    if(!(this->m_dir.x == -1 * dir.x && this->m_dir.y == -1 * dir.y)){
        this->m_dir.x = dir.x;
        this->m_dir.y = dir.y;
    }
}

bool Snake::is_eat(Vector2i pos) const {
    return (this->m_pos.x == pos.x && this->m_pos.y == pos.y);
}

bool Snake::is_hit() const {
    if(this->m_pos.x >= this->m_mat.x || this->m_pos.x < 0){
        return true;
    }
    if(this->m_pos.y >= this->m_mat.y || this->m_pos.y < 0){
        return true;
    }

    for(size_t i = 0; i < this->m_body.size() - 1; i++){
        if(this->m_body[i].x == this->m_pos.x && this->m_body[i].y == this->m_pos.y){
            return true;
        }
    }
    return false; 
}
