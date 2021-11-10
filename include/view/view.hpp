#ifndef _VIEW_H
#define _VIEW_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../utils/config.hpp"

class View
{
    private:
        sf::RenderWindow m_window;
        
        std::map<sf::Keyboard::Key,bool> m_ctrl_inputs = {
                {sf::Keyboard::Left,  false}, // 1
                {sf::Keyboard::Right, false}, // 2
                {sf::Keyboard::Up,    false}, // 3
                {sf::Keyboard::Down,  false}  // 4
        };
        std::map<sf::Keyboard::Key,int>m_view_inputs = {
                {sf::Keyboard::S,  0}, // frame rate
                {sf::Keyboard::D,  0}  // debug view
        };

    protected:
        /*** 
         * TODO
         * 
         */
        sf::ConvexShape m_convex_shape_hcycle;
        sf::CircleShape m_circle_shape;
        sf::RectangleShape m_rectangle_shape;

    private:
        void handle_input_key_cont(sf::Event event, std::map<sf::Keyboard::Key,bool>& inputs);

        void handle_input_key_disc(sf::Event event, std::map<sf::Keyboard::Key,int>& inputs);
        
        void handle_input_all(sf::Event event, sf::RenderWindow& window);

        void frame_rate();

    protected:
        void draw_convex_shape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        void draw_circle_shape(float radius, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color,
                               sf::CircleShape* circle_shape = nullptr);

        void draw_rectangle_shape(float size_x, float size_y, float position_x, float position_y,
                                  int outline_thickness, sf::Color fill_color, sf::Color outline_color,
                                  sf::RectangleShape* rectangle_shape = nullptr);

        void draw_line_shape(float position_x1, float position_y1, float position_x2, float position_y2);

        int get_ctrl_input();

        bool is_debug_view();

        void wait_exit();

        void setup();

        void loop();

        virtual void view_setup() = 0;
        
        virtual void view_loop() = 0;

        virtual void ctrl_setup() = 0;
        
        virtual void ctrl_loop() = 0;

    public:
        View();
};

#endif