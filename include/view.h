#ifndef _VIEW_H
#define _VIEW_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class View{
    private:
        std::string m_name;
        float m_wait;
        
        std::map<int,int> m_ctrl_inputs = {
                {sf::Keyboard::Left,  false}, // 1
                {sf::Keyboard::Right, false}, // 2
                {sf::Keyboard::Up,    false}, // 3
                {sf::Keyboard::Down,  false}  // 4
        }; 

        sf::RenderWindow m_window;
        sf::Clock m_clock;

    protected:
        /*** 
         * TODO
         * 
         */
        int m_cols, m_rows, m_width, m_height, m_zoom;
        sf::CircleShape circle_shape_apple;
        std::vector<sf::RectangleShape> rectangle_shapes_snake;

    public:
        View(std::string name, float wait, int cols, int rows, int zoom);

        void wait_exit();

        int get_ctrl_input();

        void handle_input(sf::Event event, sf::RenderWindow& window);

        void draw_circle_shape(sf::CircleShape& circle_shape, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        void draw_rectangle_shape(sf::RectangleShape& rectangle_shape, float position_x, float position_y,
                                  int outline_thickness, sf::Color fill_color, sf::Color outline_color);


        void setup();

        void loop();

        virtual void view_setup() = 0;
        
        virtual void view_loop() = 0;

        virtual void ctrl_setup() = 0;
        
        virtual void ctrl_loop() = 0;
};

#endif