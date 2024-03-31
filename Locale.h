#include "SFML/Graphics.hpp"

class Locale {
public:
    sf::Color button;
    sf::Color buttonOther;
    sf::Color buttonPassed;
    sf::Color textBox;
    sf::Color textBoxPassed;
    sf::Color tableIn;
    sf::Color tableOut;
    sf::Font font;

    Locale() {
        buttonOther = sf::Color(111, 146, 131);
        buttonPassed = sf::Color(105, 109, 125);
        button = sf::Color(141, 159, 135);
        font.loadFromFile("Arial.ttf");
    }
private:

};

