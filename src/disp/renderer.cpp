#include "disp/renderer.hpp"

Renderer::Renderer(sf::RenderTarget& target)
    : m_target(target)
{}

void Renderer::drawConvexShape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color)
{
    convex_shape.setPosition(sf::Vector2f(position_x, position_y));
    convex_shape.setOutlineThickness(outline_thickness);
    convex_shape.setFillColor(fill_color);
    convex_shape.setOutlineColor(outline_color);
    this->m_target.draw(convex_shape);
}

void Renderer::drawCircleShape(float radius, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color,
                               sf::CircleShape* circle_shape)
{
    bool p0 = circle_shape == nullptr;
    if(p0){ circle_shape = new sf::CircleShape(); }

    circle_shape->setRadius(radius);
    circle_shape->setPosition(sf::Vector2f(position_x, position_y));
    circle_shape->setOutlineThickness(outline_thickness);
    circle_shape->setFillColor(fill_color);
    circle_shape->setOutlineColor(outline_color);
    this->m_target.draw(*circle_shape);

    if(p0){ delete circle_shape; }
}

void Renderer::drawRectangleShape(float size_x, float size_y, float position_x, float position_y,
                                  int outline_thickness, sf::Color fill_color, sf::Color outline_color,
                                  sf::RectangleShape* rectangle_shape)
{
    bool p0 = rectangle_shape == nullptr;
    if(p0){ rectangle_shape = new sf::RectangleShape(); }

    rectangle_shape->setSize(sf::Vector2f(size_x, size_y));
    rectangle_shape->setPosition(sf::Vector2f(position_x, position_y));
    rectangle_shape->setOutlineThickness(outline_thickness);
    rectangle_shape->setFillColor(fill_color);
    rectangle_shape->setOutlineColor(outline_color);
    this->m_target.draw(*rectangle_shape);

    if(p0){ delete rectangle_shape; }
}

void Renderer::drawLineShape(float position_x1, float position_y1, float position_x2, float position_y2)
{
    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(position_x1, position_y1)),
            sf::Vertex(sf::Vector2f(position_x2, position_y2))
    };

    this->m_target.draw(line, 2, sf::Lines);
}

/***
 * INIT
 *
 */

void Renderer::initShapeHCycle(const int* hcyle)
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
 * RENDER
 *
 */

void Renderer::renderShapeHCycle(bool is_debug)
{
    if(is_debug){
        // draw hamiltonian cycle
        this->drawConvexShape(this->m_convex_shape_hcycle,
                                Conf::ZOOM / 2,
                                Conf::ZOOM / 2,
                                1, sf::Color::Transparent, sf::Color(220, 220, 220));
    }
}

void Renderer::renderShapeApple(int pos)
{
    // draw apple
    this->drawCircleShape(Conf::ZOOM * 0.4f,
                          (pos % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                          (pos / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                          0, sf::Color(255, 0, 100), sf::Color::Transparent, &this->m_circle_shape);
}

void Renderer::renderShapeSnake(const std::vector<int>& body)
{
    // draw snake
    size_t i = 1;
    while (i < body.size()){

        size_t j = 0;
        while((i + j) < body.size() &&
              body[i] - body[i - 1] ==
              body[i + j + 1] - body[i + j])
        { j++; }

        this->drawCircleShape(Conf::ZOOM * 0.4f,
                              (body[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                              (body[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                              0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->m_circle_shape);

        if(body[i] - body[i - 1] == 1){                 // left
            this->drawRectangleShape(((body[i + j] % Conf::COLS) - (body[i - 1] % Conf::COLS)) * Conf::ZOOM,
                                     Conf::ZOOM * 0.8f,
                                     (body[i - 1] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                     (body[i - 1] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                     0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->m_rectangle_shape);

        }else if(body[i] - body[i - 1] == -1){          // right
            this->drawRectangleShape(((body[i - 1] % Conf::COLS) - (body[i + j] % Conf::COLS)) * Conf::ZOOM,
                                     Conf::ZOOM * 0.8f,
                                     (body[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                     (body[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                     0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->m_rectangle_shape);

        }else if(body[i] - body[i - 1] == Conf::COLS){  // up
            this->drawRectangleShape(Conf::ZOOM * 0.8f,
                                     ((body[i + j] / Conf::COLS) - (body[i - 1] / Conf::COLS)) * Conf::ZOOM,
                                     (body[i - 1] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                     (body[i - 1] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                     0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->m_rectangle_shape);

        }else if(body[i] - body[i - 1] == -Conf::COLS){ // down
            this->drawRectangleShape(Conf::ZOOM * 0.8f,
                                     ((body[i - 1] / Conf::COLS) - (body[i + j] / Conf::COLS)) * Conf::ZOOM,
                                     (body[i + j] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                                     (body[i + j] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.5f,
                                     0, sf::Color(58, 191, 39), sf::Color::Transparent, &this->m_rectangle_shape);

        }

        i += (j + 1);
    }

    this->drawCircleShape(Conf::ZOOM * 0.4f,
                          (body[0] % Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                          (body[0] / Conf::COLS) * Conf::ZOOM + Conf::ZOOM * 0.1f,
                          0, sf::Color(0, 100, 255), sf::Color::Transparent, &this->m_circle_shape);
}
