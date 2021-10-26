#include "../include/agent.h"

Agent::Agent(int cols, int rows)
    : Super(cols, rows){

    this->m_unordered_hcycle = new int[this->Super::m_cols * this->Super::m_rows];
    for(int i = 0; i < this->Super::m_cols * this->Super::m_rows; i++){
        this->m_unordered_hcycle[this->Super::m_hcycle[i]] = i;
    }

    /* // debug
    for(int i = 0; i < this->Super::m_rows; i++){
        for(int j = 0; j < this->Super::m_cols; j++){
            if(this->m_unordered_hcycle[i * this->Super::m_cols + j] < 10){ std::cout << "   "; }
            else if(this->m_unordered_hcycle[i * this->Super::m_cols + j] < 100){ std::cout << "  "; }
            else if(this->m_unordered_hcycle[i * this->Super::m_cols + j] < 1000){ std::cout << " "; }
            std::cout <<  this->m_unordered_hcycle[i * this->Super::m_cols + j] << " ";
        }
        std::cout << "\n";
    }
    */
}

Agent::~Agent(){
    delete[] this->m_unordered_hcycle;
}

int Agent::get_action(int pos){
    this->m_count = (this->m_count + 1) % (this->Super::m_cols * this->Super::m_rows);

    if(this->Super::m_hcycle[m_count] == pos - 1){ return 1; }                        // left
    else if(this->Super::m_hcycle[m_count] == pos + 1){ return 2; }                   // right
    else if(this->Super::m_hcycle[m_count] == pos - this->Super::m_cols){ return 3; } // up
    else if(this->Super::m_hcycle[m_count] == pos + this->Super::m_cols){ return 4; } // down
    
    return 0;
}

void perturbated_hcycle(int pos_s, int pos_a){
    // int dir;
}