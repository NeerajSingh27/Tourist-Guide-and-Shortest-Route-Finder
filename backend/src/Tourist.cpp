#include "Tourist.h"
#include <utility>
Tourist::Tourist(int id, std::string name, std::string phone, std::string email)
    : Person(std::move(name), std::move(phone)), id_(id), email_(std::move(email)) {}
int Tourist::getId() const { return id_; }
const std::string &Tourist::getEmail() const { return email_; }
std::string Tourist::role() const { return "Tourist"; }
