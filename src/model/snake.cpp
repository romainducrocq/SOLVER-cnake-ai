#include "../../include/model/snake.hpp"

Apple::Apple()
{
    this->update_pos({ 0 });
}

int Apple::get_pos() const
{
    return this->m_pos;
}

void Apple::update_pos(const std::vector<int>& body)
{
    do{
        this->m_pos = std::rand() % (Conf::COLS * Conf::ROWS);
    }while(!this->is_valid_pos(body));
}

bool Apple::is_valid_pos(const std::vector<int>& body)
{
    for(size_t i = 0; i < body.size(); i++){
        if(body[i] == this->m_pos){
            return false;
        }
    }
    return true;
}

Snake::Snake()
{
    this->update_size();
}

const std::vector<int>& Snake::get_body() const
{
    return this->m_body;
}

void Snake::update_size()
{
    this->m_body.push_back(this->m_pos.x + this->m_pos.y * Conf::COLS);
}

void Snake::update_body()
{
    for(size_t i = this->m_body.size() - 1; i > 0; i--){
        this->m_body[i] = this->m_body[i-1];
    }
    this->m_body[0] = this->m_pos.x + this->m_pos.y * Conf::COLS;
}

void Snake::update_pos()
{
    this->m_pos.x += this->m_dir.x;
    this->m_pos.y += this->m_dir.y;
}

void Snake::update_dir(Vector2i dir)
{
    if(!(this->m_dir.x == -1 * dir.x && this->m_dir.y == -1 * dir.y)){
        this->m_dir.x = dir.x;
        this->m_dir.y = dir.y;
    }
}

bool Snake::is_eat(int pos) const
{
    return (pos == this->m_pos.x + this->m_pos.y * Conf::COLS);
}

bool Snake::is_hit() const
{
    if(this->m_pos.x >= Conf::COLS || this->m_pos.x < 0){
        return true;
    }
    if(this->m_pos.y >= Conf::ROWS || this->m_pos.y < 0){
        return true;
    }

    for(size_t i = 1; i < this->m_body.size(); i++){
        if(this->m_body[i] == this->m_pos.x + this->m_pos.y * Conf::COLS){
            return true;
        }
    }
    return false; 
}
