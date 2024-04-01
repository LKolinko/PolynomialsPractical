#include <SFML/Graphics.hpp>
#include <stack>
#include "Table.h"
#include "Locale.h"
#include "Button.h"
#include "TextBox.h"
class EventHandler {
public:
    EventHandler(std::vector<Button*> buttons, std::vector<std::vector<float>> buttonsSettings,
                 std::vector<TextBox*> Textboxs, std::vector<std::vector<float>> TextboxsSettings,
                 Table* table, std::vector<float> tableSettings);
    EventHandler() = default;
    void scan(sf::RenderWindow* wnd);
    void ReWrite(sf::RenderWindow* wnd);
private:
    void Update_(sf::RenderWindow* wnd, sf::Event& event);
    Table* table_;
    std::vector<float> tableSettings_;
    std::vector<Button*> buttons_;
    std::vector<TextBox*> textboxs_;
    std::vector<std::vector<float>> buttonsSettings_;
    std::vector<std::vector<float>> textboxsSettings_;
};
