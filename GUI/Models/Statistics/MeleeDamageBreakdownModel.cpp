#include "MeleeDamageBreakdownModel.h"

#include "NumberCruncher.h"
#include "StatisticsSpell.h"

MeleeDamageBreakdownModel::MeleeDamageBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = MeleeDamageBreakdownSorting::Methods::ByTotalDamageAbsolute;
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByTotalDamageAbsolute, true);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByName, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMinHit, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByAvgHit, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMaxHit, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMinCrit, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByAvgCrit, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMaxCrit, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMinGlance, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByAvgGlance, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMaxGlance, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMinDPR, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByAvgDPR, false);
    this->sorting_methods.insert(MeleeDamageBreakdownSorting::Methods::ByMaxDPR, false);
}

MeleeDamageBreakdownModel::~MeleeDamageBreakdownModel() {
    for (auto & i : spell_stats)
        delete i;
}

void MeleeDamageBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<MeleeDamageBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case MeleeDamageBreakdownSorting::Methods::ByTotalDamageAbsolute:
        std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByTotalDamagePercentage:
        std::sort(spell_stats.begin(), spell_stats.end(), total_damage);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::Icon:
    case MeleeDamageBreakdownSorting::Methods::ByName:
        std::sort(spell_stats.begin(), spell_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMinHit:
        std::sort(spell_stats.begin(), spell_stats.end(), min_hit);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByAvgHit:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_hit);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMaxHit:
        std::sort(spell_stats.begin(), spell_stats.end(), max_hit);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMinCrit:
        std::sort(spell_stats.begin(), spell_stats.end(), min_crit);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByAvgCrit:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_crit);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMaxCrit:
        std::sort(spell_stats.begin(), spell_stats.end(), max_crit);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMinGlance:
        std::sort(spell_stats.begin(), spell_stats.end(), min_glancing);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByAvgGlance:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_glancing);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMaxGlance:
        std::sort(spell_stats.begin(), spell_stats.end(), max_glancing);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMinDPR:
        std::sort(spell_stats.begin(), spell_stats.end(), min_dpr);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByAvgDPR:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_dpr);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMaxDPR:
        std::sort(spell_stats.begin(), spell_stats.end(), max_dpr);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMinDPET:
        std::sort(spell_stats.begin(), spell_stats.end(), min_dpet);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByAvgDPET:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_dpet);
        select_new_method(sorting_method);
        break;
    case MeleeDamageBreakdownSorting::Methods::ByMaxDPET:
        std::sort(spell_stats.begin(), spell_stats.end(), max_dpet);
        select_new_method(sorting_method);
        break;
    }

    layoutChanged();
}

void MeleeDamageBreakdownModel::select_new_method(const MeleeDamageBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(spell_stats.begin(), spell_stats.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<MeleeDamageBreakdownSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

int MeleeDamageBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void MeleeDamageBreakdownModel::update_statistics() {
    if (!spell_stats.empty()) {
        beginResetModel();

        for (auto & i : spell_stats)
            delete i;

        spell_stats.clear();
        endResetModel();
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

int MeleeDamageBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return spell_stats.count();
}

QVariant MeleeDamageBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= spell_stats.count())
        return QVariant();

    const StatisticsSpell* spell_stat = spell_stats[index.row()];

    if (role == MeleeDamageBreakdownSorting::ByName)
        return spell_stat->get_name();
    if (role == MeleeDamageBreakdownSorting::Icon)
        return spell_stat->get_icon();
    if (role == MeleeDamageBreakdownSorting::ByTotalDamageAbsolute)
        return spell_stat->get_total_dmg_dealt();
    if (role == MeleeDamageBreakdownSorting::ByTotalDamagePercentage)
        return QString("%1 %").arg(QString::number(spell_stat->get_percentage_of_damage_dealt() * 100, 'f', 2));
    if (role == MeleeDamageBreakdownSorting::ByMinHit)
        return spell_stat->get_min_hit_dmg();
    if (role == MeleeDamageBreakdownSorting::ByAvgHit)
        return QString::number(double(spell_stat->get_hit_dmg()) / spell_stat->get_hits(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByMaxHit)
        return spell_stat->get_max_hit_dmg();
    if (role == MeleeDamageBreakdownSorting::ByMinCrit)
        return spell_stat->get_min_crit_dmg();
    if (role == MeleeDamageBreakdownSorting::ByAvgCrit)
        return QString::number(double(spell_stat->get_crit_dmg()) / spell_stat->get_crits(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByMaxCrit)
        return spell_stat->get_max_crit_dmg();
    if (role == MeleeDamageBreakdownSorting::ByMinGlance)
        return spell_stat->get_min_glancing_dmg();
    if (role == MeleeDamageBreakdownSorting::ByAvgGlance) {
        if (spell_stat->get_glances() == 0)
            return "0";
        return QString::number(double(spell_stat->get_glancing_dmg()) / spell_stat->get_glances(), 'f', 1);
    }
    if (role == MeleeDamageBreakdownSorting::ByMaxGlance)
        return spell_stat->get_max_glancing_dmg();
    if (role == MeleeDamageBreakdownSorting::ByMinDPR)
        return QString::number(spell_stat->get_min_dpr(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByAvgDPR)
        return QString::number(spell_stat->get_avg_dpr(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByMaxDPR)
        return QString::number(spell_stat->get_max_dpr(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByMinDPET)
        return QString::number(spell_stat->get_min_dpet(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByAvgDPET)
        return QString::number(spell_stat->get_avg_dpet(), 'f', 1);
    if (role == MeleeDamageBreakdownSorting::ByMaxDPET)
        return QString::number(spell_stat->get_max_dpet(), 'f', 1);

    return QVariant();
}

QHash<int, QByteArray> MeleeDamageBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MeleeDamageBreakdownSorting::ByName] = "_name";
    roles[MeleeDamageBreakdownSorting::Icon] = "_icon";
    roles[MeleeDamageBreakdownSorting::ByTotalDamageAbsolute] = "_totaldmgabsolute";
    roles[MeleeDamageBreakdownSorting::ByTotalDamagePercentage] = "_totaldmgpercent";
    roles[MeleeDamageBreakdownSorting::Methods::ByMinHit] = "_minhit";
    roles[MeleeDamageBreakdownSorting::Methods::ByAvgHit] = "_avghit";
    roles[MeleeDamageBreakdownSorting::Methods::ByMaxHit] = "_maxhit";
    roles[MeleeDamageBreakdownSorting::Methods::ByMinCrit] = "_mincrit";
    roles[MeleeDamageBreakdownSorting::Methods::ByAvgCrit] = "_avgcrit";
    roles[MeleeDamageBreakdownSorting::Methods::ByMaxCrit] = "_maxcrit";
    roles[MeleeDamageBreakdownSorting::Methods::ByMinGlance] = "_minglance";
    roles[MeleeDamageBreakdownSorting::Methods::ByAvgGlance] = "_avgglance";
    roles[MeleeDamageBreakdownSorting::Methods::ByMaxGlance] = "_maxglance";
    roles[MeleeDamageBreakdownSorting::Methods::ByMinDPR] = "_mindpr";
    roles[MeleeDamageBreakdownSorting::Methods::ByAvgDPR] = "_avgdpr";
    roles[MeleeDamageBreakdownSorting::Methods::ByMaxDPR] = "_maxdpr";
    roles[MeleeDamageBreakdownSorting::Methods::ByMinDPET] = "_mindpet";
    roles[MeleeDamageBreakdownSorting::Methods::ByAvgDPET] = "_avgdpet";
    roles[MeleeDamageBreakdownSorting::Methods::ByMaxDPET] = "_maxdpet";
    return roles;
}
