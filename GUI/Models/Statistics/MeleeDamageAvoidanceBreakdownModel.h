#ifndef DAMAGEBREAKDOWNMODEL_H
#define DAMAGEBREAKDOWNMODEL_H

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsSpell;

class MeleeDamageAvoidanceBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods {
        ByName = Qt::UserRole + 1,
        Icon,
        ByTotalAttempts,
        ByNumHits,
        ByHitPercent,
        ByNumCrits,
        ByCritPercent,
        ByNumGlances,
        ByGlancePercent,
        ByNumMisses,
        ByMissPercent,
        ByNumDodges,
        ByDodgePercent,
        ByNumParries,
        ByParryPercent
    };
    Q_ENUMS(Methods)
};

class MeleeDamageAvoidanceBreakdownModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MeleeDamageAvoidanceBreakdownModel(NumberCruncher* statistics_source, QObject *parent = nullptr);
    ~MeleeDamageAvoidanceBreakdownModel();

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
    QHash<MeleeDamageAvoidanceBreakdownSorting::Methods, bool> sorting_methods;
    QList<StatisticsSpell*> spell_stats;
    MeleeDamageAvoidanceBreakdownSorting::Methods current_sorting_method;

    void select_new_method(const MeleeDamageAvoidanceBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};

#endif // DAMAGEBREAKDOWNMODEL_H
