
#include "NumberCruncher.h"
#include "DamageBreakdownModel.h"
#include "StatisticsSpell.h"
#include <QDebug>

DamageBreakdownModel::DamageBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = DamageBreakdownSorting::Methods::ByTotalDamageAbsolute;
    this->sorting_methods.insert(DamageBreakdownSorting::Methods::ByTotalDamageAbsolute, true);
    this->sorting_methods.insert(DamageBreakdownSorting::Methods::ByName, false);
}

DamageBreakdownModel::~DamageBreakdownModel() {
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

void DamageBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<DamageBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case DamageBreakdownSorting::Methods::ByTotalDamageAbsolute:
        std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByTotalDamagePercentage:
        std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::Icon:
    case DamageBreakdownSorting::Methods::ByName:
        std::sort(spell_stats.begin(), spell_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByTotalAttempts:
        std::sort(spell_stats.begin(), spell_stats.end(), total_attempts);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByNumHits:
        std::sort(spell_stats.begin(), spell_stats.end(), num_hits);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByHitPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), hit_percent);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByNumCrits:
        std::sort(spell_stats.begin(), spell_stats.end(), num_crits);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByCritPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), crit_percent);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByNumGlances:
        std::sort(spell_stats.begin(), spell_stats.end(), num_glances);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByGlancePercent:
        std::sort(spell_stats.begin(), spell_stats.end(), glance_percent);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByNumMisses:
        std::sort(spell_stats.begin(), spell_stats.end(), num_misses);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByMissPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), miss_percent);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByNumDodges:
        std::sort(spell_stats.begin(), spell_stats.end(), num_dodges);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByDodgePercent:
        std::sort(spell_stats.begin(), spell_stats.end(), dodge_percent);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByNumParries:
        std::sort(spell_stats.begin(), spell_stats.end(), num_parries);
        select_new_method(sorting_method);
        break;
    case DamageBreakdownSorting::Methods::ByParryPercent:
        std::sort(spell_stats.begin(), spell_stats.end(), parry_percent);
        select_new_method(sorting_method);
        break;
    }

    layoutChanged();
}

void DamageBreakdownModel::select_new_method(const DamageBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(spell_stats.begin(), spell_stats.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<DamageBreakdownSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

int DamageBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void DamageBreakdownModel::update_statistics() {
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

int DamageBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return spell_stats.count();
}

QVariant DamageBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= spell_stats.count())
        return QVariant();

    const StatisticsSpell* spell_stat = spell_stats[index.row()];

    if (role == DamageBreakdownSorting::ByName)
        return spell_stat->get_name();
    if (role == DamageBreakdownSorting::Icon)
        return "Assets/buffs/Inv_misc_head_dragon_01.png";
    if (role == DamageBreakdownSorting::ByTotalDamageAbsolute)
        return spell_stat->get_total_dmg_dealt();
    if (role == DamageBreakdownSorting::ByTotalDamagePercentage)
        return QString("%1 %").arg(QString::number(spell_stat->get_percentage_of_damage_dealt() * 100, 'f', 2));
    if (role == DamageBreakdownSorting::ByTotalAttempts)
        return spell_stat->get_total_attempts_made();
    if (role == DamageBreakdownSorting::ByNumHits)
        return spell_stat->get_hits();
    if (role == DamageBreakdownSorting::ByHitPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_hits()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == DamageBreakdownSorting::ByNumCrits)
        return spell_stat->get_crits();
    if (role == DamageBreakdownSorting::ByCritPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_crits()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == DamageBreakdownSorting::ByNumGlances)
        return spell_stat->get_glances();
    if (role == DamageBreakdownSorting::ByGlancePercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_glances()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == DamageBreakdownSorting::ByNumMisses)
        return spell_stat->get_misses();
    if (role == DamageBreakdownSorting::ByMissPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_misses()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == DamageBreakdownSorting::ByNumDodges)
        return spell_stat->get_dodges();
    if (role == DamageBreakdownSorting::ByDodgePercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_dodges()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));
    if (role == DamageBreakdownSorting::ByNumParries)
        return spell_stat->get_parries();
    if (role == DamageBreakdownSorting::ByParryPercent)
        return QString("%1 %").arg(QString::number(double(spell_stat->get_parries()) / spell_stat->get_total_attempts_made() * 100, 'f', 2));

    return QVariant();
}

QHash<int, QByteArray> DamageBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DamageBreakdownSorting::ByName] = "_name";
    roles[DamageBreakdownSorting::Icon] = "_icon";
    roles[DamageBreakdownSorting::ByTotalDamageAbsolute] = "_totaldmgabsolute";
    roles[DamageBreakdownSorting::ByTotalDamagePercentage] = "_totaldmgpercent";
    roles[DamageBreakdownSorting::ByTotalAttempts] = "_totalattempts";
    roles[DamageBreakdownSorting::ByNumHits] = "_numhits";
    roles[DamageBreakdownSorting::ByHitPercent] = "_hitpercent";
    roles[DamageBreakdownSorting::ByNumCrits] = "_numcrits";
    roles[DamageBreakdownSorting::ByCritPercent] = "_critpercent";
    roles[DamageBreakdownSorting::ByNumGlances] = "_numglances";
    roles[DamageBreakdownSorting::ByGlancePercent] = "_glancepercent";
    roles[DamageBreakdownSorting::ByNumMisses] = "_nummisses";
    roles[DamageBreakdownSorting::ByMissPercent] = "_misspercent";
    roles[DamageBreakdownSorting::ByNumDodges] = "_numdodges";
    roles[DamageBreakdownSorting::ByDodgePercent] = "_dodgepercent";
    roles[DamageBreakdownSorting::ByNumParries] = "_numparries";
    roles[DamageBreakdownSorting::ByParryPercent] = "_parrypercent";
    return roles;
}
