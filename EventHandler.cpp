//
// Created by lkolinko on 3/30/24.
//
#include "EventHandler.h"
#include <iostream>
#include <utility>

void EventHandler::scan(sf::RenderWindow *wnd) {
    sf::Event event{};
    if (wnd->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            wnd->close();
        }
        Update_(wnd, event);
    }
}

void EventHandler::Update_(sf::RenderWindow *wnd, sf::Event& event) {
    // some widgets updates
    bool IsUpdate = false;
    if (event.type == sf::Event::MouseMoved) {
        for (auto u : buttons_) {
            if (u->isMouseOver(*wnd)) {
                if (u->getColor() != 1) {
                    IsUpdate = true;
                }
                u->SetOtherColor();
            } else if (u->getColor() == 1) {
                u->SetSimpleColor();
                IsUpdate = true;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < (int)buttons_.size(); ++i) {
            auto u = buttons_[i];
            if (u->isMouseOver(*wnd)) {
                if (u->getColor() != 2) {
                    IsUpdate = true;
                }
                u->SetPassedColor();
            }
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        for (auto u : buttons_) {
            if (u->getColor() == 2) {
                u->SetSimpleColor();
                IsUpdate = true;
            }
        }
    }
    if (event.type == sf::Event::Resized) {
        sf::Vector2u windowSize = sf::Vector2u(event.size.width, event.size.height);
        wnd->setView(sf::View(sf::Vector2f((float) windowSize.x / 2.f, (float) windowSize.y / 2.f),
                              sf::Vector2f(windowSize)));
        for (int i = 0; i < (int)buttonsSettings_.size(); ++i) {
            auto u = buttonsSettings_[i];
            buttons_[i]->SetSize({ (float)windowSize.x * u[2], (float)windowSize.y * u[3] });
            buttons_[i]->SetPosition({ (float)windowSize.x * u[0], (float)windowSize.y * u[1] });
        }
        IsUpdate = true;
    }
    if (IsUpdate) {
        ReWrite(wnd);
    }
}

void EventHandler::ReWrite(sf::RenderWindow *wnd) {
    std::cout << 1 << std::endl;

    wnd->clear(sf::Color::White);

    // Buttons Rewrite
    for (auto u : buttons_) {
        u->Draw(*wnd);
    }

    wnd->display();
}

EventHandler::EventHandler(std::vector<Button*> buttons, std::vector<std::vector<float>> buttonsSettings) {
    buttons_ = std::move(buttons);
    buttonsSettings_ = std::move(buttonsSettings);
}

