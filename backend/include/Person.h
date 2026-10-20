#pragma once
#include <string>

// Abstract base class for people using the tourism application.
class Person
{
protected:
    std::string name_;
    std::string phone_;

public:
    Person(std::string name = {}, std::string phone = {});
    virtual ~Person() = default;
    const std::string &getName() const;
    const std::string &getPhone() const;
    void setName(const std::string &name);
    void setPhone(const std::string &phone);
    virtual std::string role() const = 0;
};
