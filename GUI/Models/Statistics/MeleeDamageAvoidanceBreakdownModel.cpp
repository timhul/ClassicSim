
#include "NumberCruncher.h"
#include "MeleeDamageAvoidanceBreakdownModel.h"
#include "StatisticsSpell.h"
#include <QDebug>

MeleeDamageAvoidanceBreakdownModel::MeleeDamageAvoidanceBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = MeleeDamageAvoidanceBreakdownSorting::Methods::ByTotalDamageAbsolute;
    this->sorting_methods.insert(MeleeDamageAvoidanceBreakdownSorting::Methods::ByTotalDamageAbsolute, true);
    this->sorting_methods.insert(MeleeDamageAvoidanceBreakdownSorting::Methods::ByName, false);
}

MeleeDamageAvoidanceBreakdownModel::~MeleeDamageAvoidanceBreakdownModel() {
    for (auto & i : spell_stats)
        delete i;
}

bool name(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool total_damage(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_dmg = lhs->get_total_dmg_dealt();
    auto rhs_dmg = rhs->get_total_dmg_dealt();

    return lhs_dmg == rhs_dmg ? name(lhs, rhs) : lhs_dmg > rhs_dmg;
}

bool total_attempts(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_total = lhs->get_total_attempts_made();
    auto rhs_total = rhs->get_total_attempts_made();

    return lhs_total == rhs_total ? name(lhs, rhs) : lhs_total > rhs_total;
}

bool hit_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_hit = double(lhs->get_hits()) / lhs->get_total_attempts_made();
    auto rhs_hit = double(rhs->get_hits()) / rhs->get_total_attempts_made();

    return lhs_hit < rhs_hit;
}

bool num_hits(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_hit = lhs->get_hits();
    auto rhs_hit = rhs->get_hits();

    return lhs_hit == rhs_hit ? name(lhs, rhs) : lhs_hit > rhs_hit;
}

bool crit_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_crit = double(lhs->get_crits()) / lhs->get_total_attempts_made();
    auto rhs_crit = double(rhs->get_crits()) / rhs->get_total_attempts_made();

    return lhs_crit < rhs_crit;
}

bool num_crits(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_crit = lhs->get_crits();
    auto rhs_crit = rhs->get_crits();

    return lhs_crit == rhs_crit ? name(lhs, rhs) : lhs_crit > rhs_crit;
}

bool glance_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_glance = double(lhs->get_glances()) / lhs->get_total_attempts_made();
    auto rhs_glance = double(rhs->get_glances()) / rhs->get_total_attempts_made();

    return lhs_glance < rhs_glance;
}

bool num_glances(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_glance = lhs->get_glances();
    auto rhs_glance = rhs->get_glances();

    return lhs_glance == rhs_glance ? name(lhs, rhs) : lhs_glance > rhs_glance;
}

bool miss_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_miss = double(lhs->get_misses()) / lhs->get_total_attempts_made();
    auto rhs_miss = double(rhs->get_misses()) / rhs->get_total_attempts_made();

    return lhs_miss < rhs_miss;
}

bool num_misses(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_miss = lhs->get_misses();
    auto rhs_miss = rhs->get_misses();

    return lhs_miss == rhs_miss ? name(lhs, rhs) : lhs_miss > rhs_miss;
}

bool dodge_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_dodge = double(lhs->get_dodges()) / lhs->get_total_attempts_made();
    auto rhs_dodge = double(rhs->get_dodges()) / rhs->get_total_attempts_made();

    return lhs_dodge < rhs_dodge;
}

bool num_dodges(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_dodge = lhs->get_dodges();
    auto rhs_dodge = rhs->get_dodges();

    return lhs_dodge == rhs_dodge ? name(lhs, rhs) : lhs_dodge > rhs_dodge;
}

bool parry_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_parry = double(lhs->get_parries()) / lhs->get_total_attempts_made();
    auto rhs_parry = double(rhs->get_parries()) / rhs->get_total_attempts_made();

    return lhs_parry < rhs_parry;
}

bool num_parries(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_parry = lhs->get_parries();
    auto rhs_parry = rhs->get_parries();

    return lhs_parry == rhs_parry ? name(lhs, rhs) : lhs_parry > rhs_parry;
}

void MeleeDamageAvoidanceBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<MeleeDamageAvoidanceBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByTotalDamageAbsolute:
        std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByTotalDamagePercentage:
        std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::Icon:
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByName:
        std::sort(spell_stats.begin(), spell_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByTotalAttempts:
        std::sort(spell_stats.begin(), spell_stats.end(), total_attempts);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByNumHits:
        std::sort(spell_stats.begin(), spell_stats.end(), num_hits);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByHitPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), hit_percent);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByNumCrits:
        std::sort(spell_stats.begin(), spell_stats.end(), num_crits);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByCritPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), crit_percent);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByNumGlances:
        std::sort(spell_stats.begin(), spell_stats.end(), num_glances);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByGlancePercent:
        std::sort(spell_stats.begin(), spell_stats.end(), glance_percent);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByNumMisses:
        std::sort(spell_stats.begin(), spell_stats.end(), num_misses);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByMissPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), miss_percent);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByNumDodges:
        std::sort(spell_stats.begin(), spell_stats.end(), num_dodges);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByDodgePercent:
        std::sort(spell_stats.begin(), spell_stats.end(), dodge_percent);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByNumParries:
        std::sort(spell_stats.begin(), spell_stats.end(), num_parries);
        select_new_method(sorting_method);
        break;
    case MeleeDamageAvoidanceBreakdownSorting::Methods::ByParryPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), parry_percent);
        select_new_method(sorting_method);
        break;
    }

    layoutChanged();
}

void MeleeDamageAvoidanceBreakdownModel::select_new_method(const MeleeDamageAvoidanceBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(spell_stats.begin(), spell_stats.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<MeleeDamageAvoidanceBreakdownSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

int MeleeDamageAvoidanceBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void MeleeDamageAvoidanceBreakdownModel::update_statistics() {
    if (!spell_stats.empty()) {
        beginRemoveRows(QModelIndex(), 0, spell_stats.size() - 1);

        for (auto & i : spell_stats)
            delete i;

        spell_stats.clear();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_spell_stats(spell_stats);

    QList<StatisticsSpell*>::iterator it = spell_stats.begin();

    while (it != spell_stats.end()) {
        if ((*it)->get_total_dmg_dealt() == 0) {
            delete *it;
            it = spell_stats.erase(it);
        }
        else
            ++it;
    }

    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
    layoutChanged();
}

int MeleeDamageAvoidanceBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return spell_stats.count();
}

QVariant MeleeDamageAvoidanceBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= spell_stats.count())
        return QVariant();

    const StatisticsSpell* spell_stat = spell_stats[index.row()];

    if (role == MeleeDamageAvoidanceBreakdownSorting::ByName)
        return spell_stat->get_name();
    if (role == MeleeDamageAvoidanceBreakdownSorting::Icon)
        return "Assets/buffs/Inv_misc_head_dragon_01.png";
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByTotalDamageAbsolute)
        return spell_stat->get_total_dmg_dealt();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByTotalDamagePercentage)
        return QString("%1 %").arg(QString::number(spell_stat->get_percentage_of_damage_dealt() * 100, 'f', 2));
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByTotalAttempts)
        return spell_stat->get_total_attempts_made();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByNumHits)
        return spell_stat->get_hits();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByHitPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_hits()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByNumCrits)
        return spell_stat->get_crits();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByCritPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_crits()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByNumGlances)
        return spell_stat->get_glances();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByGlancePercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_glances()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByNumMisses)
        return spell_stat->get_misses();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByMissPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_misses()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByNumDodges)
        return spell_stat->get_dodges();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByDodgePercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_dodges()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByNumParries)
        return spell_stat->get_parries();
    if (role == MeleeDamageAvoidanceBreakdownSorting::ByParryPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_parries()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));

    return QVariant();
}

QHash<int, QByteArray> MeleeDamageAvoidanceBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MeleeDamageAvoidanceBreakdownSorting::ByName] = "_name";
    roles[MeleeDamageAvoidanceBreakdownSorting::Icon] = "_icon";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByTotalDamageAbsolute] = "_totaldmgabsolute";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByTotalDamagePercentage] = "_totaldmgpercent";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByTotalAttempts] = "_totalattempts";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByNumHits] = "_numhits";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByHitPercent] = "_hitpercent";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByNumCrits] = "_numcrits";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByCritPercent] = "_critpercent";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByNumGlances] = "_numglances";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByGlancePercent] = "_glancepercent";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByNumMisses] = "_nummisses";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByMissPercent] = "_misspercent";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByNumDodges] = "_numdodges";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByDodgePercent] = "_dodgepercent";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByNumParries] = "_numparries";
    roles[MeleeDamageAvoidanceBreakdownSorting::ByParryPercent] = "_parrypercent";
    return roles;
}
