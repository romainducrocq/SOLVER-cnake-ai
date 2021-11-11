#include <cstdlib>
#include <ctime>

#include "../include/utils/config.hpp"

#include "../include/core/app.hpp"

int main(int argc, char** argv)
{
    std::srand(time(nullptr));
    
    Conf::argParse(argc, argv);

    Application app;
}