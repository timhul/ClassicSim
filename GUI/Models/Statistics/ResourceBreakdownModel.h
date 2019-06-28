#pragma once

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class StatisticsResource;
enum class SortDirection: int;

class ResourceBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods {
        ByName = Qt::UserRole + 1,
        Icon,
        ByManaPer5,
        ByRagePer5,
        ByEnergyPer5
    };
    Q_ENUMS(Methods)
};

class ResourceBreakdownModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ResourceBreakdownModel(NumberCruncher* statistics_source, QObject *parent = nullptr);
    ~ResourceBreakdownModel();

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
    QMap<ResourceBreakdownSorting::Methods, SortDirection> sorting_methods;
    QList<StatisticsResource*> resource_stats;
    ResourceBreakdownSorting::Methods current_sorting_method;

    void select_new_method(const ResourceBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};
