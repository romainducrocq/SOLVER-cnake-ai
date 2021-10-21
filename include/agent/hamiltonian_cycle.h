#ifndef _HAMILTONIAN_CYCLE_H
#define _HAMILTONIAN_CYCLE_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

#include "../utils.h"

template<typename T>
bool v_contains(const std::vector<T>& v, T i){
    return std::find(v.begin(), v.end(), i) != v.end();
}

class PrimMazeGenerator{
    private:
        int m_scols, m_srows;
        bool* m_cells;
        std::set<Vector2i> m_walls;

        void add_adj_walls(int cell);

    protected:
        std::vector<int>* m_maze;

    public:
        PrimMazeGenerator(int cols, int rows);

        ~PrimMazeGenerator();

        void prim_algorithm();

    /***
     * TEST
     * 
     */
    public:
        void print_visited();
        void print_edges();
        void print_maze();
    /**/

};

class HamiltonianCycle: public PrimMazeGenerator{
    private:
        typedef PrimMazeGenerator Super;

        int m_cols, m_rows;
        int* m_cycle;

    public:
        HamiltonianCycle(int cols, int rows);

        ~HamiltonianCycle();

        void hc_algorithm();

    /***
     * TEST
     * 
     */
    public:
        void print_cycle();
        void test();
     /**/

};

#endif