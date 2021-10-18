#ifndef _MODEL_H
#define _MODEL_H

#include "utils.h"
#include "snake.h"

struct Model{
    Mode m_mode;
    
    Apple m_apple;
    Snake m_snake;

    Model(Mode mode, int cols, int rows)
        : m_mode(mode), m_apple(cols, rows), m_snake(cols, rows) {}
};

#endif