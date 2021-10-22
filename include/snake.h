#ifndef _SNAKE_H
#define _SNAKE_H

#include <cstdlib>
#include <vector>

#include "utils.h"

class Apple{
    private:
        int m_cols, m_rows, m_pos;

    private:
        bool is_valid_pos(const std::vector<int>& body);

    public:
        Apple(int cols, int rows);

        int get_pos() const;

        void update_pos(const std::vector<int>& body);
};

class Snake{
    private:
        int m_cols, m_rows;
        Vector2i m_pos = Vector2i(0, 0);
        Vector2i m_dir = Vector2i(1, 0);
        std::vector<int> m_body;
    
    public:
        Snake(int cols, int rows);

        const std::vector<int>& get_body() const;

        void update_size();

        void update_body();

        void update_pos();

        void update_dir(Vector2i dir);

        bool is_eat(int pos) const;

        bool is_hit() const;
};

#endif