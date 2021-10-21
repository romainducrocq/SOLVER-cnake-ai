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
        bool* m_cells;
        std::set<Vector2i> m_walls;
        std::vector<int>* m_maze;

        // hamiltionian cycle
        int* m_cycle;

    private:
        // prim maze generator
        void prim_adj_walls(int cell);

        void prim_algorithm();

        // hamiltonian cycle
        void hc_algorithm();

    public:
        HamiltonianCycle(int cols, int rows);

        ~HamiltonianCycle();

    /***
     * TEST
     * 
     */
    public:
        /*
        void print_visited();
        void print_edges();
        */
        void print_pmaze();
        void print_hcycle();
        void debug();
     /**/

};

#endif