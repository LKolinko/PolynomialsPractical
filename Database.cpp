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

}

void Database::SaveToFile(std::string &str) {

}

Polinom Database::GetPolinom(int ind) {
    return data_.GetFromInd(ind);
}


