#ifndef ENGINEBREAKDOWNMODEL_H
#define ENGINEBREAKDOWNMODEL_H

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsEngine;
enum class Events: int;
enum class SortDirection: int;

class EngineBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods {
        ByEvent = Qt::UserRole + 1,
        ByPercentage,
        ByTotal,
        ByHandledPerMin,
    };
    Q_ENUMS(Methods)
};

class EngineBreakdownModel : public QAbstractListModel
{
    Q_OBJECT
public:
    EngineBreakdownModel(NumberCruncher* statistics_source, QObject *parent = nullptr);
    ~EngineBreakdownModel();

    Q_INVOKABLE void selectSort(const int method);

    void update_statistics();
    double events_handled_per_second() const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_PROPERTY(int currentSortingMethod READ get_current_sorting_method NOTIFY sortingMethodChanged)
    Q_SIGNAL void sortingMethodChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    NumberCruncher* statistics_source;
    StatisticsEngine* engine_stats;
    EngineBreakdownSorting::Methods current_sorting_method;
    unsigned total_events {0};
    unsigned time_in_combat {0};
    QMap<EngineBreakdownSorting::Methods, SortDirection> sorting_methods;
    QList<QPair<Events, unsigned>> event_statistics;

    void select_new_method(const EngineBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};

#endif // ENGINEBREAKDOWNMODEL_H
