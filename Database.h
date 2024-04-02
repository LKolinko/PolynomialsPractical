#include "Singleton.h"
#include "TwoLinkedList.h"
#include "Polinom.h"
#include <iostream>
#include <fstream>

class Database : public Singleton<Database> {
public:
    void Add(Polinom &polinom);
    void Erase(int ind);
    void LoadFromFile(std::string& str);
    void SaveToFile(std::string& str);
    Polinom GetPolinom(int ind);
private:
    TwoLinkedList<Polinom> data_;
};
