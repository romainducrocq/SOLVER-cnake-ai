#ifndef _MODEL_H
#define _MODEL_H

#include "hamiltonian_cycle.h"

#include "snake.h"

struct Model{
    HamiltonianCycle m_hc;

    Apple m_apple;
    Snake m_snake;

    Model(int cols, int rows)
        : m_hc(cols, rows), 
        
          m_apple(cols, rows), 
          m_snake(cols, rows) 
        {}
};

#endif