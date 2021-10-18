#include "../include/snake.h"

Apple::Apple(int cols, int rows)
    : m_mat(Vector2i(cols, rows)){
    this->update_pos({ Vector2i(0, 0) });
}

Vector2i Apple::get_pos() const { return this->m_pos; }

void Apple::update_pos(const std::vector<Vector2i>& body){
    do{
        this->m_pos.x = std::rand() % this->m_mat.x;
        this->m_pos.y = std::rand() % this->m_mat.y;
    }while(!this->is_valid_pos(body));
}

bool Apple::is_valid_pos(const std::vector<Vector2i>& body){
    for(size_t i = 0; i < body.size(); i++){
        if(this->m_pos.x == body[i].x && this->m_pos.y == body[i].y){
            return false;
        }
    }
    return true;
}

Snake::Snake(int cols, int rows)
    : m_mat(Vector2i(cols, rows)){
    this->update_size();
}

const std::vector<Vector2i>& Snake::get_body() const { return this->m_body; }

void Snake::update_size(){
    this->m_body.push_back(Vector2i(this->m_pos.x, this->m_pos.y));
}

void Snake::update_body(){
    for(size_t i = this->m_body.size() - 1; i > 0; i--){
        this->m_body[i] = this->m_body[i-1];
    }
    this->m_body[0] = Vector2i(this->m_pos.x, this->m_pos.y);
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

    for(size_t i = 1; i < this->m_body.size(); i++){
        if(this->m_body[i].x == this->m_pos.x && this->m_body[i].y == this->m_pos.y){
            return true;
        }
    }
    return false; 
}
