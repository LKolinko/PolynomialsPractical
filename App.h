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
    Table* table_;
    std::vector<float> tableSettings_;
    std::vector<Button*> buttons_;
    std::vector<TextBox*> texboxs_;
    std::vector<std::string> texboxTitles_;
    std::vector<std::vector<float>> textboxSettings_;
    std::vector<std::string> buttonsTitles_;
    std::vector<std::vector<float>> ButtonSettings;
};
