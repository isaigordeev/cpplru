//
// Created by Isai GORDEEV on 01/07/2025.
//

#pragma once

#include "lru.h"
#include <string>

class AbstractUser
{
    int id;
    std::string name;
    std::string email;

    AbstractUser() : id(0), name(""), email("") {}
};

template <typename K> class User: public AbstractUser
{

    LRU<K> lru;

    User(): AbstractUser() {};

};