#ifndef _UTILS_H
#define _UTILS_H

#include <string>

enum Mode{ AGENT, PLAYER };

static const int COLS = 30; // 64;
static const int ROWS = COLS; // 64;
static const int ZOOM = 20; // 15;
static const float WAIT = 0.06f; // 0.0f;
static const std::string NAME = "SNAKE";

struct Vector2i{
    int x, y;

    Vector2i()
        : x(0), y(0) {}

    Vector2i(int x, int y)
        : x(x), y(y) {}

    bool operator <(const Vector2i& o) const{
        return (x < o.x) || ((!(o.x < x)) && (y < o.y));
    }
};

#endif