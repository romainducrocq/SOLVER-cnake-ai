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

        int get_action_hc(int pos);

        int get_action_phc(int pos_h, int pos_t, int pos_a);
};

#endif