#include "../include/view.h"

View::View(std::string name, int cols, int rows, int zoom, float wait)
    : m_name(name), m_cols(cols), m_rows(rows), m_width(cols * zoom), m_height(rows * zoom), m_zoom(zoom), m_wait(wait){
    sf::ContextSettings options;
    options.antialiasingLevel = 8;

    this->m_window.create(sf::VideoMode(this->m_width, this->m_height, 32), this->m_name, sf::Style::Default, options);
    this->m_window.setVerticalSyncEnabled(true);

    this->setup();
}

void View::wait_exit(){
    while (this->m_window.isOpen()){
        sf::Event event;
        while (this->m_window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                this->m_window.close();
        }
    }
}

int View::get_input() {
    int i = 1;
    for (std::map<int,int>::iterator it=this->m_inputs.begin(); it!=this->m_inputs.end(); ++it, ++i){
        if(it->second == true){
            return i;
        }
    }
    return 0;
}

void View::handle_input(sf::Event event, sf::RenderWindow& window){
    if(event.type == sf::Event::Closed){
        window.close();
    }

    if(event.type == sf::Event::KeyPressed){
        for (std::map<int,int>::iterator it=this->m_inputs.begin(); it!=this->m_inputs.end(); ++it){
            if(event.key.code == it->first){
                it->second = true;
            }
        }
    }else if(event.type == sf::Event::KeyReleased){
        for (std::map<int,int>::iterator it=this->m_inputs.begin(); it!=this->m_inputs.end(); ++it){
            if(event.key.code == it->first){
                it->second = false;
            }
        }
    }
}

void View::draw_circle_shape(sf::CircleShape& circle_shape, float position_x, float position_y,
                            int outline_thickness, sf::Color fill_color, sf::Color outline_color){
    circle_shape.setPosition(sf::Vector2f(position_x, position_y));
    circle_shape.setOutlineThickness(outline_thickness);
    circle_shape.setFillColor(fill_color);
    circle_shape.setOutlineColor(outline_color);
    this->m_window.draw(circle_shape);
}

void View::draw_rectangle_shape(sf::RectangleShape& rectangle_shape, float position_x, float position_y,
                                int outline_thickness, sf::Color fill_color, sf::Color outline_color){
    rectangle_shape.setPosition(sf::Vector2f(position_x, position_y));
    rectangle_shape.setOutlineThickness(outline_thickness);
    rectangle_shape.setFillColor(fill_color);
    rectangle_shape.setOutlineColor(outline_color);
    this->m_window.draw(rectangle_shape);
}

bool View::loop(const Model& model){
    if(this->m_window.isOpen()){
        sf::Event event;
        while(this->m_window.pollEvent(event)){
            this->handle_input(event, this->m_window);
        }
        this->draw(model);
        
        while(this->m_clock.getElapsedTime().asSeconds() <= this->m_wait) {}
        this->m_clock.restart();
        return true;
    }
    return false;
}

/***
 * TODO
 * 
 */

void View::setup(){
    this->circle_shape_apple = sf::CircleShape(m_zoom / 2);
    this->rectangle_shapes_snake.push_back(sf::RectangleShape(sf::Vector2f(m_zoom, m_zoom)));
}

void View::draw(const Model& model){
    this->m_window.clear(sf::Color(51, 51, 51));

    this->draw_circle_shape(
        this->circle_shape_apple, model.m_apple.get_pos().x * m_zoom, model.m_apple.get_pos().y * m_zoom, 
        1, sf::Color(255, 0, 100), sf::Color(0, 0, 0));

    if(model.m_snake.get_size() > this->rectangle_shapes_snake.size()){
        this->rectangle_shapes_snake.push_back(sf::RectangleShape(sf::Vector2f(m_zoom, m_zoom)));
    }

    for(size_t i = 0; i < model.m_snake.get_size(); i++){
            this->draw_rectangle_shape(
                this->rectangle_shapes_snake[i], model.m_snake.get_pos(i).x * m_zoom, model.m_snake.get_pos(i).y * m_zoom,
                1, sf::Color(58, 191, 39), sf::Color(0, 0, 0));
    }

    this->m_window.display();
}
