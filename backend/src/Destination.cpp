#include "Destination.h"
#include <utility>
Destination::Destination(int id, std::string name, std::string subtitle, std::string region,
                         std::string description, std::string image)
    : id_(id), name_(std::move(name)), subtitle_(std::move(subtitle)), region_(std::move(region)),
      description_(std::move(description)), image_(std::move(image)) {}
int Destination::getId() const { return id_; }
const std::string& Destination::getName() const { return name_; }
const std::string& Destination::getSubtitle() const { return subtitle_; }
const std::string& Destination::getRegion() const { return region_; }
const std::string& Destination::getDescription() const { return description_; }
const std::string& Destination::getImage() const { return image_; }
