#include <vector>
#include <set>
#include <cmath>
#include "FSM.h"
#include "list.h"

class Polinom {
public:
    Polinom(std::string& str);
    Polinom() = default;
    ~Polinom() = default;
    Polinom(const Polinom& other);
    void Print();
    std::string ToString();
    Polinom Derivative(char x);
    Polinom Derivative(int k, char x);
    Polinom& operator=(const Polinom& other);
    bool operator==(Polinom& other);
    Polinom operator-();
    Polinom operator-(Polinom other);
    Polinom operator+(Polinom other);
    Polinom operator*(Polinom other);
    Polinom operator*(int num);
    Polinom operator/(Polinom other);
    Polinom operator+=(Polinom other);
    Polinom operator-=(Polinom other);
    Polinom operator*=(Polinom other);
    Polinom operator*=(int num);
    Polinom operator/=(Polinom other);
    int ValueInPoint(std::vector<int>& values);
    std::vector<int> getRoots();
private:
    struct node {
        int k;
        std::vector<int> alph;
        node() {
            k = 0;
            alph.assign(26, 0);
        }
        node(std::vector<int> al, int cnt) {
            alph = al;
            k = cnt;
        }
        node(const node& other) {
            alph = other.alph;
            k = other.k;
        }
        bool operator<(node& other) {
            int pow1 = 0, pow2 = 0;
            for (int i = 0; i < 26; ++i) {
                pow1 += alph[i];
                pow2 += other.alph[i];
            }
            if (pow1 < pow2) {
                return true;
            } else if (pow1 > pow2) {
                return false;
            } else {
                return k < other.k;
            }
        }
        bool operator>(node& other) {
            int pow1 = 0, pow2 = 0;
            for (int i = 0; i < 26; ++i) {
                pow1 += alph[i];
                pow2 += other.alph[i];
            }
            if (pow1 > pow2) {
                return true;
            } else if (pow1 < pow2) {
                return false;
            } else {
                return k > other.k;
            }

        }
        node& operator=(node other) {
            alph = other.alph;
            k = other.k;
            return *this;
        }
        bool operator==(node& other) {
            return alph == other.alph && k == other.k;
        }
        bool operator!=(node& other) {
            return !(*this == other);
        }
        node operator*(node& other) {
            node res;
            res.k = k * other.k;
            for (int i = 0; i < 26; ++i) {
                res.alph[i] = alph[i] + other.alph[i];
            }
            return res;
        }
        node operator+(node& other) {
            node res = *this;
            res.k += other.k;
            return res;
        }
        node operator*(int num) {
            node res;
            res.k = k * num;
            res.alph = alph;
            return res;
        }
        node operator*=(int num) {
            *this = (*this * num);
            return *this;
        }
        friend std::ostream &operator<<(std::ostream& out, const Polinom::node& p) {
            if (p.k < 0) {
                out << p.k;
            } else {
                out << "+" << p.k;
            }
            for (int i = 0; i < 26; ++i) {
                if (p.alph[i] == 1) {
                    out << char('a' + i);
                } else if (p.alph[i] > 1) {
                    out << char('a' + i) << '^' << p.alph[i];
                }
            }
            return out;
        }
    };
    void normalization();
    list<node> data_;
};