#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/config.hpp"

class Renderer
{
    private:
        sf::RenderTarget& m_window;

        sf::Vertex         m_line[2] = { sf::Vertex(), sf::Vertex() };
        sf::CircleShape    m_circle_shape;
        sf::RectangleShape m_rectangle_shape;

        sf::ConvexShape m_convex_shape_hcycle;

    private:
        void drawLine(float position_x1, float position_y1, float position_x2, float position_y2,
                      sf::Color color = sf::Color::Black);

        void drawCircle(float radius, float position_x, float position_y,
                        sf::Color fill_color = sf::Color::Black, int outline_thickness = 0, sf::Color outline_color = sf::Color::Black);

        void drawRectangle(float size_x, float size_y, float position_x, float position_y,
                           sf::Color fill_color = sf::Color::Black, int outline_thickness = 0, sf::Color outline_color = sf::Color::Black);

        void drawShape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                       sf::Color fill_color = sf::Color::Black, int outline_thickness = 0, sf::Color outline_color = sf::Color::Black);

    public:
        Renderer(sf::RenderWindow& target);

        /***
         * INIT
         *
         */

        void initHCycle(const int* hcyle);

        /***
         * LOOP
         *
         */

        void renderHCycle(bool is_debug);

        void renderApple(int pos);

        void renderSnake(const std::vector<int>& body);
};

#endif