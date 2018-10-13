
#include "SimSettings.h"

SimSettings::SimSettings() :
    combat_length(300),
    combat_iterations(1000)
{}

int SimSettings::get_combat_length() const {
    return this->combat_length;
}

int SimSettings::get_combat_iterations() const {
    return this->combat_iterations;
}

void SimSettings::set_combat_length(const int combat_length) {
    this->combat_length = combat_length;
}

void SimSettings::set_combat_iterations(const int combat_iterations) {
    this->combat_iterations = combat_iterations;
}
