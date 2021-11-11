#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/config.hpp"

class Renderer
{
    private:
        sf::RenderTarget& m_target;

        sf::ConvexShape m_convex_shape_hcycle;
        sf::CircleShape m_circle_shape;
        sf::RectangleShape m_rectangle_shape;

    private:
        void drawConvexShape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                             int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        void drawCircleShape(float radius, float position_x, float position_y,
                             int outline_thickness, sf::Color fill_color, sf::Color outline_color,
                             sf::CircleShape* circle_shape = nullptr);

        void drawRectangleShape(float size_x, float size_y, float position_x, float position_y,
                                int outline_thickness, sf::Color fill_color, sf::Color outline_color,
                                sf::RectangleShape* rectangle_shape = nullptr);

        void drawLineShape(float position_x1, float position_y1, float position_x2, float position_y2);

    public:
        Renderer(sf::RenderTarget& target);

        /***
         * INIT
         *
         */

        void initShapeHCycle(const int* hcyle);

        /***
         * RENDER
         *
         */

        void renderShapeHCycle(bool is_debug);

        void renderShapeApple(int pos);

        void renderShapeSnake(const std::vector<int>& body);
};

#endif