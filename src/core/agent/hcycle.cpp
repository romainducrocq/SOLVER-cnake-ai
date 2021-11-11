#include "../../../include/core/agent/hcycle.hpp"


HamiltonianCycle::HamiltonianCycle()
{
    assert(Conf::COLS % 2 == 0 && Conf::ROWS % 2 == 0);

    this->m_hcycle = new int[Conf::COLS * Conf::ROWS];
    
    this->hCycleGenAlg();
}

HamiltonianCycle::~HamiltonianCycle()
{
    delete[] this->m_hcycle;
}

/***
 * PRIM MAZE GENERATOR
 * 
 */

void HamiltonianCycle::addPWalls(std::set<Vector2i>& pwalls, int pcell)
{
    if(pcell % (Conf::COLS / 2) != 0){                      // left
        pwalls.insert(Vector2i(pcell - 1, pcell));
    }
    if((pcell + 1) % (Conf::COLS / 2) != 0){                // right
        pwalls.insert(Vector2i(pcell, pcell + 1));
    }
    if(pcell >= (Conf::COLS / 2)){                          // up
        pwalls.insert(Vector2i(pcell - (Conf::COLS / 2), pcell));
    }
    if(pcell < ((Conf::ROWS / 2)- 1) * (Conf::COLS / 2)){ // down
        pwalls.insert(Vector2i(pcell, pcell + (Conf::COLS / 2)));
    }
}

void HamiltonianCycle::pMazeGenAlg(std::vector<int>* pmaze)
{
    // https://en.wikipedia.org/wiki/Maze_generation_algorithm

    // start with a grid full of walls
    bool* pcells;
    std::set<Vector2i> pwalls;

    pcells = new bool[(Conf::COLS / 2) * (Conf::ROWS / 2)];
    for(int i = 0; i < (Conf::COLS / 2) * (Conf::ROWS / 2); i++){
        pcells[i] = false;
    }

    // pick random cell, set to visited
    int pcell = std::rand() % ((Conf::COLS / 2) * (Conf::ROWS / 2));
    pcells[pcell] = true;

    // add adjacent walls to wall list
    this->addPWalls(pwalls, pcell);

    // while wall list not empty
    while(!pwalls.empty()){

        // pick random wall from wall list
        auto pwall = pwalls.begin();
        std::advance(pwall, rand() % pwalls.size());

        // if wall has only one visited cell
        if(!pcells[pwall->x] != !pcells[pwall->y]){
            
            // wall is edge, add to maze
            pmaze[pwall->x].push_back(pwall->y);
            pmaze[pwall->y].push_back(pwall->x);

            // set unvisited cell to visited
            pcell = pcells[pwall->x] ? pwall->y : pwall->x;
            pcells[pcell] = true;

            // add adjacent walls to wall list
            this->addPWalls(pwalls, pcell);
        }

        // remove wall from wall list
        pwalls.erase(pwall);
    }

    delete[] pcells;
}

/***
 * HAMILTONIAN CYCLE
 * 
 */

void HamiltonianCycle::hCycleGenAlg()
{
    std::vector<int>* pmaze = new std::vector<int>[(Conf::COLS / 2) * (Conf::ROWS / 2)];

    this->pMazeGenAlg(pmaze);

    int hcell = 0, hdir = 0, hcount = 0;

    do{
        this->m_hcycle[hcount] = hcell;
        hcount++;

        int hnext;
        int pcell = ((hcell / Conf::COLS) / 2) * (Conf::COLS / 2) + ((hcell % Conf::COLS) / 2);
        for(int i = 0; i < 3; i++){
            if(i == 0){ hnext = (hdir + 3) % 4; }
            else if(i == 1){ hnext = (hdir + 4) % 4; }
            else if(i == 2){ hnext = (hdir + 5) % 4; }

            if(hnext == 0 && ((hcell / Conf::COLS) % 2 == 1 || v_contains(pmaze[pcell], pcell - (Conf::COLS / 2)))){       // up
                hcell -= Conf::COLS; 
                hdir = 0;
                break;

            }else if(hnext == 1 && (hcell % 2 == 0 || v_contains(pmaze[pcell], pcell + 1))){                                   // right
                hcell += 1; 
                hdir = 1;
                break;

            }else if(hnext == 2 && ((hcell / Conf::COLS) % 2 == 0 || v_contains(pmaze[pcell], pcell + (Conf::COLS / 2)))){ // down
                hcell += Conf::COLS; 
                hdir = 2;
                break;

            }else if(hnext == 3 && (hcell % 2 == 1 || v_contains(pmaze[pcell], pcell - 1))){                                   // left
                hcell -= 1; 
                hdir = 3;
                break;

            }
        }
    }while(hcount < Conf::COLS * Conf::ROWS);

    // this->print_debug(pmaze);
    
    delete[] pmaze;
}

const int* HamiltonianCycle::getHCycle() const
{
    return this->m_hcycle;
}

/***
 * TEST
 * 
 */

void HamiltonianCycle::printDebug(const std::vector<int>* pmaze) const
{

    // print pmaze
    std::cout << "\nMaze:\n";
    for(int i = 0; i < (Conf::COLS / 2); i++){
        std::cout << " _";
    }
    std::cout << "\n";
    for(int i = 0; i < (Conf::ROWS / 2); i++){
        std::cout << "|";
        for(int j = 0; j < (Conf::COLS / 2); j++){
            if(v_contains(pmaze[i * (Conf::COLS / 2) + j], (i + 1) * (Conf::COLS / 2) + j)){
                std::cout << " "; 
            }else{
                std::cout << "_"; 
            }
            if(v_contains(pmaze[i * (Conf::COLS / 2) + j], i * (Conf::COLS / 2) + (j + 1))){
                std::cout << " "; 
            }else{
                std::cout << "|"; 
            }
        }
        std::cout << "\n";
    }

    // print hcycle
    std::cout << "\nHamiltonian cycle:\n\n"; 
    for(int i = 0; i < Conf::COLS * Conf::ROWS; i++){
        std::cout << this->m_hcycle[i] << " ";
    }
    std::cout << "\n";
}