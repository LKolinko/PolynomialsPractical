#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen.h"
#include "EventHandler.h"
#include "vector"
class App {
public:
    App();
    ~App() = default;
    void run();
private:
    EventHandler eventHandler;
    std::vector<float> tableSettings_;
    std::vector<std::string> texboxTitles_;
    std::vector<std::vector<float>> textboxSettings_;
    std::vector<std::string> buttonsTitles_;
    std::vector<std::vector<float>> ButtonSettings;
};
