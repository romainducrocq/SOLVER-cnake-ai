#include <cstdlib>
#include <ctime>

#include "../include/utils/config.hpp"
#include "../include/controller/main_loop.hpp"

int main(int argc, char** argv)
{
    std::srand(time(nullptr));
    
    Conf::argParse(argc, argv);

    MainLoop game;
}