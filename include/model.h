#ifndef _MODEL_H
#define _MODEL_H

#include "agent.h"
#include "snake.h"

struct Model{
    Agent m_agent;
    Apple m_apple;
    Snake m_snake;

    Model(int cols, int rows)
        : m_agent(cols, rows), 
          m_apple(cols, rows), 
          m_snake(cols, rows) 
        {}
};

#endif