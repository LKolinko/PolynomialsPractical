#include "FSM.h"

FSM::FSM(std::string a) {
    if (a[0] != '+' && a[0] != '-') {
        a = "+" + a;
    }
    str_ = a;
    ind = 0;
    state = 0;
}

std::pair<std::vector<int>, int> FSM::getNode() {
    std::vector<int> alph(26, 0);
    int k = -1, sign = 1, cnt = 0;
    char teck = '/';
    while (ind != str_.size()) {
        if (state == 0) {
            if (str_[ind] == '-') {
                state = 1;
                sign = -1;
            } else if (str_[ind] == '+') {
                state = 1;
                sign = 1;
            } else {
                std::string error = "expected sign received: ";
                error.push_back(str_[ind]);
                throw std::runtime_error(error);
            }
            ++ind;
            state = 1;
        } else if (state == 1) {
            if (str_[ind] >= '0' && str_[ind] <= '9') {
                if (k == -1) {
                    k = 0;
                }
                k *= 10;
                k += (str_[ind] - '0');
                ++ind;
            } else if (str_[ind] >= 'a' && str_[ind] <= 'z') {
                if (k == -1) {
                    k = 1;
                }
                state = 2;
            } else if ((str_[ind] == '-' || str_[ind] == '+') && (str_[ind - 1] != '-' && str_[ind - 1] != '+')) {
                state = 0;
                break;
            } else {
                std::string error = "expected number, received: ";
                error.push_back(str_[ind]);
                throw std::runtime_error(error);
            }
        } else if (state == 2) {
            if (str_[ind] >= 'a' && str_[ind] <= 'z') {
                alph[str_[ind] - 'a'] = 1;
                teck = str_[ind];
                state = 2;
            } else if (str_[ind] == '^') {
                cnt = 0;
                state = 3;
            } else if (str_[ind] == '-' || str_[ind] == '+') {
                state = 0;
                break;
            } else {
                std::string error = "expected letter, power, sign, received: ";
                error.push_back(str_[ind]);
                throw std::runtime_error(error);
            }
            ++ind;
        } else if (state == 3) {
            if (str_[ind] >= '0' && str_[ind] <= '9') {
                cnt *= 10;
                cnt += (str_[ind] - '0');
                ++ind;
                if (ind == str_.size()) {
                    alph[teck - 'a'] = cnt;
                }
            } else if (str_[ind] >= 'a' && str_[ind] <= 'z' && cnt != 0) {
                alph[teck - 'a'] = cnt;
                state = 2;
            } else if (str_[ind] == '-' || str_[ind] == '+') {
                alph[teck - 'a'] = cnt;
                state = 0;
                break;
            } else {
                std::string error = "expected number, received: ";
                error.push_back(str_[ind]);
                throw std::runtime_error(error);
            }
        }
    }

    k *= sign;
    return { alph, k };
}

bool FSM::is_end() {
    return ind == str_.size();
}
