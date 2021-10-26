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
    protected:
        int m_cols, m_rows;

        int* m_hcycle;

    private:
        // test
        void print_debug(const std::vector<int>* pmaze);

        // prim maze generator
        void add_pwalls(std::set<Vector2i>& pwalls, int pcell);

        void pmaze_gen_alg(std::vector<int>* pmaze);

        // hamiltonian cycle
        void hcycle_gen_alg();

    public:
        HamiltonianCycle(int cols, int rows);

        ~HamiltonianCycle();

        const int* get_hcycle() const;
};

#endif