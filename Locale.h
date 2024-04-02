#include "SFML/Graphics.hpp"
#include "Singleton.h"
#include "Table.h"
#include "Button.h"
#include "TextBox.h"
class Locale : public Singleton<Locale>{
public:
    sf::Color button;
    sf::Color buttonOther;
    sf::Color buttonPassed;
    sf::Color textBox;
    sf::Color textBoxPassed;
    sf::Color tableIn;
    sf::Color tableOut;
    sf::Font font;
    std::vector<Button*> buttons_;
    std::vector<TextBox*> texboxs_;
    Table* table_;

    void Init() {
        buttonOther = sf::Color(111, 146, 131);
        buttonPassed = sf::Color(105, 109, 125);
        button = sf::Color(141, 159, 135);
        textBoxPassed = sf::Color(233, 198, 165);
        textBox = sf::Color(205, 198, 165);
        tableIn = sf::Color(152, 193, 217);
        tableOut = sf::Color(58, 183, 149);
        font.loadFromFile("Arial.ttf");
    }
    ~Locale() {
        for (auto &u : buttons_) {
            delete u;
        }
        for (auto &u : texboxs_) {
            delete u;
        }
        delete table_;
    }
private:

};

