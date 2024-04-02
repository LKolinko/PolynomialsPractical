#include "App.h"

void App::run() {
    while (Screen::GetInstance()->window->isOpen()) {
        eventHandler.scan(Screen::GetInstance()->window);
    }
}

App::App() {
    Screen::GetInstance()->Init();
    Locale::GetInstance()->Init();
    Screen::GetInstance()->window->clear(sf::Color::White);
    // buttons
    ButtonSettings = {
            { 0.01, 0.01, 0.3, 0.1 },
            { 0.01, 0.13, 0.3, 0.1 },
            { 0.01, 0.25, 0.3, 0.1 },
            { 0.01, 0.37, 0.145, 0.1 },
            { 0.165, 0.37, 0.145, 0.1 },
            { 0.01, 0.49, 0.145, 0.1 },
            { 0.165, 0.49, 0.145, 0.1 },
            { 0.01, 0.61, 0.3, 0.1 },
            { 0.33, 0.01, 0.2, 0.1 },
            { 0.33, 0.13, 0.2, 0.1 },
    };
    buttonsTitles_ = {
            "value at point",
            "n-derivative",
            "find roots",
            "a == b",
            "a + b",
            "a - b",
            "a * b",
            "a / b",
            "add",
            "add",
    };
    sf::Vector2u size = Screen::GetInstance()->window->getSize();
    for (int i = 0; i < (int)ButtonSettings.size(); ++i) {
        auto u = ButtonSettings[i];
        Button* bnt = new Button({ (float)size.x * u[2], (float)size.y * u[3] },
                                 { (float)size.x * u[0], (float)size.y * u[1] },
                                 Locale::GetInstance()->button, Locale::GetInstance()->buttonOther,
                                 Locale::GetInstance()->buttonPassed, Locale::GetInstance()->font, buttonsTitles_[i], 10);
        Locale::GetInstance()->buttons_.push_back(bnt);
    }
    // textboxs
    textboxSettings_ = {
            { 0.55, 0.01, 0.43, 0.1 },
            { 0.55, 0.13, 0.43, 0.1 }
    };
    texboxTitles_ = {
            "Input:",
            "Result:",
    };
    for (int i = 0; i < (int)textboxSettings_.size(); ++i) {
        auto u = textboxSettings_[i];
        TextBox* text = new TextBox({ (float)size.x * u[2], (float)size.y * u[3] },
                                   { (float)size.x * u[0], (float)size.y * u[1] },
                                   Locale::GetInstance()->textBox, Locale::GetInstance()->textBoxPassed, Locale::GetInstance()->font, texboxTitles_[i], 10);
        Locale::GetInstance()->texboxs_.push_back(text);
    }
    // table
    tableSettings_ = { 0.33, 0.25, 0.65, 0.7, 100, 50 };
    Locale::GetInstance()->table_ = new Table({ (float)size.x * tableSettings_[2], (float)size.y * tableSettings_[3] },
                       { (float)size.x * tableSettings_[0], (float)size.y * tableSettings_[1] },
                       Locale::GetInstance()->tableOut, Locale::GetInstance()->tableIn, 10, 10, { tableSettings_[4], tableSettings_[5] },
                       Locale::GetInstance()->font);

    eventHandler = EventHandler(ButtonSettings, textboxSettings_, tableSettings_);
}
