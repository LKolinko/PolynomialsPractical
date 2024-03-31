#include "TextBox.h"
void TextBox::Create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, sf::Font &font, std::string str_title,
                     float radius) {
    back = RoundedRectangle(color, size, pos, radius);
    TextBoxWidth = size.x;
    TextBoxHeight = size.y;

    if (str_title.empty()) {
        is_title = false;
    } else {
        is_title = true;
    }

    title.setString(str_title);
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(back.vertic.getLocalBounds().height / 3.5);
    title.setFont(font);
    title.setPosition({ pos.x + 5, pos.y });

    text_.setFont(font);
    float xPos = pos.x + 5;
    float yPos = (pos.y + TextBoxHeight / 2.7);
    text_.setPosition(xPos, yPos);
    if (is_title) {
        text_.setCharacterSize(back.vertic.getLocalBounds().height / 3);
    } else {
        text_.setCharacterSize(back.vertic.getLocalBounds().height / 2);
    }
    text_.setFillColor(sf::Color::Black);

    position = pos;
    ft = radius;
}
void TextBox::Draw(sf::RenderWindow& wnd) {
    sf::RenderTexture textbox;

    textbox.create(static_cast<unsigned int>(back.horisont.getLocalBounds().width - ft / 2 - 5),
                 static_cast<unsigned int>(back.vertic.getLocalBounds().height / (is_title ? 2.5 : 1) - (is_title ? 0 : ft)));
    textbox.clear(back.getColor());

    back.Draw(wnd);

    wnd.draw(title);

    text_.setPosition(start, 0);
    textbox.draw(text_);


    textbox.display();
    sf::Sprite sprite(textbox.getTexture());
    if (is_title) {
        sprite.setPosition(position.x + 5, position.y + TextBoxHeight / 2.7 );
    } else {
        sprite.setPosition(position.x + ft / 2, position.y + ft / 2);

    }
    wnd.draw(sprite);
}

std::string TextBox::get_text() {
    return str_;
}

bool TextBox::isMousOver(sf::RenderWindow& wnd) {
    int mouseX = sf::Mouse::getPosition(wnd).x;
    int mouseY = sf::Mouse::getPosition(wnd).y;
    int btnPosX = position.x;
    int btnPosY = position.y;
    int btnxPosWidth = position.x + TextBoxWidth;
    int btnyPosHeight = position.y + TextBoxHeight;
    return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
}

void TextBox::Clear() {
    str_.clear();
    text_.setString(str_);
}

