#include "../include/agent.h"

Agent::Agent(int cols, int rows)
    : m_cols(cols), m_rows(rows), m_hcycle(cols, rows){}

int Agent::get_action(int pos){
    this->m_count = (this->m_count + 1) % (this->m_cols * this->m_rows);

    if(this->m_hcycle.get_hcycle()[m_count] == pos - 1){ return 1; }                 // left
    else if(this->m_hcycle.get_hcycle()[m_count] == pos + 1){ return 2; }            // right
    else if(this->m_hcycle.get_hcycle()[m_count] == pos - this->m_cols){ return 3; } // up
    else if(this->m_hcycle.get_hcycle()[m_count] == pos + this->m_cols){ return 4; } // down
    
    return 0;
}