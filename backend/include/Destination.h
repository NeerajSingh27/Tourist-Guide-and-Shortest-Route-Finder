#pragma once
#include <string>
class Destination
{
private:
    int id_{};
    std::string name_, subtitle_, region_, description_, image_;

public:
    Destination(int id, std::string name, std::string subtitle, std::string region,
                std::string description, std::string image);
    int getId() const;
    const std::string &getName() const;
    const std::string &getSubtitle() const;
    const std::string &getRegion() const;
    const std::string &getDescription() const;
    const std::string &getImage() const;
};
