#pragma once
#include <SFML/Graphics.hpp>
#include "RoundedRectangle.h"
class Button {
public:
    Button() = default;
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Color Back, sf::Color Other, sf::Color Passed, sf::Font& font,
           std::string btnText, float radius);
    ~Button() = default;

    void SetOtherColor();
    void SetPassedColor();
    void SetSimpleColor();
    void SetSize(sf::Vector2f size);
    void SetPosition(sf::Vector2f pos);
    void Draw(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);
    int getColor();
private:
    // Colors
    sf::Color Color_;
    sf::Color Passed_;
    sf::Color Other_;
    // Font;
    sf::Font font_;
    sf::Vector2f position_;
    RoundedRectangle button;
    sf::Text text;
    int btnWidth;
    int btnHeight;
};