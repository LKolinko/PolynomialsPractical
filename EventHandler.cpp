//
// Created by lkolinko on 3/30/24.
//

#include "EventHandler.h"
#include "Database.h"
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
        for (auto u : Locale::GetInstance()->buttons_) {
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
        for (int i = 0; i < (int)Locale::GetInstance()->buttons_.size(); ++i) {
            auto u = Locale::GetInstance()->buttons_[i];
            if (u->isMouseOver(*wnd)) {
                if (u->getColor() != 2) {
                    if (i == 2) GetRoots();
                    if (i == 8) AddPolinom();
                    IsUpdate = true;
                }
                u->SetPassedColor();
            }
        }
        for (auto u : Locale::GetInstance()->texboxs_) {
            if (u->isMousOver(*wnd)) {
                if (u->getColor() != 1) {
                    IsUpdate = true;
                }
                u->SetPressed();
            } else if (u->getColor() == 1) {
                IsUpdate = true;
                u->SetSimple();
            }
        }
        if (Locale::GetInstance()->table_->isMouseOver(*wnd)) {
            Locale::GetInstance()->table_->FillCeil(wnd);
            IsUpdate = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        for (auto u : Locale::GetInstance()->buttons_) {
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
            Locale::GetInstance()->buttons_[i]->SetSize({ (float)windowSize.x * u[2], (float)windowSize.y * u[3] });
            Locale::GetInstance()->buttons_[i]->SetPosition({ (float)windowSize.x * u[0], (float)windowSize.y * u[1] });
        }
        for (int i = 0; i < (int)textboxsSettings_.size(); ++i) {
            auto u = textboxsSettings_[i];
            Locale::GetInstance()->texboxs_[i]->SetSize({ (float)windowSize.x * u[2], (float)windowSize.y * u[3] });
            Locale::GetInstance()->texboxs_[i]->SetPosition({ (float)windowSize.x * u[0], (float)windowSize.y * u[1] });
        }
        Locale::GetInstance()->table_->SetSize({ (float)windowSize.x * tableSettings_[2], (float)windowSize.y * tableSettings_[3] });
        Locale::GetInstance()->table_->SetPosition({ (float)windowSize.x * tableSettings_[0], (float)windowSize.y * tableSettings_[1] });
        IsUpdate = true;
    }
    if (event.type == sf::Event::TextEntered) {
        for (int i = 0; i < (int)Locale::GetInstance()->texboxs_.size(); ++i) {
            if (Locale::GetInstance()->texboxs_[i]->getColor() == 1) {
                if (event.key.code == 13) {
                    Locale::GetInstance()->texboxs_[i]->SetSimple();
                } else {
                    if (event.key.code == 8 || event.key.code == 127) {
                        Locale::GetInstance()->texboxs_[i]->RemoveSimbol();
                    } else {
                        char c = static_cast<char>(event.key.code);
                        Locale::GetInstance()->texboxs_[i]->AddSimbol(c);
                    }
                }
                IsUpdate = true;
            }
        }
    }
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (Locale::GetInstance()->table_->isMouseOver(*wnd)) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                Locale::GetInstance()->table_->Scroll(std::make_pair((int) event.mouseWheelScroll.delta, 0));
            } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                Locale::GetInstance()->table_->Scroll(std::make_pair(0, (int) event.mouseWheelScroll.delta));
            }
            IsUpdate = true;
        }
    }
    if (IsUpdate) {
        ReWrite(wnd);
    }
}

void EventHandler::ReWrite(sf::RenderWindow *wnd) {

    wnd->clear(sf::Color::White);

    // Buttons Rewrite
    for (auto u : Locale::GetInstance()->buttons_) {
        u->Draw(*wnd);
    }
    // Textboxs Rewrite
    for (auto u : Locale::GetInstance()->texboxs_) {
        u->Draw(*wnd);
    }
    // Table Rewrite
    Locale::GetInstance()->table_->Draw(*wnd);
    wnd->display();
}

EventHandler::EventHandler(std::vector<std::vector<float>>& buttonsSettings,
                           std::vector<std::vector<float>>& TextboxsSettings,
                           std::vector<float>& tableSettings) {
    buttonsSettings_ = buttonsSettings;
    textboxsSettings_ = TextboxsSettings;
    tableSettings_ = tableSettings;
}

void EventHandler::AddPolinom() {
    std::string str = Locale::GetInstance()->texboxs_[0]->get_text();
    Polinom polinom;
    try {
        polinom = Polinom(str);
    } catch (std::runtime_error) {
        return;
    }
    str = polinom.ToString();
    Locale::GetInstance()->table_->PushBack(str);
    Database::GetInstance()->Add(polinom);
}

void EventHandler::GetRoots() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.empty()) {
        return;
    }
    std::vector<int> res = Database::GetInstance()->GetPolinom(ind.front()).getRoots();
    std::string text;
    for (int i = 0; i < (int)res.size(); ++i) {
        text += std::to_string(res[i]);
        text.push_back(' ');
    }
    Locale::GetInstance()->texboxs_[1]->SetText(text);
}

