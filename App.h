#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen.h"
#include "EventHandler.h"
#include "vector"
class App {
public:
    App();
    ~App();
    void run();
private:
    Locale locale_;
    EventHandler eventHandler;
    sf::RenderWindow* window;
    std::vector<Button*> buttons_;
    std::vector<std::vector<float>> ButtonSettings;
};
