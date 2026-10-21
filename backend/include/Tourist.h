#pragma once
#include "Person.h"
#include <string>
class Tourist : public Person {
private:
    int id_{};
    std::string email_;
public:
    Tourist(int id = 0, std::string name = {}, std::string phone = {}, std::string email = {});
    int getId() const;
    const std::string& getEmail() const;
    std::string role() const override;
};
