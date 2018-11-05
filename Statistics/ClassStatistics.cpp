
#include "ClassStatistics.h"
#include "StatisticsSpell.h"
#include "StatisticsBuff.h"
#include "StatisticsResource.h"
#include "StatisticsProc.h"
#include <QDebug>

ClassStatistics::ClassStatistics(SimSettings* sim_settings) :
    sim_settings(sim_settings),
    option(SimOption::Name::NoScale),
    combat_iterations(0),
    combat_length(0),
    damage_dealt_previous_iterations(0)
{}

ClassStatistics::~ClassStatistics() {
    delete_maps();
}

void ClassStatistics::set_sim_option(const SimOption::Name option) {
    assert(this->option == SimOption::Name::NoScale);
    this->option = option;
}

SimOption::Name ClassStatistics::get_sim_option() const {
    return this->option;
}

StatisticsSpell* ClassStatistics::get_spell_statistics(const QString &name, const QString& icon) {
    assert(!spell_statistics.contains(name));

    spell_statistics[name] = new StatisticsSpell(name, icon);
    return spell_statistics[name];
}

StatisticsBuff* ClassStatistics::get_buff_statistics(const QString& name, const QString& icon, const bool debuff) {
    assert(!buff_statistics.contains(name));

    buff_statistics[name] = new StatisticsBuff(name, icon, debuff);
    return buff_statistics[name];
}

StatisticsResource *ClassStatistics::get_resource_statistics(const QString& name, const QString& icon) {
    assert(!resource_statistics.contains(name));

    resource_statistics[name] = new StatisticsResource(name, icon);
    return resource_statistics[name];
}

StatisticsProc *ClassStatistics::get_proc_statistics(const QString& name, const QString& icon) {
    assert(!proc_statistics.contains(name));

    proc_statistics[name] = new StatisticsProc(name, icon);
    return proc_statistics[name];
}

void ClassStatistics::finish_combat_iteration() {
    int damage_dealt_this_iteration = get_total_damage_dealt() - damage_dealt_previous_iterations;
    assert(damage_dealt_this_iteration >= 0);

    dps_for_iterations.append(static_cast<double>(damage_dealt_this_iteration) / combat_length);
    damage_dealt_previous_iterations += damage_dealt_this_iteration;
}

int ClassStatistics::get_total_damage_dealt() const {
    int sum = 0;

    QMap<QString, StatisticsSpell*>::const_iterator it = spell_statistics.constBegin();
    auto end = spell_statistics.constEnd();
    while(it != end) {
        sum += it.value()->get_total_dmg_dealt();
        ++it;
    }

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
    delete_maps();

    combat_iterations = sim_settings->get_combat_iterations_full_sim();
    combat_length = sim_settings->get_combat_length();
}

void ClassStatistics::delete_maps() {
    QMap<QString, StatisticsSpell*>::const_iterator it_spell = spell_statistics.constBegin();
    auto end_spell = spell_statistics.constEnd();
    while(it_spell != end_spell) {
        delete it_spell.value();
        ++it_spell;
    }

    QMap<QString, StatisticsBuff*>::const_iterator it_buff = buff_statistics.constBegin();
    auto end_buff = buff_statistics.constEnd();
    while(it_buff != end_buff) {
        delete it_buff.value();
        ++it_buff;
    }

    QMap<QString, StatisticsResource*>::const_iterator it_resource = resource_statistics.constBegin();
    auto end_resource = resource_statistics.constEnd();
    while(it_resource != end_resource) {
        delete it_resource.value();
        ++it_resource;
    }

    QMap<QString, StatisticsProc*>::const_iterator it_proc = proc_statistics.constBegin();
    auto end_proc = proc_statistics.constEnd();
    while(it_proc != end_proc) {
        delete it_proc.value();
        ++it_proc;
    }

    spell_statistics.clear();
    buff_statistics.clear();
    resource_statistics.clear();
    proc_statistics.clear();
}
