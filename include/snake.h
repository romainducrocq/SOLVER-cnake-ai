#ifndef _SNAKE_H
#define _SNAKE_H

#include <cstdlib>
#include <vector>

#include "utils.h"

class Apple{
    private:
        Vector2i m_mat;
        Vector2i m_pos;

    public:
        Apple(int cols, int rows);

        Vector2i get_pos() const;
        void update_pos();
};

class Snake{
    private:
        Vector2i m_mat;
        Vector2i m_pos = Vector2i(0, 0);
        Vector2i m_dir = Vector2i(1, 0);
        std::vector<Vector2i> m_body;
    
    public:
        Snake(int cols, int rows);

        Vector2i get_pos(int i) const;

        size_t get_size() const;

        void update_size();

        void update_body();

        void update_pos();

        void update_dir(Vector2i dir);

        bool is_eat(Vector2i pos) const;

        bool is_hit() const;
};

#endif