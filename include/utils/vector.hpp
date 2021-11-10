#ifndef _VECTOR_H
#define _VECTOR_H

struct Vector2i
{
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