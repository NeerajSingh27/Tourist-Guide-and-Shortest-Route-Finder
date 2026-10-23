#pragma once
#include <string>
class Booking {
private:
    std::string tourist_, guide_, destination_, date_;
public:
    Booking(std::string tourist, std::string guide, std::string destination, std::string date);
    const std::string& getTourist() const;
    const std::string& getGuide() const;
    const std::string& getDestination() const;
    const std::string& getDate() const;
    bool isValid() const;
};
