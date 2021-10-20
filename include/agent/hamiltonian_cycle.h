#ifndef _HAMILTONIAN_CYCLE_H
#define _HAMILTONIAN_CYCLE_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

#include "../utils.h"

class PrimMazeGenerator{
    private:
        int m_scols, m_srows;
        bool* m_cells;
        std::set<Vector2i> m_walls;

        void add_adj_walls(int cell);

        /***
         * TEST
         * 
         */
        void test();
        void print_visited();
        void print_edges();
        void print_maze();
        /**/

    protected:
        std::vector<int>* m_maze;

    public:
        PrimMazeGenerator(int cols, int rows);

        ~PrimMazeGenerator();

        void prim_algorithm();
};

class HamiltonianCycle: public PrimMazeGenerator{
    private:
        typedef PrimMazeGenerator Super;

        int m_cols, m_rows;

    public:
        HamiltonianCycle(int cols, int rows);
};

#endif