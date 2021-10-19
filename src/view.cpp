#include "../include/view.h"

View::View(std::string name, float wait, int cols, int rows, int zoom)
    : m_name(name), m_wait(wait), m_cols(cols), m_rows(rows), m_width(cols * zoom), m_height(rows * zoom), m_zoom(zoom){
    sf::ContextSettings options;
    options.antialiasingLevel = 8;

    this->m_window.create(sf::VideoMode(this->m_width, this->m_height, 32), this->m_name, sf::Style::Default, options);
    this->m_window.setVerticalSyncEnabled(true);
}

/***
 * INPUTS
 * 
 */

void View::handle_input_key_cont(sf::Event event, std::map<sf::Keyboard::Key,bool>& inputs){
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

void View::handle_input_key_disc(sf::Event event, std::map<sf::Keyboard::Key,bool>& inputs){
    if(event.type == sf::Event::KeyReleased){
        for (std::map<sf::Keyboard::Key,bool>::iterator it=inputs.begin(); it!=inputs.end(); ++it){
            if(event.key.code == it->first){
                it->second = !it->second;
            }
        }
    }
}

void View::handle_input_all(sf::Event event, sf::RenderWindow& window){
    if(event.type == sf::Event::Closed){
        window.close();
    }

    this->handle_input_key_cont(event, this->m_ctrl_inputs);
    this->handle_input_key_disc(event, this->m_view_inputs);
}

bool View::is_wait(){
    return this->m_view_inputs[sf::Keyboard::Space];
}

/***
 * SHAPES 
 * 
 */

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

/***
 * 
 * 
 */

int View::get_ctrl_input() {
    int i = 1;
    for (std::map<sf::Keyboard::Key,bool>::iterator it=this->m_ctrl_inputs.begin(); it!=this->m_ctrl_inputs.end(); ++it, ++i){
        if(it->second == true){
            return i;
        }
    }
    return 0;
}

void View::frame_rate(){
    if(this->is_wait()){
        while(this->m_clock.getElapsedTime().asSeconds() <= this->m_wait) {}
        this->m_clock.restart();
    }
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

/***
 *
 * 
 */

void View::setup(){
    this->ctrl_setup();
    this->view_setup();
}

void View::loop(){
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
