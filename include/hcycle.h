#ifndef _HAMILTONIAN_CYCLE_H
#define _HAMILTONIAN_CYCLE_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

#include "utils.h"

template<typename T>
bool v_contains(const std::vector<T>& v, T i){
    return std::find(v.begin(), v.end(), i) != v.end();
}

class HamiltonianCycle{
    private:
        int m_cols, m_rows;

        // prim maze generator
        bool* m_pcells;
        std::set<Vector2i> m_pwalls;
        std::vector<int>* m_pmaze;

        // hamiltionian cycle
        int* m_hcycle;

    private:
        // prim maze generator
        void pmaze_adj_pwalls(int pcell);

        void pmaze_gen_alg();

        // hamiltonian cycle
        void hcycle_gen_alg();

    public:
        HamiltonianCycle(int cols, int rows);

        ~HamiltonianCycle();

        const int* get_hcycle() const;

    /***
     * TEST
     * 
     */
    public:
        void print_pmaze();
        void print_hcycle();
        void debug();
     /**/

};

#endif