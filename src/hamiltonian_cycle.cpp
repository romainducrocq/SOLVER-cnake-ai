# include "../include/hamiltonian_cycle.h"

HamiltonianCycle::HamiltonianCycle(int cols, int rows)
    : m_cols(cols), m_rows(rows){

    assert(this->m_cols % 2 == 0);
    assert(this->m_rows % 2 == 0);

    // prim maze generator
    this->m_cells = new bool[(this->m_cols / 2) * (this->m_rows / 2)];
    for(int i = 0; i < (this->m_cols / 2) * (this->m_rows / 2); i++){
        this->m_cells[i] = false;
    }

    this->m_maze = new std::vector<int>[(this->m_cols / 2) * (this->m_rows / 2)];

    this->prim_algorithm();

    // hamiltonian cycle
    this->m_cycle = new int[this->m_cols * this->m_rows];

    this->hc_algorithm();
}

HamiltonianCycle::~HamiltonianCycle(){
    // prim maze generator
    delete[] this->m_cells;
    delete[] this->m_maze;

    // hamiltonian cycle
    delete[] this->m_cycle;
}

/***
 * PRIM MAZE GENERATOR
 * 
 */

void HamiltonianCycle::prim_adj_walls(int cell){
    if(cell % (this->m_cols / 2) != 0){                      //left
        this->m_walls.insert(Vector2i(cell - 1, cell));
    }
    if((cell + 1) % (this->m_cols / 2) != 0){                //right
        this->m_walls.insert(Vector2i(cell, cell + 1));
    }
    if(cell >= (this->m_cols / 2)){                          //up
        this->m_walls.insert(Vector2i(cell - (this->m_cols / 2), cell));
    }
    if(cell < ((this->m_rows / 2)- 1) * (this->m_cols / 2)){ //down
        this->m_walls.insert(Vector2i(cell, cell + (this->m_cols / 2)));
    }
}

void HamiltonianCycle::prim_algorithm(){
    // https://en.wikipedia.org/wiki/Maze_generation_algorithm

    // pick random cell, set to visited
    int cell = std::rand() % ((this->m_cols / 2) * (this->m_rows / 2));
    this->m_cells[cell] = true;

    // add adjacent walls to wall list
    this->prim_adj_walls(cell);

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
            this->prim_adj_walls(cell);
        }

        // remove wall from wall list
        this->m_walls.erase(wall);
    }
}

/***
 * HAMILTONIAN CYCLE
 * 
 */

void HamiltonianCycle::hc_algorithm(){
    int cell = 0, dir = 0, count = 0;

    do{
        this->m_cycle[count] = cell;
        count++;

        int next;
        int c_maze = ((cell / this->m_cols) / 2) * (this->m_cols / 2) + ((cell % this->m_cols) / 2);
        for(int i = 0; i < 3; i++){
            if(i == 0){ next = (dir + 3) % 4; }
            else if(i == 1){ next = (dir + 4) % 4; }
            else if(i == 2){ next = (dir + 5) % 4; }

            if(next == 0 && ((cell / this->m_cols) % 2 == 1 || v_contains(this->m_maze[c_maze], c_maze - (this->m_cols / 2)))){       // up
                cell -= this->m_cols; 
                dir = 0;
                break;

            }else if(next == 1 && (cell % 2 == 0 || v_contains(this->m_maze[c_maze], c_maze + 1))){                                   // right
                cell += 1; 
                dir = 1;
                break;

            }else if(next == 2 && ((cell / this->m_cols) % 2 == 0 || v_contains(this->m_maze[c_maze], c_maze + (this->m_cols / 2)))){ // down
                cell += this->m_cols; 
                dir = 2;
                break;

            }else if(next == 3 && (cell % 2 == 1 || v_contains(this->m_maze[c_maze], c_maze - 1))){                                   // left
                cell -= 1; 
                dir = 3;
                break;

            }
        }
    }while(count < this->m_cols * this->m_rows);
}

const int* HamiltonianCycle::get_hc() const{
    return this->m_cycle;
}

/***
 * TEST
 * 
 */

void HamiltonianCycle::print_pmaze(){
    std::cout << "\nMaze:\n";
    for(int i = 0; i < (this->m_cols / 2); i++){
        std::cout << " _";
    }
    std::cout << "\n";
    for(int i = 0; i < (this->m_rows / 2); i++){
        std::cout << "|";
        for(int j = 0; j < (this->m_cols / 2); j++){
            if(v_contains(this->m_maze[i * (this->m_cols / 2) + j], (i + 1) * (this->m_cols / 2) + j)){
                std::cout << " "; 
            }else{
                std::cout << "_"; 
            }
            if(v_contains(this->m_maze[i * (this->m_cols / 2) + j], i * (this->m_cols / 2) + (j + 1))){
                std::cout << " "; 
            }else{
                std::cout << "|"; 
            }
        }
        std::cout << "\n";
    }
}

void HamiltonianCycle::print_hcycle(){
    std::cout << "\nHamiltonian cycle:\n\n"; 
    for(int i = 0; i < this->m_cols * this->m_rows; i++){
        std::cout << this->m_cycle[i] << " ";
    }
    std::cout << "\n";
}

void HamiltonianCycle::debug(){
    this->print_pmaze();
    this->print_hcycle();
}