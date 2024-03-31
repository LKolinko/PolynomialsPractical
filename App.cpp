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
    ButtonSettings = {
            { 0.01, 0.05, 0.3, 0.15 }, //+
            { 0.01, 0.22, 0.3, 0.15 }, //-
            { 0.01, 0.39, 0.3, 0.15 }, //*
            { 0.01, 0.56, 0.3, 0.15 }, //(/)
            { 0.01, 0.73, 0.3, 0.15 }, // Proisz
    };
    sf::Vector2u size = window->getSize();
    for (auto u : ButtonSettings) {
        Button* bnt = new Button({ (float)size.x * u[2], (float)size.y * u[3] },
                                 { (float)size.x * u[0], (float)size.y * u[1] },
                                 locale_.button, locale_.buttonOther,
                                 locale_.buttonPassed, locale_.font, "Button", 10);
        buttons_.push_back(bnt);
    }
    eventHandler = EventHandler(buttons_);
    eventHandler.ReWrite(window);
}

App::~App() {
    for (auto u : buttons_) {
        delete u;
    }
}
