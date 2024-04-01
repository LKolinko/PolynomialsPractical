#include "App.h"

void App::run() {
    while (window->isOpen()) {
        eventHandler.scan(window);
    }
}

App::App() {
    Screen::GetInstance()->Init();
    window = Screen::GetInstance()->window;
    window->clear(sf::Color::White);
    // buttons
    ButtonSettings = {
            { 0.01, 0.01, 0.3, 0.1 },
            { 0.01, 0.13, 0.3, 0.1 },
            { 0.01, 0.25, 0.3, 0.1 },
            { 0.01, 0.37, 0.3, 0.1 },
            { 0.01, 0.49, 0.3, 0.1 },
            { 0.01, 0.61, 0.3, 0.1 },
            { 0.01, 0.73, 0.3, 0.1 },
            { 0.01, 0.85, 0.3, 0.1 },
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
    sf::Vector2u size = window->getSize();
    for (int i = 0; i < (int)ButtonSettings.size(); ++i) {
        auto u = ButtonSettings[i];
        Button* bnt = new Button({ (float)size.x * u[2], (float)size.y * u[3] },
                                 { (float)size.x * u[0], (float)size.y * u[1] },
                                 locale_.button, locale_.buttonOther,
                                 locale_.buttonPassed, locale_.font, buttonsTitles_[i], 10);
        buttons_.push_back(bnt);
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
                                   locale_.textBox, locale_.textBoxPassed, locale_.font, texboxTitles_[i], 10);
        texboxs_.push_back(text);
    }
    eventHandler = EventHandler(buttons_, ButtonSettings, texboxs_, textboxSettings_);
}

App::~App() {
    for (auto u : buttons_) {
        delete u;
    }
    for (auto u : texboxs_) {
        delete u;
    }
}
