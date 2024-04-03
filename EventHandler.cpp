//
// Created by lkolinko on 3/30/24.
//

#include "EventHandler.h"
#include "Database.h"
#include <iostream>
#include <utility>
#include <sstream>

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
                    if (i == 0) ValueInPoint();
                    if (i == 1) Derivative();
                    if (i == 2) GetRoots();
                    if (i == 3) Comparison();
                    if (i == 4) Addition();
                    if (i == 5) Subtraction();
                    if (i == 6) Multiplication();
                    if (i == 7) Division();
                    if (i == 8) AddPolinom(0);
                    if (i == 9) AddPolinom(1);
                    if (i == 10) Delete();
                    if (i == 11) Save();
                    if (i == 12) Load();
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

void EventHandler::AddPolinom(int ind) {
    std::string str = Locale::GetInstance()->texboxs_[ind]->get_text();
    Polinom polinom;
    try {
        polinom = Polinom(str);
    } catch (const std::runtime_error& e) {
        std::string ans = e.what();
        Locale::GetInstance()->texboxs_[1]->SetText(ans);
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

void EventHandler::Delete() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.empty()) {
        return;
    }
    Locale::GetInstance()->table_->Remove(ind.front());
    Database::GetInstance()->Erase(ind.front());
}

void EventHandler::Comparison() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.size() < 2) {
        return;
    }
    Polinom first = Database::GetInstance()->GetPolinom(ind[0]);
    Polinom second = Database::GetInstance()->GetPolinom(ind[1]);
    std::string ans;
    if (first == second) {
        ans = "YES";
    } else {
        ans = "NO";
    }
    Locale::GetInstance()->texboxs_[1]->SetText(ans);
}

void EventHandler::Addition() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.size() < 2) {
        return;
    }
    Polinom first = Database::GetInstance()->GetPolinom(ind[0]);
    Polinom second = Database::GetInstance()->GetPolinom(ind[1]);
    first += second;
    std::string ans;
    ans = first.ToString();
    Locale::GetInstance()->texboxs_[1]->SetText(ans);
}

void EventHandler::Subtraction() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.size() < 2) {
        return;
    }
    Polinom first = Database::GetInstance()->GetPolinom(ind[0]);
    Polinom second = Database::GetInstance()->GetPolinom(ind[1]);
    first -= second;
    std::string ans;
    ans = first.ToString();
    Locale::GetInstance()->texboxs_[1]->SetText(ans);
}

void EventHandler::Multiplication() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.size() < 2) {
        return;
    }
    Polinom first = Database::GetInstance()->GetPolinom(ind[0]);
    Polinom second = Database::GetInstance()->GetPolinom(ind[1]);
    first *= second;
    std::string ans;
    ans = first.ToString();
    Locale::GetInstance()->texboxs_[1]->SetText(ans);
}

void EventHandler::ValueInPoint() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.empty()) {
        return;
    }
    std::string str = Locale::GetInstance()->texboxs_[0]->get_text();

    std::stringstream ss(str);
    std::vector<int> values(26, 0);
    std::string in;
    while (ss >> in) {
        char x = in.front();
        std::reverse(in.begin(), in.end());
        in.pop_back();
        in.pop_back();
        std::reverse(in.begin(), in.end());
        values[x - 'a'] = std::stoi(in);
    }

    Polinom polinom = Database::GetInstance()->GetPolinom(ind[0]);
    std::string ans = std::to_string(polinom.ValueInPoint(values));
    Locale::GetInstance()->texboxs_[1]->SetText(ans);
}

void EventHandler::Derivative() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.empty()) {
        return;
    }
    std::string str = Locale::GetInstance()->texboxs_[0]->get_text();

    std::stringstream ss(str);
    int n;
    char x;
    ss >> n >> x;
    Polinom polinom = Database::GetInstance()->GetPolinom(ind[0]);
    polinom = polinom.Derivative(n, x);
    std::string ans = polinom.ToString();
    Locale::GetInstance()->texboxs_[1]->SetText(ans);
}

void EventHandler::Division() {
    auto ind = Locale::GetInstance()->table_->GetFill();
    if (ind.size() < 2) {
        return;
    }
    Polinom first = Database::GetInstance()->GetPolinom(ind[0]);
    Polinom second = Database::GetInstance()->GetPolinom(ind[1]);
    Polinom res;
    try {
        res = first / second;
    } catch (const std::runtime_error& e) {
        std::string error = e.what();
        Locale::GetInstance()->texboxs_[1]->SetText(error);
        return;
    }
    Polinom ost = first - res * second;
    std::string ans1 = res.ToString(), ans2 = ost.ToString();
    Locale::GetInstance()->texboxs_[0]->SetText(ans1);
    Locale::GetInstance()->texboxs_[1]->SetText(ans2);
}

void EventHandler::Save() {
    std::string name = Locale::GetInstance()->texboxs_[2]->get_text();
    Database::GetInstance()->SaveToFile(name);
}

void EventHandler::Load() {
    std::string name = Locale::GetInstance()->texboxs_[3]->get_text();
    try {
        Database::GetInstance()->LoadFromFile(name);
    } catch (...) {
        return;
    }
    std::ifstream in(name);
    std::string a;
    while (in >> a) {
        Locale::GetInstance()->table_->PushBack(a);
    }
}

