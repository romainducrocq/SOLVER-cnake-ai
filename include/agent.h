#ifndef _AGENT_H
#define _AGENT_H

#include "hcycle.h"

class Agent: public HamiltonianCycle{
    private:
        typedef HamiltonianCycle Super;

        int m_count = 0;

    public:
        Agent(int cols, int rows);

        int get_action(int pos);
};

#endif