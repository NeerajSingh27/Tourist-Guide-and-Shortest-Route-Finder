#pragma once
#include "Person.h"
#include <string>
class Guide : public Person {
private:
    int id_{};
    int experience_{};
    double rating_{};
    std::string specialization_;
    bool available_{true};
public:
    Guide(int id = 0, std::string name = {}, std::string phone = {}, int experience = 0,
          double rating = 0.0, std::string specialization = {}, bool available = true);
    int getId() const;
    int getExperience() const;
    double getRating() const;
    const std::string& getSpecialization() const;
    bool isAvailable() const;
    void setAvailable(bool available);
    std::string role() const override;
};
