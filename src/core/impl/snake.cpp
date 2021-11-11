#include "core/impl/snake.hpp"

Apple::Apple()
{
    this->updatePos({ 0 });
}

int Apple::getPos() const
{
    return this->m_pos;
}

void Apple::updatePos(const std::vector<int>& body)
{
    do{
        this->m_pos = std::rand() % (Conf::COLS * Conf::ROWS);
    }while(!this->isValidPos(body));
}

bool Apple::isValidPos(const std::vector<int>& body)
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
    this->updateSize();
}

const std::vector<int>& Snake::getBody() const
{
    return this->m_body;
}

void Snake::updateSize()
{
    this->m_body.push_back(this->m_pos.x + this->m_pos.y * Conf::COLS);
}

void Snake::updateBody()
{
    for(size_t i = this->m_body.size() - 1; i > 0; i--){
        this->m_body[i] = this->m_body[i-1];
    }
    this->m_body[0] = this->m_pos.x + this->m_pos.y * Conf::COLS;
}

void Snake::updatePos()
{
    this->m_pos.x += this->m_dir.x;
    this->m_pos.y += this->m_dir.y;
}

void Snake::updateDir(Vector2i dir)
{
    if(!(this->m_dir.x == -1 * dir.x && this->m_dir.y == -1 * dir.y)){
        this->m_dir.x = dir.x;
        this->m_dir.y = dir.y;
    }
}

bool Snake::isEat(int pos) const
{
    return (pos == this->m_pos.x + this->m_pos.y * Conf::COLS);
}

bool Snake::isHit() const
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

void Snake::act(int action)
{
    switch(action){
        case Conf::Action::LEFT:  // left
            this->updateDir(Vector2i(-1, 0));
            break;
        case Conf::Action::RIGHT: // right
            this->updateDir(Vector2i(1, 0));
            break;
        case Conf::Action::UP:    // up
            this->updateDir(Vector2i(0, -1));
            break;
        case Conf::Action::DOWN:  // down
            this->updateDir(Vector2i(0, 1));
            break;
        default:
            break;
    }
}
