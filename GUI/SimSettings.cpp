
#include "SimSettings.h"

SimSettings::SimSettings() :
    combat_length(300),
    combat_iterations(1000)
{
    sim_options = QSet<SimOption>({SimOption::ScaleStrength, SimOption::ScaleCritChance, SimOption::ScaleHitChance});
}

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

void SimSettings::add_sim_option(SimOption option) {
    assert(option != SimOption::NoScale);
    sim_options.insert(option);
}

void SimSettings::remove_sim_option(SimOption option) {
    if (sim_options.contains(option))
        sim_options.remove(option);
}

bool SimSettings::option_active(SimOption option) const {
    return sim_options.contains(option);
}

QSet<SimOption> SimSettings::get_active_options() const {
    return sim_options;
}
