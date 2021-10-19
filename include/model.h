#ifndef _MODEL_H
#define _MODEL_H

#include "utils.h"
#include "snake.h"

struct Model{
    Apple m_apple;
    Snake m_snake;

    Model(int cols, int rows)
        : m_apple(cols, rows), m_snake(cols, rows) {}
};

#endif