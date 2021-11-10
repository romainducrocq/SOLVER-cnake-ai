#ifndef _AGENT_H
#define _AGENT_H

#include "hcycle.hpp"

#include "../utils/config.hpp"

class Agent: public HamiltonianCycle
{
    private:
        typedef HamiltonianCycle Super;

        int m_count = 0;

        int* m_unordered_hcycle;

    public:
        Agent();
        
        ~Agent();

        Conf::Action get_action_hc(int pos);

        Conf::Action get_action_phc(int pos_h, int pos_t, int pos_a);
};

#endif