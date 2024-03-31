#include "Button.h"

void Button::Draw(sf::RenderWindow &window) {
    text.setFont(font_);
    button.Draw(window);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int btnPosX = button.position.x;
    int btnPosY = button.position.y;
    int btnxPosWidth = button.position.x + btnWidth;
    int btnyPosHeight = button.position.y + btnHeight;
    return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color Back, sf::Color Other, sf::Color Passed, sf::Font &font,
               std::string btnText, float radius) {

    Color_ = Back;
    Other_ = Other;
    Passed_ = Passed;

    font_ = font;

    btnWidth = size.x;
    btnHeight = size.y;
    button.Create(Back, size, pos, radius);

    text.setString(btnText);
    text.setCharacterSize(button.vertic.getLocalBounds().height / 3);
    text.setFillColor(sf::Color::Black);
    text.setFont(font);

    float xPos = (pos.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
    float yPos = (pos.y + btnHeight / 2.7) - (text.getLocalBounds().height / 2);

    text.setPosition(xPos, yPos);
}

void Button::SetOtherColor() {
    button.SetColor(Other_);
}

void Button::SetPassedColor() {
    button.SetColor(Passed_);
}

int Button::getColor() {
    if (button.getColor() == Color_) {
        return 0;
    }
    if (button.getColor() == Other_) {
        return 1;
    }
    return 2;
}

void Button::SetSimpleColor() {
    button.SetColor(Color_);
}
