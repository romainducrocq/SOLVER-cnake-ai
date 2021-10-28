#include "../include/agent.h"

Agent::Agent(int cols, int rows)
    : Super(cols, rows){

    this->m_unordered_hcycle = new int[this->Super::m_cols * this->Super::m_rows];
    for(int i = 0; i < this->Super::m_cols * this->Super::m_rows; i++){
        this->m_unordered_hcycle[this->Super::m_hcycle[i]] = i;
    }
}

Agent::~Agent(){
    delete[] this->m_unordered_hcycle;
}

/***
 * HAMILTONIAN CYCLE
 * 
 */

int Agent::get_action_hc(int pos){
    this->m_count = (this->m_count + 1) % (this->Super::m_cols * this->Super::m_rows);

    if(this->Super::m_hcycle[m_count] == pos - 1){ return 1; }                        // left
    else if(this->Super::m_hcycle[m_count] == pos + 1){ return 2; }                   // right
    else if(this->Super::m_hcycle[m_count] == pos - this->Super::m_cols){ return 3; } // up
    else if(this->Super::m_hcycle[m_count] == pos + this->Super::m_cols){ return 4; } // down
    
    return 0;
}

/***
 * PERTURBATED HAMILTONIAN CYCLE
 * 
 */

int Agent::get_action_phc(int pos_h, int pos_t, int pos_a){
    int dir = 0, sc = 0;

    if(pos_h % this->Super::m_cols != 0 && 
       !(this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t] &&
         this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h - 1]) && 
       !(this->m_unordered_hcycle[pos_h - 1] < this->m_unordered_hcycle[pos_h] &&
         this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t]) &&
       !(this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h - 1] &&
         this->m_unordered_hcycle[pos_h - 1] < this->m_unordered_hcycle[pos_h])
    ){ // left
        if(
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - 1] &&
            this->m_unordered_hcycle[pos_h - 1] <= this->m_unordered_hcycle[pos_a] &&
            sc < this->m_unordered_hcycle[pos_h - 1] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - 1] - this->m_unordered_hcycle[pos_h];
            dir = 1;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - 1] &&
            sc < this->m_unordered_hcycle[pos_h - 1] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - 1] - this->m_unordered_hcycle[pos_h];
            dir = 1;

        }else if(
            this->m_unordered_hcycle[pos_h - 1] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - 1]
        ){
            sc = (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - 1];
            dir = 1;  

        }
    }

    if((pos_h + 1) % this->Super::m_cols != 0 && 
       !(this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t] &&
         this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h + 1]) && 
       !(this->m_unordered_hcycle[pos_h + 1] < this->m_unordered_hcycle[pos_h] &&
         this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t]) &&
       !(this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h + 1] &&
         this->m_unordered_hcycle[pos_h + 1] < this->m_unordered_hcycle[pos_h])
    ){ // right
        if(
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + 1] &&
            this->m_unordered_hcycle[pos_h + 1] <= this->m_unordered_hcycle[pos_a] &&
            sc < this->m_unordered_hcycle[pos_h + 1] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h + 1] - this->m_unordered_hcycle[pos_h];
            dir = 2;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + 1] &&
            sc < this->m_unordered_hcycle[pos_h + 1] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h + 1] - this->m_unordered_hcycle[pos_h];
            dir = 2;

        }else if(
            this->m_unordered_hcycle[pos_h + 1] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + 1]
        ){
            sc = (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + 1];
            dir = 2;  

        }
    }
    
    if(pos_h >= this->Super::m_cols && 
       !(this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t] &&
         this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h - this->Super::m_cols]) && 
       !(this->m_unordered_hcycle[pos_h - this->Super::m_cols] < this->m_unordered_hcycle[pos_h] &&
         this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t]) &&
       !(this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h - this->Super::m_cols] &&
         this->m_unordered_hcycle[pos_h - this->Super::m_cols] < this->m_unordered_hcycle[pos_h])
    ){ // up
        if(
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - this->Super::m_cols] &&
            this->m_unordered_hcycle[pos_h - this->Super::m_cols] <= this->m_unordered_hcycle[pos_a] &&
            sc < this->m_unordered_hcycle[pos_h - this->Super::m_cols] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - this->Super::m_cols] - this->m_unordered_hcycle[pos_h];
            dir = 3;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - this->Super::m_cols] &&
            sc < this->m_unordered_hcycle[pos_h - this->Super::m_cols] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - this->Super::m_cols] - this->m_unordered_hcycle[pos_h];
            dir = 3;

        }else if(
            this->m_unordered_hcycle[pos_h - this->Super::m_cols] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - this->Super::m_cols]
        ){
            sc = (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - this->Super::m_cols];
            dir = 3;  

        }
    }
    
    if(pos_h < (this->Super::m_rows - 1) * this->Super::m_cols && 
       !(this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t] &&
         this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h + this->Super::m_cols]) && 
       !(this->m_unordered_hcycle[pos_h + this->Super::m_cols] < this->m_unordered_hcycle[pos_h] &&
         this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t]) &&
       !(this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h + this->Super::m_cols] &&
         this->m_unordered_hcycle[pos_h + this->Super::m_cols] < this->m_unordered_hcycle[pos_h])
    ){ // down
        if(
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + this->Super::m_cols] &&
            this->m_unordered_hcycle[pos_h + this->Super::m_cols] <= this->m_unordered_hcycle[pos_a] &&
            sc < this->m_unordered_hcycle[pos_h + this->Super::m_cols] - this->m_unordered_hcycle[pos_h]
        ){
            // sc = this->m_unordered_hcycle[pos_h + this->Super::m_cols] - this->m_unordered_hcycle[pos_h];
            dir = 4;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + this->Super::m_cols] &&
            sc < this->m_unordered_hcycle[pos_h + this->Super::m_cols] - this->m_unordered_hcycle[pos_h]
        ){
            // sc = this->m_unordered_hcycle[pos_h + this->Super::m_cols] - this->m_unordered_hcycle[pos_h];
            dir = 4;

        }else if(
            this->m_unordered_hcycle[pos_h + this->Super::m_cols] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + this->Super::m_cols]
        ){
            // sc = (this->Super::m_cols * this->Super::m_rows) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + this->Super::m_cols];
            dir = 4;  

        }
    }

    return dir;
}