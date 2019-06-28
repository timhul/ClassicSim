#pragma once

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsBuff;
enum class SortDirection: int;

class BuffBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods {
        ByName = Qt::UserRole + 1,
        Icon,
        ByMinUptime,
        ByMaxUptime,
        ByAvgUptime
    };
    Q_ENUMS(Methods)
};

class BuffBreakdownModel : public QAbstractListModel
{
    Q_OBJECT
public:
    BuffBreakdownModel(NumberCruncher* statistics_source, QObject *parent = nullptr);
    ~BuffBreakdownModel();

    Q_INVOKABLE void selectSort(const int method);

    void update_statistics();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_PROPERTY(int currentSortingMethod READ get_current_sorting_method NOTIFY sortingMethodChanged)
    Q_SIGNAL void sortingMethodChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
    NumberCruncher* statistics_source;
    QMap<BuffBreakdownSorting::Methods, SortDirection> sorting_methods;
    QList<StatisticsBuff*> buff_stats;
    BuffBreakdownSorting::Methods current_sorting_method;

    void select_new_method(const BuffBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
    virtual void add_statistics();
};
