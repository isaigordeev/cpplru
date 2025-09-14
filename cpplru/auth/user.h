//
// Created by Isai GORDEEV on 01/07/2025.
//

#pragma once

#include <string>

#include "cpplru/lru/lru.h"

class AbstractUser {
 private:
  int id;
  std::string name;
  std::string email;

 public:
  AbstractUser() : id(0), name(""), email("") {}

  AbstractUser(int uid = 0, const std::string& name = "",
               const std::string& email = "")
      : id(uid), name(name), email(email) {}

  int getUid() const { return id; }
  const std::string& getName() const { return name; }
  const std::string& getEmain() const { return email; }

  void setId(int uid) { id = uid; }
  void setName(const std::string& uname) { name = uname; }
  void setEmail(const std::string& uemail) { email = uemail; }
};

template <typename K>
class User : public AbstractUser {
 public:
  User(int uid = 0, const std::string& name = "", const std::string& email = "")
      : AbstractUser(uid, name, email), lru(LRU<K>()) {}

 private:
  LRU<K> lru;
};