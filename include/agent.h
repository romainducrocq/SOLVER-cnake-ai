#ifndef _AGENT_H
#define _AGENT_H

#include "hcycle.h"

class Agent: public HamiltonianCycle{
    private:
        typedef HamiltonianCycle Super;

        int m_count = 0;

        int* m_unordered_hcycle;

    public:
        Agent(int cols, int rows);
        
        ~Agent();

        int get_action(int pos);

        void perturbated_hcycle(int pos_s, int pos_a);
};

#endif