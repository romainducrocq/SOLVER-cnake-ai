#ifndef _HCYCLE_HPP
#define _HCYCLE_HPP

#include <iostream>
#include <cassert>
#include <cstdlib>

#include <algorithm>
#include <vector>
#include <set>

#include "../../utils/config.hpp"
#include "../../utils/vector.hpp"

template<typename T>
bool v_contains(const std::vector<T>& v, T i)
{
    return std::find(v.begin(), v.end(), i) != v.end();
}

class HamiltonianCycle
{
    protected:
        int* m_hcycle;

    private:
        // test
        void printDebug(const std::vector<int>* pmaze) const;

        // prim maze generator
        void addPWalls(std::set<Vector2i>& pwalls, int pcell);

        void pMazeGenAlg(std::vector<int>* pmaze);

        // hamiltonian cycle
        void hCycleGenAlg();

    public:
        HamiltonianCycle();

        ~HamiltonianCycle();

        const int* getHCycle() const;
};

#endif