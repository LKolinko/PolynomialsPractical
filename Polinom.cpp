#include "Polinom.h"


Polinom::Polinom(std::string &str) {
    FSM f(str);
    while (!f.is_end()) {
        auto u = f.getNode();
        data_.PushBack(node(u.first, u.second));
    }
    normalization();
    data_.Sort();
}

void Polinom::Print() {
    if (data_.getRoot() == nullptr) {
        std::cout << 0;
    }
    data_.Print();
}

Polinom& Polinom::operator=(const Polinom& other) {
    data_ = other.data_;
    return *this;
}

Polinom Polinom::operator-() {
    auto u = data_.getRoot();
    while (u != nullptr) {
        u->val.k *= -1;
        u = u->next;
    }
    return *this;
}

Polinom::Polinom(const Polinom &other) {
    data_ = other.data_;
}

Polinom Polinom::operator+(Polinom other) {
    Polinom res;
    auto u = data_.getRoot();
    for (; u != nullptr; u = u->next) {
        bool flag = true;
        for (auto e = other.data_.getRoot(); e != nullptr; e = e->next) {
            if (u->val.alph == e->val.alph) {
                node a = u->val;
                a.k += e->val.k;
                flag = false;
                if (a.k != 0) {
                    res.data_.PushBack(a);
                    break;
                }
            }
        }
        if (flag) {
            res.data_.PushBack(u->val);
        }
    }
    for (auto e = other.data_.getRoot(); e != nullptr; e = e->next) {
        bool flag = true;
        for (u = data_.getRoot(); u != nullptr; u = u->next) {
            if (u->val.alph == e->val.alph) {
                flag = false;
                break;
            }
        }
        if (flag) {
            res.data_.PushBack(e->val);
        }
    }
    res.data_.Sort();
    return res;
}

Polinom Polinom::operator-(Polinom other) {
    Polinom res = *this + -other;
    return res;
}

Polinom Polinom::operator+=(Polinom other) {
    *this = *this + other;
    return *this;
}

Polinom Polinom::operator-=(Polinom other) {
    *this = *this - other;
    return *this;
}

void Polinom::normalization() {
    Polinom res;
    std::set<std::vector<int>> st;
    for (auto u = data_.getRoot(); u != nullptr; u = u->next) {
        if (st.find(u->val.alph) != st.end()) {
            continue;
        }
        st.insert(u->val.alph);
        node a = u->val;
        for (auto e = data_.getRoot(); e != nullptr; e = e->next) {
            if (e != u && u->val.alph == e->val.alph) {
                a.k += e->val.k;
            }
        }
        if (a.k != 0) {
            res.data_.PushBack(a);
        }
    }
    *this = res;
}

Polinom Polinom::operator*(Polinom other) {
    Polinom res;
    for (auto u = data_.getRoot(); u != nullptr; u = u->next) {
        for (auto e = other.data_.getRoot(); e != nullptr; e = e->next) {
            res.data_.PushBack(u->val * e->val);
        }
    }
    res.normalization();
    res.data_.Sort();
    return res;
}

Polinom Polinom::operator*=(Polinom other) {
    *this = *this * other;
    return *this;
}

Polinom Polinom::operator*(int num) {
    Polinom res = *this;
    for (auto u = res.data_.getRoot(); u != nullptr; u = u->next) {
        u->val *= num;
    }
    return res;
}

Polinom Polinom::operator*=(int num) {
    *this = *this * num;
    return *this;
}

Polinom Polinom::Derivative(int k, char x) {
    Polinom res = *this;
    while (k--) {
        res = res.Derivative(x);
    }
    return res;
}

Polinom Polinom::Derivative(char x) {
    Polinom res;
    for (auto u = data_.getRoot(); u != nullptr; u = u->next) {
        if (u->val.alph[x - 'a']) {
            auto newAlph = u->val.alph;
            newAlph[x - 'a']--;
            res.data_.PushBack(node(newAlph, u->val.k * u->val.alph[x - 'a']));
        }
    }
    return res;
}
