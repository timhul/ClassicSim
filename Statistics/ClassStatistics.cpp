#include "ClassStatistics.h"

#include "StatisticsBuff.h"
#include "StatisticsEngine.h"
#include "StatisticsProc.h"
#include "StatisticsResource.h"
#include "StatisticsRotationExecutor.h"
#include "StatisticsSpell.h"
#include "Utils/Check.h"

ClassStatistics::ClassStatistics(SimSettings* sim_settings, const bool ignore_non_buff_statistics) :
    sim_settings(sim_settings),
    option(SimOption::Name::NoScale),
    combat_iterations(0),
    combat_length(0),
    damage_dealt_previous_iterations(0),
    ignore_non_buff_statistics(ignore_non_buff_statistics)
{}

ClassStatistics::~ClassStatistics() {
    delete_objects();
}

void ClassStatistics::set_sim_option(const SimOption::Name option) {
    this->option = option;
}

StatisticsSpell* ClassStatistics::get_spell_statistics(const QString &name, const QString& icon, const int spell_rank) {
    const auto recorded_name = spell_rank > 1 ? QString("%1 (rank %2)").arg(name).arg(spell_rank) : name;
    check(!spell_statistics.contains(recorded_name), QString("'%1' has already initialized spell statistics").arg(recorded_name).toStdString());

    spell_statistics[recorded_name] = new StatisticsSpell(recorded_name, icon);
    return spell_statistics[recorded_name];
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

    proc_statistics[name] = new StatisticsProc(name, icon, combat_length * combat_iterations);
    return proc_statistics[name];
}

StatisticsRotationExecutor* ClassStatistics::get_executor_statistics(const QString& name) {
    auto executor_statistics = new StatisticsRotationExecutor(QString("(%1) %2").arg(rotation_executor_statistics.size() + 1).arg(name));
    rotation_executor_statistics.append(executor_statistics);

    return executor_statistics;
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

    for (const auto & spell : spell_statistics)
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

void ClassStatistics::prepare_statistics() {
    delete_objects();

    spell_statistics.clear();
    buff_statistics.clear();
    resource_statistics.clear();
    proc_statistics.clear();
    rotation_executor_statistics.clear();

    engine_statistics = new StatisticsEngine();

    combat_iterations = sim_settings->get_combat_iterations_full_sim();
    combat_length = sim_settings->get_combat_length();
}

void ClassStatistics::delete_objects() {
    for (const auto & i: spell_statistics)
        delete i;

    for (const auto & i : buff_statistics)
        delete i;

    for (const auto & i : resource_statistics)
        delete i;

    for (const auto & i : proc_statistics)
        delete i;

    for (const auto & i: rotation_executor_statistics)
        delete i;

    delete engine_statistics;
}
