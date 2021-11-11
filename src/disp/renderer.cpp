#include "disp/renderer.hpp"

Renderer::Renderer(sf::RenderWindow& window)
    : m_window(window)
{}

void Renderer::drawShape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                         sf::Color fill_color, int outline_thickness, sf::Color outline_color)
{
    convex_shape.setPosition(sf::Vector2f(position_x, position_y));
    convex_shape.setOutlineThickness(outline_thickness);
    convex_shape.setFillColor(fill_color);
    convex_shape.setOutlineColor(outline_color);
    this->m_window.draw(convex_shape);
}

void Renderer::drawCircle(float radius, float position_x, float position_y,
                          sf::Color fill_color, int outline_thickness, sf::Color outline_color)
{
    this->m_circle_shape.setRadius(radius);
    this->m_circle_shape.setPosition(sf::Vector2f(position_x, position_y));
    this->m_circle_shape.setOutlineThickness(outline_thickness);
    this->m_circle_shape.setFillColor(fill_color);
    this->m_circle_shape.setOutlineColor(outline_color);
    this->m_window.draw(this->m_circle_shape);
}

void Renderer::drawRectangle(float size_x, float size_y, float position_x, float position_y,
                             sf::Color fill_color, int outline_thickness, sf::Color outline_color)
{
    this->m_rectangle_shape.setSize(sf::Vector2f(size_x, size_y));
    this->m_rectangle_shape.setPosition(sf::Vector2f(position_x, position_y));
    this->m_rectangle_shape.setOutlineThickness(outline_thickness);
    this->m_rectangle_shape.setFillColor(fill_color);
    this->m_rectangle_shape.setOutlineColor(outline_color);
    this->m_window.draw(this->m_rectangle_shape);
}

void Renderer::drawLine(float position_x1, float position_y1, float position_x2, float position_y2,
                        sf::Color color)
{
    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(position_x1, position_y1), color),
            sf::Vertex(sf::Vector2f(position_x2, position_y2), color)
    };

    this->m_window.draw(line, 2, sf::Lines);
}

/***
 * INIT
 *
 */

void Renderer::initHCycle(const int* hcyle)
{
    this->m_convex_shape_hcycle.setPointCount(Conf::COLS * Conf::ROWS);
    for(int i = 0; i < Conf::COLS * Conf::ROWS; i++){
        this->m_convex_shape_hcycle.setPoint(i, sf::Vector2f(
                (hcyle[i] % Conf::COLS) * Conf::ZOOM,
                (hcyle[i] / Conf::COLS) * Conf::ZOOM
        ));
    }
}

/***
 * LOOP
 *
 */

void Renderer::renderHCycle(bool is_debug)
{
    if(is_debug){
        // draw hamiltonian cycle
        this->drawShape(this->m_convex_shape_hcycle,
                        Conf::ZOOM / 2,
                        Conf::ZOOM / 2,
                        sf::Color::Transparent, 1, sf::Color(220, 220, 220));
    }
}

void Renderer::renderApple(int pos)
{
    // draw apple
    this->drawCircle(Conf::ZOOM * 0.4f,
                     (pos % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                     (pos / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                     sf::Color(255, 0, 100));
}

void Renderer::renderSnake(const std::vector<int>& body)
{
    // draw snake
    size_t i = 1;
    while (i < body.size()){

        size_t j = 0;
        while((i + j) < body.size() &&
              body[i] - body[i - 1] ==
              body[i + j + 1] - body[i + j])
        { j++; }

        this->drawCircle(Conf::ZOOM * 0.4f,
                         (body[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                         (body[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                         sf::Color(58, 191, 39));

        if(body[i] - body[i - 1] == 1){                 // left
            this->drawRectangle(((body[i + j] % Conf::COLS) - (body[i - 1] % Conf::COLS)) * Conf::ZOOM,
                                Conf::ZOOM * 0.8f,
                                (body[i - 1] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                (body[i - 1] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                sf::Color(58, 191, 39));

        }else if(body[i] - body[i - 1] == -1){          // right
            this->drawRectangle(((body[i - 1] % Conf::COLS) - (body[i + j] % Conf::COLS)) * Conf::ZOOM,
                                Conf::ZOOM * 0.8f,
                                (body[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                (body[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                sf::Color(58, 191, 39));

        }else if(body[i] - body[i - 1] == Conf::COLS){  // up
            this->drawRectangle(Conf::ZOOM * 0.8f,
                                ((body[i + j] / Conf::COLS) - (body[i - 1] / Conf::COLS)) * Conf::ZOOM,
                                (body[i - 1] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                (body[i - 1] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                sf::Color(58, 191, 39));

        }else if(body[i] - body[i - 1] == -Conf::COLS){ // down
            this->drawRectangle(Conf::ZOOM * 0.8f,
                                ((body[i - 1] / Conf::COLS) - (body[i + j] / Conf::COLS)) * Conf::ZOOM,
                                (body[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                (body[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                sf::Color(58, 191, 39));

        }

        i += (j + 1);
    }

    this->drawCircle(Conf::ZOOM * 0.4f,
                     (body[0] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                     (body[0] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                     sf::Color(0, 100, 255));
}
