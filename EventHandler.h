#include <SFML/Graphics.hpp>
#include <stack>
#include "Locale.h"
#include "Button.h"
class EventHandler {
public:
    EventHandler(std::vector<Button*> buttons, std::vector<std::vector<float>> buttonsSettings);
    EventHandler() = default;
    void scan(sf::RenderWindow* wnd);
    void ReWrite(sf::RenderWindow* wnd);
private:
    void Update_(sf::RenderWindow* wnd, sf::Event& event);
    std::vector<Button*> buttons_;
    std::vector<std::vector<float>> buttonsSettings_;
};
