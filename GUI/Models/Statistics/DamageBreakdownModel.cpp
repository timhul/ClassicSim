
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

    return QVariant();
}

QHash<int, QByteArray> DamageBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DamageBreakdownSorting::ByName] = "_name";
    roles[DamageBreakdownSorting::Icon] = "_icon";
    roles[DamageBreakdownSorting::ByTotalDamageAbsolute] = "_totaldmgabsolute";
    roles[DamageBreakdownSorting::ByTotalDamagePercentage] = "_totaldmgpercent";
    return roles;
}
