#ifndef _SNAKE_HPP
#define _SNAKE_HPP

#include <cstdlib>
#include <vector>

#include "utils/config.hpp"
#include "utils/vector.hpp"

class Apple
{
    private:
        int m_pos;

    private:
        bool isValidPos(const std::vector<int>& body);

    public:
        Apple();

        int getPos() const;

        void updatePos(const std::vector<int>& body);
};

class Snake
{
    private:
        Vector2i m_pos = Vector2i(0, 0);
        Vector2i m_dir = Vector2i(1, 0);
        std::vector<int> m_body;
    
    public:
        Snake();

        const std::vector<int>& getBody() const;

        void updateSize();

        void updateBody();

        void updatePos();

        void updateDir(Vector2i dir);

        bool isEat(int pos) const;

        bool isHit() const;

        void act(int action);
};

#endif