#pragma once

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsSpell;
enum class SortDirection : int;

class ThreatBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods
    {
        ByName = Qt::UserRole + 1,
        Icon,
        ByTotalThreatAbsolute,
        ByTotalThreatPercentage,
        ByMinHitThrt,
        ByAvgHitThrt,
        ByMaxHitThrt,
        ByMinCritThrt,
        ByAvgCritThrt,
        ByMaxCritThrt,
        ByMinGlanceThrt,
        ByAvgGlanceThrt,
        ByMaxGlanceThrt,
        ByMinTPR,
        ByAvgTPR,
        ByMaxTPR,
        ByMinTPET,
        ByAvgTPET,
        ByMaxTPET,
    };
    Q_ENUM(Methods)
};

class ThreatBreakdownModel : public QAbstractListModel {
    Q_OBJECT
public:
    ThreatBreakdownModel(NumberCruncher* statistics_source, QObject* parent = nullptr);
    ~ThreatBreakdownModel();

    Q_INVOKABLE void selectSort(const int method);

    void update_statistics();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    Q_PROPERTY(int currentSortingMethod READ get_current_sorting_method NOTIFY sortingMethodChanged)
    Q_SIGNAL void sortingMethodChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    NumberCruncher* statistics_source;
    QMap<ThreatBreakdownSorting::Methods, SortDirection> sorting_methods;
    QList<StatisticsSpell*> spell_stats;
    ThreatBreakdownSorting::Methods current_sorting_method;

    void select_new_method(const ThreatBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};
