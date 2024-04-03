//
// Created by lkolinko on 4/2/24.
//

#include "Database.h"

void Database::Add(Polinom &polinom) {
    data_.PushBack(polinom);
}

void Database::Erase(int ind) {
    data_.EraseInd(ind);
}

void Database::LoadFromFile(std::string &str) {
    std::ifstream in(str);
    std::string a;
    while (in >> a) {
        Polinom res = Polinom(a);
        Add(res);
    }
    in.close();
}

void Database::SaveToFile(std::string &str) {
    std::ofstream out(str);
    for (auto u = data_.GetRoot(); u != nullptr; u = u->next) {
        out << u->val.ToString() << '\n';
    }
    out.close();
}

Polinom Database::GetPolinom(int ind) {
    return data_.GetFromInd(ind);
}


