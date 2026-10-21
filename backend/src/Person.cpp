#include "Person.h"
#include <utility>
Person::Person(std::string name, std::string phone) : name_(std::move(name)), phone_(std::move(phone)) {}
const std::string& Person::getName() const { return name_; }
const std::string& Person::getPhone() const { return phone_; }
void Person::setName(const std::string& name) { name_ = name; }
void Person::setPhone(const std::string& phone) { phone_ = phone; }
