#ifndef _MODEL_H
#define _MODEL_H

#include "hcycle.h"

#include "snake.h"

struct Model{
    HamiltonianCycle m_hcycle;

    Apple m_apple;
    Snake m_snake;

    Model(int cols, int rows)
        : m_hcycle(cols, rows), 

          m_apple(cols, rows), 
          m_snake(cols, rows) 
        {}
};

#endif