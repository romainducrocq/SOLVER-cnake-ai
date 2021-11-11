#ifndef _AGENT_HPP
#define _AGENT_HPP

#include "utils/config.hpp"

#include "hcycle.hpp"

class Agent: public HamiltonianCycle
{
    private:
        typedef HamiltonianCycle Super;

        int m_count = 0;

        int* m_unordered_hcycle;

    public:
        Agent();
        
        ~Agent();

        Conf::Action getActionHC(int pos);

        Conf::Action getActionPHC(int pos_h, int pos_t, int pos_a) const;
};

#endif