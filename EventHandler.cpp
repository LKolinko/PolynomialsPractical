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

EventHandler::EventHandler(std::vector<Button*> buttons) {
    buttons_ = std::move(buttons);
}

