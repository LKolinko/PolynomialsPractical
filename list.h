#include <iostream>

template<typename T>
class list {
public:
    struct node {
        T val;
        node* next;
        node() = default;
        node& operator=(node& other) {
            val = other.val;
            next = other.next;
            return *this;
        }
        node(const node& other) {
            val = other.val;
            next = other.next;
        }
    };
    list() = default;
    ~list();
    list(const list& other);
    void PushBack(T p);
    void Erase(T p);
    void Print();
    void Sort();
    void Clear();
    list &operator=(list other);
    node* getRoot();
private:
    node* root = nullptr;
    node* tail = nullptr;

    node* find(T val);

    void Add(node *&l, node *&lt, node *q);

    std::pair<node*, node*> partision(node** l, node* r);
    void QuickSort(node** l, node* r);

    void Delete(node* p);
    node* DeleteLast(node* p);
};

template<typename T>
typename list<T>::node *list<T>::getRoot() {
    return root;
}

template<typename T>
list<T>::list(const list &other) {
    Clear();
    auto u = other.root;
    while (u != nullptr) {
        PushBack(u->val);
        u = u->next;
    }
}

template<typename T>
list<T> &list<T>::operator=(list other) {
    Clear();
    auto u = other.root;
    while (u != nullptr) {
        PushBack(u->val);
        u = u->next;
    }
    return *this;
}

template<typename T>
void list<T>::Clear() {
    tail = nullptr;
    while (root != nullptr) {
        auto u = root->next;
        delete root;
        root = u;
    }
}

template<typename T>
void list<T>::Add(list::node *&l, list::node *&lt, list::node *q) {
    if (l == nullptr) {
        lt = q;
        lt->next = nullptr;
        l = lt;
    } else {
        lt->next = q;
        lt = q;
    }
}

template<typename T>
void list<T>::Sort() {
    QuickSort(&root, nullptr);
}

template<typename T>
void list<T>::QuickSort(list::node **l, list::node *r) {
    if (*l == r || (*l)->next == r) {
        return;
    }
    auto u = partision(l, r);
    QuickSort(l, u.first);
    QuickSort(&u.second->next, r);
}

template<typename T>
std::pair<typename list<T>::node*,typename list<T>::node*> list<T>::partision(list::node **l, list::node *r) {
    node* pivot = *l;
    node* ls = nullptr;
    node* gr = nullptr;
    node* qe = nullptr;
    node* lt = nullptr;
    node* gt = nullptr;
    node* qt = nullptr;
    node* q = *l;
    while (q != r) {
        auto u = q->next;
        if (q->val > pivot->val) {
            Add(ls, lt, q);
        } else if (q->val == pivot->val) {
            Add(qe, qt, q);
        } else {
            Add(gr, gt, q);
        }
        q = u;
    }
    if (gt == nullptr) {
        gr = r;
    } else {
        gt->next = r;
    }
    if (ls == nullptr) {
        ls = qe;
    } else {
        lt->next = qe;
    }
    qt->next = gr;
    *l = ls;
    return { qe, qt };
}

template<typename T>
list<T>::~list() {
    while (root != nullptr) {
        auto u = root->next;
        delete root;
        root = u;
    }
}

template<typename T>
void list<T>::Print() {
    auto u = root;
    while (u != nullptr) {
        std::cout << u->val;
        u = u->next;
    }
    std::cout << '\n';
}

template<typename T>
typename list<T>::node *list<T>::find(T val) {
    auto v = root;
    std::cout << root->val << '\n';
    while (v != nullptr && v->val != val) {
        v = v->next;
    }
    return v;
}

template<typename T>
void list<T>::Erase(T p) {
    auto u = find(p);
    if (u) {
        Delete(u);
    }
}

template<typename T>
void list<T>::PushBack(T p) {
    node* q = new node();
    q->val = p;
    q->next = nullptr;
    if (root == nullptr) {
        tail = q;
        root = tail;
    } else {
        tail->next = q;
        tail = q;
    }
}

template<typename T>
void list<T>::Delete(list::node *p) {
    if (p == root) {
        delete root;
        root == nullptr;
    }
    if (p->next == nullptr) {
        auto u = DeleteLast(p);
        u->next = nullptr;
        delete p;
    } else {
        node *q = p->next;
        *p = *q;
        delete q;
    }
}

template<typename T>
typename list<T>::node *list<T>::DeleteLast(list::node *p) {
    auto v = root;
    if (root == p) {
        return root;
    }
    while (v->next != p) {
        v = v->next;
    }
    return v;
}
