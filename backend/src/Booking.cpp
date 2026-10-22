
#include "Booking.h"
#include <utility>

Booking::Booking(std::string tourist, std::string guide, std::string destination, std::string date)
    : tourist_(std::move(tourist)), guide_(std::move(guide)), destination_(std::move(destination)), date_(std::move(date)) {}

const std::string& Booking::getTourist() const {
    return tourist_;
}
const std::string& Booking::getGuide() const {
    return guide_;
}
const std::string& Booking::getDestination() const {
    return destination_;
}
const std::string& Booking::getDate() const {
    return date_;
}

bool Booking::isValid() const {
    return !tourist_.empty() && !guide_.empty() && !destination_.empty() && !date_.empty();
}
