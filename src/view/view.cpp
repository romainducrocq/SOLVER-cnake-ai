#include "../../include/view/view.hpp"

View::View()
{
    sf::ContextSettings options;
    options.antialiasingLevel = 0;

    this->m_window.create(sf::VideoMode(Conf::COLS * Conf::ZOOM, Conf::ROWS * Conf::ZOOM, 32), Conf::NAME, sf::Style::Default, options);
    this->m_window.setVerticalSyncEnabled(false);
}

/***
 * INPUTS
 * 
 */

void View::handle_input_key_cont(sf::Event event, std::map<sf::Keyboard::Key,bool>& inputs)
{
    if(event.type == sf::Event::KeyPressed){
        for (std::map<sf::Keyboard::Key,bool>::iterator it=inputs.begin(); it!=inputs.end(); ++it){
            if(event.key.code == it->first){
                it->second = true;
            }
        }
    }else if(event.type == sf::Event::KeyReleased){
        for (std::map<sf::Keyboard::Key,bool>::iterator it=inputs.begin(); it!=inputs.end(); ++it){
            if(event.key.code == it->first){
                it->second = false;
            }
        }
    }
}

void View::handle_input_key_disc(sf::Event event, std::map<sf::Keyboard::Key,int>& inputs)
{
    if(event.type == sf::Event::KeyReleased){
        for (std::map<sf::Keyboard::Key,int>::iterator it=inputs.begin(); it!=inputs.end(); ++it){
            if(event.key.code == it->first){
                it->second++;
            }
        }
    }
}

void View::handle_input_all(sf::Event event, sf::RenderWindow& window)
{
    if(event.type == sf::Event::Closed){
        window.close();
    }

    this->handle_input_key_cont(event, this->m_ctrl_inputs);
    this->handle_input_key_disc(event, this->m_view_inputs);
}

/***
 * SHAPES 
 * 
 */

void View::draw_convex_shape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                            int outline_thickness, sf::Color fill_color, sf::Color outline_color)
{
    convex_shape.setPosition(sf::Vector2f(position_x, position_y));
    convex_shape.setOutlineThickness(outline_thickness);
    convex_shape.setFillColor(fill_color);
    convex_shape.setOutlineColor(outline_color);
    this->m_window.draw(convex_shape);
}

void View::draw_circle_shape(float radius, float position_x, float position_y,
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
    this->m_window.draw(*circle_shape);

    if(p0){ delete circle_shape; }
}

void View::draw_rectangle_shape(float size_x, float size_y, float position_x, float position_y,
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
    this->m_window.draw(*rectangle_shape);

    if(p0){ delete rectangle_shape; }
}

void View::draw_line_shape(float position_x1, float position_y1, float position_x2, float position_y2)
{
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(position_x1, position_y1)),
            sf::Vertex(sf::Vector2f(position_x2, position_y2))
        };

        this->m_window.draw(line, 2, sf::Lines);
}

/***
 * 
 * 
 */

int View::get_ctrl_input()
{
    int i = 1;
    for (std::map<sf::Keyboard::Key,bool>::iterator it=this->m_ctrl_inputs.begin(); it!=this->m_ctrl_inputs.end(); ++it, ++i){
        if(it->second == true){
            return i;
        }
    }
    return 0;
}

void View::frame_rate()
{
    switch(this->m_view_inputs[sf::Keyboard::S] % 3){
    case 0:
        this->m_window.setFramerateLimit(24);
        break;
    case 1:
        this->m_window.setFramerateLimit(0);
        this->m_window.setVerticalSyncEnabled(true);
        break;
    case 2:
        this->m_window.setVerticalSyncEnabled(false);
    default:
        break;
    }
}

bool View::is_debug_view()
{
    return (this->m_view_inputs[sf::Keyboard::D] % 2);
}

void View::wait_exit()
{
    while (this->m_window.isOpen()){
        sf::Event event;
        while (this->m_window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                this->m_window.close();
        }
    }
}

/***
 *
 * 
 */

void View::setup()
{
    this->ctrl_setup();
    this->view_setup();
}

void View::loop()
{
    while(this->m_window.isOpen()){
        this->ctrl_loop();

        sf::Event event;
        while(this->m_window.pollEvent(event)){
            this->handle_input_all(event, this->m_window);
        }
        this->m_window.clear(sf::Color(51, 51, 51));
        this->view_loop();
        this->m_window.display();
        
        this->frame_rate();
    }
}
