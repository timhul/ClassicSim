
#include "SimSettings.h"
#include "RulesetControl.h"
#include <QThread>

SimSettings::SimSettings() :
    combat_length(300),
    combat_iterations(1000),
    num_threads(QThread::idealThreadCount()),
    ruleset_control(new RulesetControl())
{
    sim_options = QSet<SimOption>({SimOption::ScaleStrength, SimOption::ScaleCritChance, SimOption::ScaleHitChance});
}

SimSettings::~SimSettings() {
    delete ruleset_control;
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

int SimSettings::get_num_threads_current() const {
    return num_threads;
}

int SimSettings::get_num_threads_max() const {
    return QThread::idealThreadCount();
}

void SimSettings::set_num_threads(const int num_threads) {
    if (num_threads < 1 || num_threads > get_num_threads_max())
        return;

    this->num_threads = num_threads;
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

void SimSettings::use_ruleset(Ruleset ruleset, Character* pchar) {
    ruleset_control->use_ruleset(ruleset, pchar, this);
}

Ruleset SimSettings::get_ruleset() const {
    return ruleset_control->get_active_ruleset();
}

double SimSettings::get_execute_threshold() const {
    return this->execute_threshold;
}

void SimSettings::set_execute_threshold(const double threshold) {
    this->execute_threshold = threshold;
}

void SimSettings::clear_execute_threshold() {
    this->execute_threshold = 0.2;
}
