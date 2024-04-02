//
// Created by lkolinko on 4/1/24.
//
#include <iostream>

template<typename T>
class TwoLinkedList {
public:
    TwoLinkedList() = default;
    ~TwoLinkedList();
    TwoLinkedList(const TwoLinkedList& other);
    void PushBack(T val);
    T GetFromInd(int ind);
    void Erase(T val);
    void EraseInd(int ind);
    void Clear();
    void Print();
private:
    struct node {
        T val;
        node* next;
        node* prev;
        node() {
            next = nullptr;
            prev = nullptr;
        }
        node(T value) {
            val = value;
            prev = nullptr;
            next = nullptr;
        }
    };
    node* find(T val);
    void EraseHead();
    node* root = nullptr;
    node* tail = nullptr;
};

template<typename T>
T TwoLinkedList<T>::GetFromInd(int ind) {
    auto u = root;
    for (int i = 0; i != ind; ++i) {
        u = u->next;
    }
    return u->val;
}

template<typename T>
void TwoLinkedList<T>::Print() {
    auto u = root;
    while (u != nullptr) {
        std::cout << u->val << '\n';
        u = u->next;
    }
}

template<typename T>
void TwoLinkedList<T>::EraseHead() {
    auto u = root;
    root = root->next;
    root->prev = nullptr;
    delete u;
}

template<typename T>
void TwoLinkedList<T>::EraseInd(int ind) {
    if (ind == 0) {
        EraseHead();
        return;
    }
    auto u = root;
    for (int i = 0; i != ind; ++i) {
        u = u->next;
    }
    if (u->prev) {
        u->prev->next = u->next;
    }
    if (u->next) {
        u->next->prev = u->prev;
    }
    delete u;
}

template<typename T>
void TwoLinkedList<T>::Erase(T val) {
    auto u = find(val);
    if (u) {
        if (u == root) {
            EraseHead();
        } else {
            if (u->prev) {
                u->prev->next = u->next;
            }
            if (u->next) {
                u->next->prev = u->prev;
            }
            delete u;
        }
    }
}

template<typename T>
typename TwoLinkedList<T>::node *TwoLinkedList<T>::find(T val) {
    auto u = root;
    while (u != nullptr) {
        if (u->val == val) {
            break;
        }
        u = u->next;
    }
    return u;
}

template<typename T>
void TwoLinkedList<T>::PushBack(T val) {
    auto u = new node(val);
    if (root == nullptr) {
        tail = u;
        root = tail;
    } else {
        u->prev = tail;
        tail->next = u;
        tail = u;
    }
}

template<typename T>
void TwoLinkedList<T>::Clear() {
    tail = nullptr;
    while (root != nullptr) {
        auto u = root->next;
        delete root;
        root = u;
    }
}

template<typename T>
TwoLinkedList<T>::TwoLinkedList(const TwoLinkedList &other) {
    Clear();
    auto u = other.root;
    while (u != nullptr) {
        PushBack(u->val);
        u = u->next;
    }
}

template<typename T>
TwoLinkedList<T>::~TwoLinkedList() {
    while (root != nullptr) {
        auto u = root->next;
        delete root;
        root = u;
    }
}
