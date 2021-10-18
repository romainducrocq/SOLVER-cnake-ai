#ifndef _UTILS_H
#define _UTILS_H

#include <string>

static const int COLS = 30;
static const int ROWS = 30;
static const int ZOOM = 20;
static const float WAIT = 0.06f;
static const std::string NAME = "SNAKE";

struct Vector2i{
    int x, y;

    Vector2i()
        : x(0), y(0) {}

    Vector2i(int x, int y)
        : x(x), y(y) {}
};

#endif