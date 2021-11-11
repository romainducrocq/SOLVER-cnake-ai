#include "../../../include/core/agent/agent.hpp"

Agent::Agent()
{
    this->m_unordered_hcycle = new int[Conf::COLS * Conf::ROWS];
    for(int i = 0; i < Conf::COLS * Conf::ROWS; i++){
        this->m_unordered_hcycle[this->Super::m_hcycle[i]] = i;
    }
}

Agent::~Agent()
{
    delete[] this->m_unordered_hcycle;
}

/***
 * HAMILTONIAN CYCLE
 * 
 */

Conf::Action Agent::getActionHC(int pos)
{
    this->m_count = (this->m_count + 1) % (Conf::COLS * Conf::ROWS);

    if(this->Super::m_hcycle[m_count] == pos - 1){ return Conf::LEFT; }               // left
    else if(this->Super::m_hcycle[m_count] == pos + 1){ return Conf::RIGHT; }         // right
    else if(this->Super::m_hcycle[m_count] == pos - Conf::COLS){ return Conf::UP; }   // up
    else if(this->Super::m_hcycle[m_count] == pos + Conf::COLS){ return Conf::DOWN; } // down
    
    return Conf::NOOP;
}

/***
 * PERTURBATED HAMILTONIAN CYCLE
 * 
 */

Conf::Action Agent::getActionPHC(int pos_h, int pos_t, int pos_a) const
{
    Conf::Action action = Conf::NOOP;
    int sc = 0;

    if(pos_h % Conf::COLS != 0 && 
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
            action = Conf::LEFT;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - 1] &&
            sc < this->m_unordered_hcycle[pos_h - 1] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - 1] - this->m_unordered_hcycle[pos_h];
            action = Conf::LEFT;

        }else if(
            this->m_unordered_hcycle[pos_h - 1] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - 1]
        ){
            sc = (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - 1];
            action = Conf::LEFT;  

        }
    }

    if((pos_h + 1) % Conf::COLS != 0 && 
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
            action = Conf::RIGHT;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + 1] &&
            sc < this->m_unordered_hcycle[pos_h + 1] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h + 1] - this->m_unordered_hcycle[pos_h];
            action = Conf::RIGHT;

        }else if(
            this->m_unordered_hcycle[pos_h + 1] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + 1]
        ){
            sc = (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + 1];
            action = Conf::RIGHT;  

        }
    }
    
    if(pos_h >= Conf::COLS && 
       !(this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t] &&
         this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h - Conf::COLS]) && 
       !(this->m_unordered_hcycle[pos_h - Conf::COLS] < this->m_unordered_hcycle[pos_h] &&
         this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t]) &&
       !(this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h - Conf::COLS] &&
         this->m_unordered_hcycle[pos_h - Conf::COLS] < this->m_unordered_hcycle[pos_h])
    ){ // up
        if(
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - Conf::COLS] &&
            this->m_unordered_hcycle[pos_h - Conf::COLS] <= this->m_unordered_hcycle[pos_a] &&
            sc < this->m_unordered_hcycle[pos_h - Conf::COLS] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - Conf::COLS] - this->m_unordered_hcycle[pos_h];
            action = Conf::UP;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h - Conf::COLS] &&
            sc < this->m_unordered_hcycle[pos_h - Conf::COLS] - this->m_unordered_hcycle[pos_h]
        ){
            sc = this->m_unordered_hcycle[pos_h - Conf::COLS] - this->m_unordered_hcycle[pos_h];
            action = Conf::UP;

        }else if(
            this->m_unordered_hcycle[pos_h - Conf::COLS] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - Conf::COLS]
        ){
            sc = (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h - Conf::COLS];
            action = Conf::UP;  

        }
    }
    
    if(pos_h < (Conf::ROWS - 1) * Conf::COLS && 
       !(this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t] &&
         this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h + Conf::COLS]) && 
       !(this->m_unordered_hcycle[pos_h + Conf::COLS] < this->m_unordered_hcycle[pos_h] &&
         this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_t]) &&
       !(this->m_unordered_hcycle[pos_t] < this->m_unordered_hcycle[pos_h + Conf::COLS] &&
         this->m_unordered_hcycle[pos_h + Conf::COLS] < this->m_unordered_hcycle[pos_h])
    ){ // down
        if(
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + Conf::COLS] &&
            this->m_unordered_hcycle[pos_h + Conf::COLS] <= this->m_unordered_hcycle[pos_a] &&
            sc < this->m_unordered_hcycle[pos_h + Conf::COLS] - this->m_unordered_hcycle[pos_h]
        ){
            // sc = this->m_unordered_hcycle[pos_h + Conf::COLS] - this->m_unordered_hcycle[pos_h];
            action = Conf::DOWN;

        }else if(
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            this->m_unordered_hcycle[pos_h] < this->m_unordered_hcycle[pos_h + Conf::COLS] &&
            sc < this->m_unordered_hcycle[pos_h + Conf::COLS] - this->m_unordered_hcycle[pos_h]
        ){
            // sc = this->m_unordered_hcycle[pos_h + Conf::COLS] - this->m_unordered_hcycle[pos_h];
            action = Conf::DOWN;

        }else if(
            this->m_unordered_hcycle[pos_h + Conf::COLS] <= this->m_unordered_hcycle[pos_a] &&
            this->m_unordered_hcycle[pos_a] < this->m_unordered_hcycle[pos_h] &&
            sc < (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + Conf::COLS]
        ){
            // sc = (Conf::COLS * Conf::ROWS) - this->m_unordered_hcycle[pos_h] + this->m_unordered_hcycle[pos_h + Conf::COLS];
            action = Conf::DOWN;  

        }
    }

    return action;
}