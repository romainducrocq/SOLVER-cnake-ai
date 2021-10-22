#ifndef _AGENT_H
#define _AGENT_H

#include "hcycle.h"

class Agent{
    private:
        int m_cols, m_rows, m_count = 0;

    public:
        HamiltonianCycle m_hcycle;

    public:
        Agent(int cols, int rows);

        int get_action(int pos);
};

#endif