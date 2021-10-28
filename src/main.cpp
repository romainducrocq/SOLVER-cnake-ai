#include "../include/controller.h"

Game::Game(Mode mode, int cols, int rows, int zoom, std::string name) 
    : Super(name, cols, rows, zoom), m_model(cols, rows), m_mode(mode){
    this->setup();
    this->loop();
} 

void Game::act(int action){
    switch(action){
    case 1: // left
        this->m_model.m_snake.update_dir(Vector2i(-1, 0));
        break;
    case 2: // right
        this->m_model.m_snake.update_dir(Vector2i(1, 0));        
        break;
    case 3: // up
        this->m_model.m_snake.update_dir(Vector2i(0, -1));
        break;
    case 4: // down
        this->m_model.m_snake.update_dir(Vector2i(0, 1));
        break;
    default:
        break;
    }
}

int Game::get_action(){
    switch (this->m_mode){
    case Mode::AGENT_PHC:
        return this->m_model.m_agent.get_action_phc(
            this->m_model.m_snake.get_body()[0],
            this->m_model.m_snake.get_body()[
                this->m_model.m_snake.get_body().size() - 1],
            this->m_model.m_apple.get_pos()
        );
    case Mode::AGENT_HC:
        return this->m_model.m_agent.get_action_hc(
            this->m_model.m_snake.get_body()[0]
        );
    case Mode::PLAYER:
        return this->Super::get_ctrl_input();
    default:
        return 0;
    }
}

/***
 * VIEW
 * 
 */

void Game::view_setup(){
    this->Super::m_convex_shape_hcycle.setPointCount(this->Super::m_cols * this->Super::m_rows);
    for(int i = 0; i < this->Super::m_cols * this->Super::m_rows; i++){
        this->Super::m_convex_shape_hcycle.setPoint(i, sf::Vector2f(
            (this->m_model.m_agent.get_hcycle()[i] % this->Super::m_cols) * this->Super::m_zoom,
            (this->m_model.m_agent.get_hcycle()[i] / this->Super::m_cols) * this->Super::m_zoom
        ));
    }
}

void Game::view_loop(){
    if(this->Super::is_debug_view()){
        // draw hamiltonian cycle
        this->Super::draw_convex_shape(this->Super::m_convex_shape_hcycle, 
                                       this->Super::m_zoom / 2, 
                                       this->Super::m_zoom / 2, 
                                       1, sf::Color::Transparent, sf::Color(220, 220, 220));
    }

    // draw apple
    this->Super::draw_circle_shape(Super::m_zoom * 0.4f, 
                                   (this->m_model.m_apple.get_pos() % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f, 
                                   (this->m_model.m_apple.get_pos() / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f, 
                                   0, sf::Color(255, 0, 100), sf::Color::Transparent, &this->Super::m_circle_shape);

    // draw snake
    size_t i = 1;
    while (i < this->m_model.m_snake.get_body().size()){

        size_t j = 0;
        while((i + j) < this->m_model.m_snake.get_body().size() && 
              this->m_model.m_snake.get_body()[i] - this->m_model.m_snake.get_body()[i - 1] == 
              this->m_model.m_snake.get_body()[i + j + 1] - this->m_model.m_snake.get_body()[i + j])
        { j++; }

        this->Super::draw_circle_shape(Super::m_zoom * 0.4f,
                                       (this->m_model.m_snake.get_body()[i + j] % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f, 
                                       (this->m_model.m_snake.get_body()[i + j] / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                       0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_circle_shape);

        if(this->m_model.m_snake.get_body()[i] - this->m_model.m_snake.get_body()[i - 1] == 1){                          // left
            this->Super::draw_rectangle_shape(((this->m_model.m_snake.get_body()[i + j] % this->Super::m_cols) -
                                                (this->m_model.m_snake.get_body()[i - 1] % this->Super::m_cols)) * Super::m_zoom,
                                              Super::m_zoom * 0.8f,
                                              (this->m_model.m_snake.get_body()[i - 1] % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.5f,
                                              (this->m_model.m_snake.get_body()[i - 1] / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);
        
        }else if(this->m_model.m_snake.get_body()[i] - this->m_model.m_snake.get_body()[i - 1] == -1){                   // right
            this->Super::draw_rectangle_shape(((this->m_model.m_snake.get_body()[i - 1] % this->Super::m_cols) - 
                                                (this->m_model.m_snake.get_body()[i + j] % this->Super::m_cols)) * Super::m_zoom,
                                              Super::m_zoom * 0.8f,
                                              (this->m_model.m_snake.get_body()[i + j] % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.5f,
                                              (this->m_model.m_snake.get_body()[i + j] / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);

        }else if(this->m_model.m_snake.get_body()[i] - this->m_model.m_snake.get_body()[i - 1] == this->Super::m_cols){  // up
            this->Super::draw_rectangle_shape(Super::m_zoom * 0.8f,
                                              ((this->m_model.m_snake.get_body()[i + j] / this->Super::m_cols) -
                                                (this->m_model.m_snake.get_body()[i - 1] / this->Super::m_cols)) * Super::m_zoom,
                                              (this->m_model.m_snake.get_body()[i - 1] % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                              (this->m_model.m_snake.get_body()[i - 1] / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.5f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);

        }else if(this->m_model.m_snake.get_body()[i] - this->m_model.m_snake.get_body()[i - 1] == -this->Super::m_cols){ // down
            this->Super::draw_rectangle_shape(Super::m_zoom * 0.8f,
                                              ((this->m_model.m_snake.get_body()[i - 1] / this->Super::m_cols) -
                                                (this->m_model.m_snake.get_body()[i + j] / this->Super::m_cols)) * Super::m_zoom,
                                              (this->m_model.m_snake.get_body()[i + j] % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                              (this->m_model.m_snake.get_body()[i + j] / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.5f,
                                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->Super::m_rectangle_shape);
        
        }

        i += (j + 1);
    }

    this->Super::draw_circle_shape(Super::m_zoom * 0.4f,
                                   (this->m_model.m_snake.get_body()[0] % this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                   (this->m_model.m_snake.get_body()[0] / this->Super::m_cols) * Super::m_zoom + Super::m_zoom * 0.1f,
                                   0, sf::Color(0, 100, 255), sf::Color::Transparent, &this->Super::m_circle_shape);
}

/***
 * CONTROLLER
 * 
 */

void Game::ctrl_setup(){
    
}

void Game::ctrl_loop(){
    this->act(this->get_action());

    this->m_model.m_snake.update_pos();
    if(this->m_model.m_snake.is_eat(
        this->m_model.m_apple.get_pos()
    )){
        this->m_model.m_snake.update_size();
        this->m_model.m_apple.update_pos(
            this->m_model.m_snake.get_body()
        );
    }
    this->m_model.m_snake.update_body();
    
    if(this->m_model.m_snake.is_hit()){
        this->Super::wait_exit();
    }
}

/***
 * 
 * 
 */

int main(int argc, char** argv){
    std::srand(time(nullptr));
    
    Args args;

    // https://github.com/gnif/LookingGlass/blob/c0c63fd93bf999b6601a782fec8b56e9133388cc/client/main.c#L1391

    for(;;){
        switch(getopt(argc, argv, "hM:S:")){
            case '?':
            case 'h':
            default :
                std::cerr << "usage: app/exec [-h] [-M MODE] [-S SIZE]\n";
                std::cerr << "\n";
                std::cerr << args.name << "\n";
                std::cerr << "\n";
                std::cerr << "optional args:\n";
                std::cerr << "  -h        show this help message and exit\n";
                std::cerr << "  -M MODE   set mode  < phc | hc | play >  \n";
                std::cerr << "  -S SIZE   set size  < small | large >    \n";
                std::cerr << "\n";
                std::cerr << "optional cmds:\n";
                std::cerr << "  key SPACE set frate 24FPS, VSYNC, MAX    \n";
                std::cerr << "  key D     set debug NO, YES              \n";

                return -1;

            case -1:
                break;

            case 'M': // MODE
                if(std::strcmp(optarg, "phc") == 0){        // agent phc
                    ; // default
                }else if(std::strcmp(optarg, "hc") == 0){   // agent hc
                    args.mode = Mode::AGENT_HC;
                }else if(std::strcmp(optarg, "play") == 0){ // player
                    args.mode = Mode::PLAYER;
                }
                continue;

            case 'S': // SIZE
                if(std::strcmp(optarg, "small") == 0){         // small
                    ; // default
                }else if(std::strcmp(optarg, "large") == 0){   // large
                        args.cols = 128;
                        args.rows = 64;
                        args.zoom = 15;  
                }
                continue;

        }
        break;
    }

    Game game(args.mode, args.cols, args.rows, args.zoom, args.name);
}