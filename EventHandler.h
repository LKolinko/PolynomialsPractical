#include <SFML/Graphics.hpp>
#include <stack>
#include "Locale.h"
#include "Button.h"
class EventHandler {
public:
    EventHandler(std::vector<Button*> buttons);
    EventHandler() = default;
    void scan(sf::RenderWindow* wnd);
    void ReWrite(sf::RenderWindow* wnd);
private:
    void Update_(sf::RenderWindow* wnd, sf::Event& event);
    std::vector<Button*> buttons_;
    std::stack<sf::Event> events_;
};
