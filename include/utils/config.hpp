#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include <unistd.h>

#include <iostream>
#include <cstring>

template<typename T>
struct DefaultConf
{
    enum Action{
        NOOP, LEFT, RIGHT, UP, DOWN
    };
    enum Mode{
        AGENT_PHC, AGENT_HC, PLAYER
    };

    const static char* NAME;
    const static int BG_COL[3];
    const static int FRAMERATE;
    const static int ANTIALIAS;

    static int WIN_W;
    static int WIN_H;

    static Mode MODE;
    static int COLS;
    static int ROWS;
    static int ZOOM;

    static bool argParse(int argc, char** argv)
    {
        // https://github.com/gnif/LookingGlass/blob/c0c63fd93bf999b6601a782fec8b56e9133388cc/client/main.c#L1391

        for(;;){
            switch(getopt(argc, argv, "hM:S:")){
                case '?':
                case 'h':
                default :
                    std::cerr << "usage: apps/exec [-h] [-M MODE] [-S SIZE]\n";
                    std::cerr << "\n";
                    std::cerr << DefaultConf<T>::NAME << "\n";
                    std::cerr << "\n";
                    std::cerr << "optional args:\n";
                    std::cerr << "  -h       show this help message and exit\n";
                    std::cerr << "  -M MODE  set mode  < phc | hc | play >  \n";
                    std::cerr << "  -S SIZE  set size  < small | large >    \n";
                    std::cerr << "\n";
                    std::cerr << "optional cmds:\n";
                    std::cerr << "  key S    set speed 24FPS, VSYNC, MAX    \n";
                    std::cerr << "  key D    set debug NO, YES              \n";

                    return false;

                case -1:
                    break;

                case 'M': // MODE
                    if(std::strcmp(optarg, "phc") == 0){        // agent phc
                        DefaultConf<T>::MODE = DefaultConf<T>::Mode::AGENT_PHC;
                    }else if(std::strcmp(optarg, "hc") == 0){   // agent hc
                        DefaultConf<T>::MODE = DefaultConf<T>::Mode::AGENT_HC;
                    }else if(std::strcmp(optarg, "play") == 0){ // player
                        DefaultConf<T>::MODE = DefaultConf<T>::Mode::PLAYER;
                    }
                    continue;

                case 'S': // SIZE
                    if(std::strcmp(optarg, "small") == 0){         // small
                        DefaultConf<T>::COLS = 32;
                        DefaultConf<T>::ROWS = 32;
                        DefaultConf<T>::ZOOM = 20;
                        DefaultConf<T>::WIN_W = 32 * 20;
                        DefaultConf<T>::WIN_H = 32 * 20;
                    }else if(std::strcmp(optarg, "large") == 0){   // large
                        DefaultConf<T>::COLS = 128;
                        DefaultConf<T>::ROWS = 64;
                        DefaultConf<T>::ZOOM = 15;
                        DefaultConf<T>::WIN_W = 128 * 15;
                        DefaultConf<T>::WIN_H = 64 * 15;
                    }
                    continue;

            }
            break;
        }

        return true;
    }
};

template<typename T>
const char* DefaultConf<T>::NAME = "Hamiltonian Snake";
template<typename T>
const int DefaultConf<T>::BG_COL[3] = { 51, 51, 51 };
template<typename T>
const int DefaultConf<T>::FRAMERATE = 24;
template<typename T>
const int DefaultConf<T>::ANTIALIAS = 0;

template<typename T>
int DefaultConf<T>::WIN_W = 32 * 20;
template<typename T>
int DefaultConf<T>::WIN_H = 32 * 20;

template<typename T>
typename DefaultConf<T>::Mode DefaultConf<T>::MODE = DefaultConf<T>::Mode::AGENT_PHC;
template<typename T>
int DefaultConf<T>::COLS = 32;
template<typename T>
int DefaultConf<T>::ROWS = 32;
template<typename T>
int DefaultConf<T>::ZOOM = 20;

using Conf = DefaultConf<int>;

#endif