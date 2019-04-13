#ifndef PROCBREAKDOWNMODEL_H
#define PROCBREAKDOWNMODEL_H

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsProc;
enum class SortDirection: int;

class ProcBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods {
        ByName = Qt::UserRole + 1,
        Icon,
        ByAvgProcRate,
        ByNumProcs
    };
    Q_ENUMS(Methods)
};

class ProcBreakdownModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ProcBreakdownModel(NumberCruncher* statistics_source, QObject *parent = nullptr);
    ~ProcBreakdownModel();

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
    QMap<ProcBreakdownSorting::Methods, SortDirection> sorting_methods;
    QList<StatisticsProc*> proc_stats;
    ProcBreakdownSorting::Methods current_sorting_method;

    void select_new_method(const ProcBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};

#endif // PROCBREAKDOWNMODEL_H
