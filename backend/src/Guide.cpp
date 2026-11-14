#include "Guide.h"
#include <utility>
Guide::Guide(int id, std::string name, std::string phone, int experience, double rating,
             std::string specialization, bool available)
    : Person(std::move(name), std::move(phone)), id_(id), experience_(experience), rating_(rating),
      specialization_(std::move(specialization)), available_(available) {}
int Guide::getId() const { return id_; }
int Guide::getExperience() const { return experience_; }
double Guide::getRating() const { return rating_; }
const std::string &Guide::getSpecialization() const { return specialization_; }
bool Guide::isAvailable() const { return available_; }
void Guide::setAvailable(bool available) { available_ = available; }
std::string Guide::role() const { return "Guide"; }
