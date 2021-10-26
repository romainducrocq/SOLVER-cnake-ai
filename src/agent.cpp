#include "../include/agent.h"

Agent::Agent(int cols, int rows)
    : Super(cols, rows){}

int Agent::get_action(int pos){
    this->m_count = (this->m_count + 1) % (this->Super::m_cols * this->Super::m_rows);

    if(this->Super::m_hcycle[m_count] == pos - 1){ return 1; }                        // left
    else if(this->Super::m_hcycle[m_count] == pos + 1){ return 2; }                   // right
    else if(this->Super::m_hcycle[m_count] == pos - this->Super::m_cols){ return 3; } // up
    else if(this->Super::m_hcycle[m_count] == pos + this->Super::m_cols){ return 4; } // down
    
    return 0;
}