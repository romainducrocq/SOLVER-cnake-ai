#ifndef _VIEW_H
#define _VIEW_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class View{
    private:
        sf::RenderWindow m_window;
        sf::Clock m_clock;

        std::string m_name;
        float m_wait;
        
        std::map<sf::Keyboard::Key,bool> m_ctrl_inputs = {
                {sf::Keyboard::Left,  false}, // 1
                {sf::Keyboard::Right, false}, // 2
                {sf::Keyboard::Up,    false}, // 3
                {sf::Keyboard::Down,  false}  // 4
        }, m_view_inputs = {
                {sf::Keyboard::Space,  true}
        };

    protected:
        /*** 
         * TODO
         * 
         */
        int m_cols, m_rows, m_width, m_height, m_zoom;
        sf::ConvexShape convex_shape_hc;
        sf::CircleShape circle_shape_apple;
        std::vector<sf::RectangleShape> rectangle_shapes_snake;

    private:
        void handle_input_key_cont(sf::Event event, std::map<sf::Keyboard::Key,bool>& inputs);

        void handle_input_key_disc(sf::Event event, std::map<sf::Keyboard::Key,bool>& inputs);
        
        void handle_input_all(sf::Event event, sf::RenderWindow& window);

        bool is_wait();

        void frame_rate();

    public:
        View(std::string name, float wait, int cols, int rows, int zoom);

        void draw_convex_shape(sf::ConvexShape& convex_shape, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        void draw_circle_shape(sf::CircleShape& circle_shape, float position_x, float position_y,
                               int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        void draw_rectangle_shape(sf::RectangleShape& rectangle_shape, float position_x, float position_y,
                                  int outline_thickness, sf::Color fill_color, sf::Color outline_color);

        int get_ctrl_input();

        void wait_exit();

        void setup();

        void loop();

        virtual void view_setup() = 0;
        
        virtual void view_loop() = 0;

        virtual void ctrl_setup() = 0;
        
        virtual void ctrl_loop() = 0;
};

#endif