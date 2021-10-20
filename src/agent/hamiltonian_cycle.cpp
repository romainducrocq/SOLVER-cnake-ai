# include "../../include/agent/hamiltonian_cycle.h"

/***
 * PRIM MAZE GENERATOR
 * 
 */ 

PrimMazeGenerator::PrimMazeGenerator(int cols, int rows)
    : m_scols(cols / 2), m_srows(rows / 2){
    this->m_cells = new bool[this->m_scols * this->m_srows];
    for(int i = 0; i < this->m_scols * this->m_srows; i++){
        this->m_cells[i] = false;
    }

    this->m_maze = new std::vector<int>[this->m_scols * this->m_srows];

    this->prim_algorithm();

    /***
     *  TEST 
     * 
     * */

    this->test();

    /**/
}

PrimMazeGenerator::~PrimMazeGenerator(){
    delete[] this->m_cells;
    delete[] this->m_maze;
}

void PrimMazeGenerator::add_adj_walls(int cell){
    if(cell % this->m_scols != 0){                 //left
        this->m_walls.insert(Vector2i(cell - 1, cell));
    }
    if((cell + 1) % this->m_scols != 0){            //right
        this->m_walls.insert(Vector2i(cell, cell + 1));
    }
    if(cell >= this->m_scols){                     //up
        this->m_walls.insert(Vector2i(cell - this->m_scols, cell));
    }
    if(cell < (this->m_scols - 1) * this->m_srows){ //down
        this->m_walls.insert(Vector2i(cell, cell + this->m_scols));
    }
}

void PrimMazeGenerator::prim_algorithm(){
    // https://en.wikipedia.org/wiki/Maze_generation_algorithm

    // pick random cell, set to visited
    int cell = std::rand() % (this->m_scols * this->m_srows);
    this->m_cells[cell] = true;

    // add adjacent walls to wall list
    this->add_adj_walls(cell);

    // while wall list not empty
    while(!this->m_walls.empty()){

        // pick random wall from wall list
        auto wall = this->m_walls.begin();
        std::advance(wall, rand() % m_walls.size());

        // if wall has only one visited cell
        if(!this->m_cells[wall->x] != !this->m_cells[wall->y]){
            
            // wall is edge, add to maze
            this->m_maze[wall->x].push_back(wall->y);
            this->m_maze[wall->y].push_back(wall->x);

            // set unvisited cell to visited
            cell = this->m_cells[wall->x] ? wall->y : wall->x;
            this->m_cells[cell] = true;

            // add adjacent walls to wall list
            this->add_adj_walls(cell);
        }

        // remove wall from wall list
        this->m_walls.erase(wall);
    }
}

/***
 * TEST
 * 
 */

void PrimMazeGenerator::print_visited(){
    std::cout << "\nVisited:\n";
    for(int i = 0; i < this->m_srows; i++){
        for(int j = 0; j < this->m_scols; j++){
            std::cout << "(" << i << ", " << j << ") = " << this->m_cells[i * this->m_scols + j] << "\n";
        }
    }
}

void PrimMazeGenerator::print_edges(){
    std::cout << "\nEdges:\n";
    for(int i = 0; i < this->m_scols * this->m_srows; i++){
        std::cout << i << " -> ";
        for(const auto& e: this->m_maze[i]){
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
}

void PrimMazeGenerator::print_maze(){
    std::cout << "\nMaze:\n";
    for(int i = 0; i < this->m_scols; i++){
        std::cout << " _";
    }
    std::cout << "\n";
    for(int i = 0; i < this->m_srows; i++){
        std::cout << "|";
        for(int j = 0; j < this->m_scols; j++){
            if(std::find(this->m_maze[i * this->m_scols + j].begin(), this->m_maze[i * this->m_scols + j].end(), 
                        ((i + 1) * this->m_scols + j)) != this->m_maze[i * this->m_scols + j].end()){
                std::cout << " "; 
            }else{
                std::cout << "_"; 
            }
            if(std::find(this->m_maze[i * this->m_scols + j].begin(), this->m_maze[i * this->m_scols + j].end(), 
                        (i * this->m_scols + (j + 1))) != this->m_maze[i * this->m_scols + j].end()){
                std::cout << " "; 
            }else{
                std::cout << "|"; 
            }
        }
        std::cout << "\n";
    }
}

void PrimMazeGenerator::test(){
    /*
    this->print_visited();
    this->print_edges();
    */
    this->print_maze();
}

/***
 * HAMILTONIAN CYCLE
 * 
 */ 

HamiltonianCycle::HamiltonianCycle(int cols, int rows)
    : Super(cols, rows), m_cols(cols), m_rows(rows){}