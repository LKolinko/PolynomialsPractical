#include <sstream>
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
    auto first = this->data_.getRoot();
    auto second = other.data_.getRoot();
    while (first != nullptr && second != nullptr) {
        if (first->val.alph == second->val.alph) {
            if (first->val.k + second->val.k != 0) {
                res.data_.PushBack(first->val + second->val);
            }
            first = first->next;
            second = second->next;
        } else if (first->val > second->val) {
            res.data_.PushBack(first->val);
            first = first->next;
        } else {
            res.data_.PushBack(second->val);
            second = second->next;
        }
    }
    while (first != nullptr) {
        res.data_.PushBack(first->val);
        first = first->next;
    }
    while (second != nullptr) {
        res.data_.PushBack(second->val);
        second = second->next;
    }
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
            node a = (u->val * e->val);
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

std::string Polinom::ToString() {
    std::string str;
    std::stringstream ss;
    if (data_.getRoot() == nullptr) {
        ss << 0;
    }
    for (auto u = data_.getRoot(); u != nullptr; u = u->next) {
        ss << u->val;
    }
    ss >> str;
    if (str.front() == '+') {
        std::string ans;
        for (int i = 1; i < str.size(); ++i) {
            ans.push_back(str[i]);
        }
        str = ans;
    }
    return str;
}

int Polinom::ValueInPoint(std::vector<int> &values) {
    int res = 0;
    for (auto u = data_.getRoot(); u != nullptr; u = u->next) {
        int tec = u->val.k;
        for (int i = 0; i < 26; ++i) {
            tec *= pow(values[i], u->val.alph[i]);
        }
        res += tec;
    }
    return res;
}

bool Polinom::operator==(Polinom &other) {
    return data_ == other.data_;
}

std::vector<int> Polinom::getRoots() {
    std::vector<int> res;
    int free;
    int x;
    auto u = data_.getRoot();
    while (u->next != nullptr) {
        int cnt = 0;
        for (int i = 0; i < 26; ++i) {
            if (u->val.alph[i]) {
                ++cnt;
                x = i;
            }
            if (cnt >= 2) {
                throw std::runtime_error("NO, hohoho");
            }
        }
        u = u->next;
    }
    for (auto e : u->val.alph) {
        if (e) {
            free = 0;
            std::vector<int> values(26, 0);
            if (ValueInPoint(values) == 0) {
                return { 0 };
            }
        }
    }
    free = u->val.k;
    for (int i = -abs(free); i <= abs(free); ++i) {
        if (i == 0) continue;
        std::vector<int> values(26, 0);
        values[x] = i;
        if (free % i == 0 && ValueInPoint(values) == 0) {
            res.push_back(i);
        }
    }
    return res;
}

Polinom Polinom::operator/(Polinom other) {

    if (other.data_.getRoot() == nullptr) {
        throw std::runtime_error("stupid");
    }

    for (auto u = data_.getRoot(); u != nullptr; u = u->next) {
        int cnt = 0;
        for (int i = 0; i < 26; ++i) {
            if (u->val.alph[i]) {
                ++cnt;
            }
        }
        if (cnt > 1) {
            throw std::runtime_error("more than one variable");
        }
    }


    for (auto u = other.data_.getRoot(); u != nullptr; u = u->next) {
        int cnt = 0;
        for (int i = 0; i < 26; ++i) {
            if (u->val.alph[i]) {
                ++cnt;
            }
        }
        if (cnt > 1) {
            throw std::runtime_error("more than one variable");
        }
    }

    Polinom res;
    Polinom copy = *this;
    while (true) {
        if (copy.data_.getRoot() == nullptr) {
            break;
        }
        node resNode = copy.data_.getRoot()->val / other.data_.getRoot()->val;

        if (resNode.k == 0) {
            break;
        }

        res.data_.PushBack(resNode);
        Polinom del;
        del.data_.PushBack(resNode);

        copy -= other * del;

    }
    return res;
}
