#include <SFML/Graphics.hpp>
#include <stack>
#include "Table.h"
#include "Locale.h"
#include "Button.h"
#include "TextBox.h"
class EventHandler {
public:
    EventHandler(std::vector<std::vector<float>>& buttonsSettings,
                 std::vector<std::vector<float>>& TextboxsSettings,
                 std::vector<float>& tableSettings);
    EventHandler() = default;
    ~EventHandler() = default;
    void scan(sf::RenderWindow* wnd);
    void ReWrite(sf::RenderWindow* wnd);
private:
    void AddPolinom();
    void GetRoots();
    void Delete();
    void Comparison();
    void Addition();
    void Subtraction();
    void Multiplication();
    void ValueInPoint();
    void Derivative();
    void Division();

    void Update_(sf::RenderWindow* wnd, sf::Event& event);
    std::vector<float> tableSettings_;
    std::vector<std::vector<float>> buttonsSettings_;
    std::vector<std::vector<float>> textboxsSettings_;
};
