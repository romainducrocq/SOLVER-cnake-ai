#include <cstdlib>
#include <ctime>

#include "utils/config.hpp"

#include "core/app.hpp"

int main(int argc, char** argv)
{
    std::srand(time(nullptr));
    
    Conf::argParse(argc, argv);

    Application app;
}