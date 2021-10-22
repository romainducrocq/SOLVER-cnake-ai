#ifndef _AGENT_H
#define _AGENT_H

#include "hcycle.h"

class Agent{
    private:
        int m_cols, m_rows;

    public:
        HamiltonianCycle m_hcycle;

    public:
        Agent(int cols, int rows);
};

#endif