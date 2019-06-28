#pragma once

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsSpell;
enum class SortDirection: int;

class MeleeDamageBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods {
        ByName = Qt::UserRole + 1,
        Icon,
        ByTotalDamageAbsolute,
        ByTotalDamagePercentage,
        ByMinHit,
        ByAvgHit,
        ByMaxHit,
        ByMinCrit,
        ByAvgCrit,
        ByMaxCrit,
        ByMinGlance,
        ByAvgGlance,
        ByMaxGlance,
        ByMinDPR,
        ByAvgDPR,
        ByMaxDPR,
        ByMinDPET,
        ByAvgDPET,
        ByMaxDPET
    };
    Q_ENUMS(Methods)
};

class MeleeDamageBreakdownModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MeleeDamageBreakdownModel(NumberCruncher* statistics_source, QObject *parent = nullptr);
    ~MeleeDamageBreakdownModel();

    Q_INVOKABLE void selectSort(const int method);

    void update_statistics();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_PROPERTY(int currentSortingMethod READ get_current_sorting_method NOTIFY sortingMethodChanged)
    Q_SIGNAL void sortingMethodChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    NumberCruncher* statistics_source;
    QMap<MeleeDamageBreakdownSorting::Methods, SortDirection> sorting_methods;
    QList<StatisticsSpell*> spell_stats;
    MeleeDamageBreakdownSorting::Methods current_sorting_method;

    void select_new_method(const MeleeDamageBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};
