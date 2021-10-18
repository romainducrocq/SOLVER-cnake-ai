#ifndef _VIEW_H
#define _VIEW_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "model.h"

class View{
    private:
        std::string m_name;
        int m_cols, m_rows, m_width, m_height, m_zoom;
        float m_wait;
        
        std::map<int,int> m_inputs = {
                {sf::Keyboard::Left,  false}, // 1
                {sf::Keyboard::Right, false}, // 2
                {sf::Keyboard::Up,    false}, // 3
                {sf::Keyboard::Down,  false}  // 4
        }; 


        sf::RenderWindow m_window;
        sf::Clock m_clock;

    private:
        /*** 
         * TODO
         * 
         */
        sf::CircleShape circle_shape_apple;
        std::vector<sf::RectangleShape> rectangle_shapes_snake;

    public:
        View(std::string name, int cols, int rows, int zoom, float wait);

        int get_input();

        void handle_input(sf::Event event, sf::RenderWindow& window);

        void draw_circle_shape(sf::CircleShape& circle_shape, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        void draw_rectangle_shape(sf::RectangleShape& rectangle_shape, float position_x, float position_y,
                                  int outline_thickness, sf::Color fill_color, sf::Color outline_color);


        void setup();
        bool loop(const Model& model);
        void draw(const Model& model);
};

#endif