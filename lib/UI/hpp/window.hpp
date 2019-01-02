#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

namespace UI
{
    class Window : virtual public UI::Component
    {
        /*
        Window();
        Window(int width, int height, sf::Color bg, );
        ~Window();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*);
        std::string create(std::string obj, std::string params);
        std::string getText();
    private:
        std::string text;
        bool isPressed;
        Action click;
        */
    };
}

#endif // UI_WINDOW_HPP
