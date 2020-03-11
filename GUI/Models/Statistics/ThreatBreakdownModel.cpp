#include "ThreatBreakdownModel.h"

#include "NumberCruncher.h"
#include "SortDirection.h"
#include "StatisticsSpell.h"

ThreatBreakdownModel::ThreatBreakdownModel(NumberCruncher* statistics_source, QObject* parent) :
    QAbstractListModel(parent), statistics_source(statistics_source) {
    this->current_sorting_method = ThreatBreakdownSorting::Methods::ByTotalThreatAbsolute;
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByTotalThreatAbsolute, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByName, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMinHitThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByAvgHitThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMaxHitThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMinCritThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByAvgCritThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMaxCritThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMinGlanceThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByAvgGlanceThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMaxGlanceThrt, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMinTPR, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByAvgTPR, SortDirection::Forward);
    this->sorting_methods.insert(ThreatBreakdownSorting::Methods::ByMaxTPR, SortDirection::Forward);
}

ThreatBreakdownModel::~ThreatBreakdownModel() {
    for (const auto& i : spell_stats)
        delete i;
}

void ThreatBreakdownModel::selectSort(const int method) {
    emit layoutAboutToBeChanged();

    auto sorting_method = static_cast<ThreatBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case ThreatBreakdownSorting::Methods::ByTotalThreatAbsolute:
        std::sort(spell_stats.begin(), spell_stats.end(), total_threat);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByTotalThreatPercentage:
        std::sort(spell_stats.begin(), spell_stats.end(), total_threat);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::Icon:
    case ThreatBreakdownSorting::Methods::ByName:
        std::sort(spell_stats.begin(), spell_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMinHitThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), min_hit_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByAvgHitThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_hit_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMaxHitThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), max_hit_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMinCritThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), min_crit_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByAvgCritThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_crit_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMaxCritThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), max_crit_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMinGlanceThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), min_glancing_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByAvgGlanceThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_glancing_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMaxGlanceThrt:
        std::sort(spell_stats.begin(), spell_stats.end(), max_glancing_thrt);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMinTPR:
        std::sort(spell_stats.begin(), spell_stats.end(), min_tpr);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByAvgTPR:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_tpr);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMaxTPR:
        std::sort(spell_stats.begin(), spell_stats.end(), max_tpr);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMinTPET:
        std::sort(spell_stats.begin(), spell_stats.end(), min_tpet);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByAvgTPET:
        std::sort(spell_stats.begin(), spell_stats.end(), avg_tpet);
        select_new_method(sorting_method);
        break;
    case ThreatBreakdownSorting::Methods::ByMaxTPET:
        std::sort(spell_stats.begin(), spell_stats.end(), max_tpet);
        select_new_method(sorting_method);
        break;
    }

    emit layoutChanged();
}

void ThreatBreakdownModel::select_new_method(const ThreatBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method] == SortDirection::Reverse)
        std::reverse(spell_stats.begin(), spell_stats.end());

    const auto next_sort_direction = sorting_methods[new_method] == SortDirection::Forward ? SortDirection::Reverse : SortDirection::Forward;
    current_sorting_method = new_method;

    for (auto& direction : sorting_methods)
        direction = SortDirection::Forward;

    sorting_methods[current_sorting_method] = next_sort_direction;

    emit sortingMethodChanged();
}

int ThreatBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void ThreatBreakdownModel::update_statistics() {
    if (!spell_stats.empty()) {
        beginResetModel();

        for (const auto& i : spell_stats)
            delete i;

        spell_stats.clear();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_spell_stats(spell_stats);

    QList<StatisticsSpell*>::iterator it = spell_stats.begin();

    while (it != spell_stats.end()) {
        if ((*it)->get_total_dmg_dealt() == 0 && (*it)->get_total_thrt_dealt() == 0) {
            delete *it;
            it = spell_stats.erase(it);
        } else
            ++it;
    }

    endInsertRows();

    emit layoutAboutToBeChanged();
    std::sort(spell_stats.begin(), spell_stats.end(), total_threat);
    emit layoutChanged();
}

int ThreatBreakdownModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return spell_stats.count();
}

QVariant ThreatBreakdownModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= spell_stats.count())
        return QVariant();

    const StatisticsSpell* spell_stat = spell_stats[index.row()];

    if (role == ThreatBreakdownSorting::ByName)
        return spell_stat->get_name();
    if (role == ThreatBreakdownSorting::Icon)
        return spell_stat->get_icon();
    if (role == ThreatBreakdownSorting::ByTotalThreatAbsolute)
        return spell_stat->get_total_thrt_dealt();
    if (role == ThreatBreakdownSorting::ByTotalThreatPercentage)
        return QString("%1 %").arg(QString::number(spell_stat->get_percentage_of_threat_dealt() * 100, 'f', 2));
    if (role == ThreatBreakdownSorting::ByMinHitThrt)
        return spell_stat->get_min_hit_thrt();
    if (role == ThreatBreakdownSorting::ByAvgHitThrt)
        return QString::number(static_cast<double>(spell_stat->get_hit_thrt()) / spell_stat->get_hits(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByMaxHitThrt)
        return spell_stat->get_max_hit_thrt();
    if (role == ThreatBreakdownSorting::ByMinCritThrt)
        return spell_stat->get_min_crit_thrt();
    if (role == ThreatBreakdownSorting::ByAvgCritThrt)
        return QString::number(static_cast<double>(spell_stat->get_crit_thrt()) / spell_stat->get_crits(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByMaxCritThrt)
        return spell_stat->get_max_crit_thrt();
    if (role == ThreatBreakdownSorting::ByMinGlanceThrt)
        return spell_stat->get_min_glancing_thrt();
    if (role == ThreatBreakdownSorting::ByAvgGlanceThrt) {
        if (spell_stat->get_glances() == 0)
            return "0";
        return QString::number(static_cast<double>(spell_stat->get_glancing_thrt()) / spell_stat->get_glances(), 'f', 1);
    }
    if (role == ThreatBreakdownSorting::ByMaxGlanceThrt)
        return spell_stat->get_max_glancing_thrt();
    if (role == ThreatBreakdownSorting::ByMinTPR)
        return QString::number(spell_stat->get_min_tpr(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByAvgTPR)
        return QString::number(spell_stat->get_avg_tpr(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByMaxTPR)
        return QString::number(spell_stat->get_max_tpr(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByMinTPET)
        return QString::number(spell_stat->get_min_tpet(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByAvgTPET)
        return QString::number(spell_stat->get_avg_tpet(), 'f', 1);
    if (role == ThreatBreakdownSorting::ByMaxTPET)
        return QString::number(spell_stat->get_max_tpet(), 'f', 1);

    return QVariant();
}

QHash<int, QByteArray> ThreatBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ThreatBreakdownSorting::ByName] = "_name";
    roles[ThreatBreakdownSorting::Icon] = "_icon";
    roles[ThreatBreakdownSorting::ByTotalThreatAbsolute] = "_totalthrtabsolute";
    roles[ThreatBreakdownSorting::ByTotalThreatPercentage] = "_totalthrtpercent";
    roles[ThreatBreakdownSorting::Methods::ByMinHitThrt] = "_minhitthrt";
    roles[ThreatBreakdownSorting::Methods::ByAvgHitThrt] = "_avghitthrt";
    roles[ThreatBreakdownSorting::Methods::ByMaxHitThrt] = "_maxhitthrt";
    roles[ThreatBreakdownSorting::Methods::ByMinCritThrt] = "_mincritthrt";
    roles[ThreatBreakdownSorting::Methods::ByAvgCritThrt] = "_avgcritthrt";
    roles[ThreatBreakdownSorting::Methods::ByMaxCritThrt] = "_maxcritthrt";
    roles[ThreatBreakdownSorting::Methods::ByMinGlanceThrt] = "_minglancethrt";
    roles[ThreatBreakdownSorting::Methods::ByAvgGlanceThrt] = "_avgglancethrt";
    roles[ThreatBreakdownSorting::Methods::ByMaxGlanceThrt] = "_maxglancethrt";
    roles[ThreatBreakdownSorting::Methods::ByMinTPR] = "_mintpr";
    roles[ThreatBreakdownSorting::Methods::ByAvgTPR] = "_avgtpr";
    roles[ThreatBreakdownSorting::Methods::ByMaxTPR] = "_maxtpr";
    roles[ThreatBreakdownSorting::Methods::ByMinTPET] = "_mintpet";
    roles[ThreatBreakdownSorting::Methods::ByAvgTPET] = "_avgtpet";
    roles[ThreatBreakdownSorting::Methods::ByMaxTPET] = "_maxtpet";
    return roles;
}
