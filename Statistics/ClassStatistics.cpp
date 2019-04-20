#include "ClassStatistics.h"

#include "StatisticsBuff.h"
#include "StatisticsEngine.h"
#include "StatisticsProc.h"
#include "StatisticsResource.h"
#include "StatisticsSpell.h"
#include "Utils/Check.h"

ClassStatistics::ClassStatistics(SimSettings* sim_settings) :
    sim_settings(sim_settings),
    option(SimOption::Name::NoScale),
    combat_iterations(0),
    combat_length(0),
    damage_dealt_previous_iterations(0)
{}

ClassStatistics::~ClassStatistics() {
    delete_maps();

    delete engine_statistics;
}

void ClassStatistics::set_sim_option(const SimOption::Name option) {
    this->option = option;
}

SimOption::Name ClassStatistics::get_sim_option() const {
    return this->option;
}

StatisticsSpell* ClassStatistics::get_spell_statistics(const QString &name, const QString& icon) {
    check(!spell_statistics.contains(name), QString("'%1' has already initialized spell statistics").arg(name).toStdString());

    spell_statistics[name] = new StatisticsSpell(name, icon);
    return spell_statistics[name];
}

StatisticsBuff* ClassStatistics::get_buff_statistics(const QString& name, const QString& icon, const bool debuff) {
    check(!buff_statistics.contains(name), QString("'%1' has already initialized buff statistics").arg(name).toStdString());

    buff_statistics[name] = new StatisticsBuff(name, icon, debuff);
    return buff_statistics[name];
}

StatisticsResource* ClassStatistics::get_resource_statistics(const QString& name, const QString& icon) {
    check(!resource_statistics.contains(name), QString("'%1' has already initialized resource statistics").arg(name).toStdString());

    resource_statistics[name] = new StatisticsResource(name, icon, combat_length * combat_iterations);
    return resource_statistics[name];
}

StatisticsProc* ClassStatistics::get_proc_statistics(const QString& name, const QString& icon) {
    check(!proc_statistics.contains(name), QString("'%1' has already initialized proc statistics").arg(name).toStdString());

    proc_statistics[name] = new StatisticsProc(name, icon);
    return proc_statistics[name];
}

StatisticsEngine* ClassStatistics::get_engine_statistics() {
    return engine_statistics;
}

void ClassStatistics::finish_combat_iteration() {
    int damage_dealt_this_iteration = get_total_damage_dealt() - damage_dealt_previous_iterations;
    check((damage_dealt_this_iteration >= 0), "Damage dealt must be a positive value");

    dps_for_iterations.append(static_cast<double>(damage_dealt_this_iteration) / combat_length);
    damage_dealt_previous_iterations += damage_dealt_this_iteration;
}

int ClassStatistics::get_total_damage_dealt() const {
    int sum = 0;

    for (auto & spell : spell_statistics)
        sum += spell->get_total_dmg_dealt();

    return sum;
}

double ClassStatistics::get_total_dps() const {
    int damage_dealt = get_total_damage_dealt();

    return static_cast<double>(damage_dealt) / (combat_iterations * combat_length);
}

int ClassStatistics::get_total_damage_for_spell(const QString& name) const {
    if (!spell_statistics.contains(name))
        return 0;

    return spell_statistics[name]->get_total_dmg_dealt();
}

int ClassStatistics::get_total_attempts_for_spell(const QString& name) const {
    if (!spell_statistics.contains(name))
        return 0;

    return spell_statistics[name]->get_total_attempts_made();
}

void ClassStatistics::prepare_statistics() {
    delete engine_statistics;
    engine_statistics = new StatisticsEngine();

    delete_maps();

    spell_statistics.clear();
    buff_statistics.clear();
    resource_statistics.clear();
    proc_statistics.clear();

    combat_iterations = sim_settings->get_combat_iterations_full_sim();
    combat_length = sim_settings->get_combat_length();
}

void ClassStatistics::delete_maps() {
    for (auto & i: spell_statistics)
        delete i;

    for (auto & i : buff_statistics)
        delete i;

    for (auto & i : resource_statistics)
        delete i;

    for (auto & i : proc_statistics)
        delete i;
}
