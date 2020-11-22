#pragma once

#include <QAbstractListModel>
#include <QVector>

class NumberCruncher;
class ScaleResult;
class StatisticsProc;
enum class SortDirection : int;

class ScaleResultSorting : public QObject {
    Q_OBJECT
public:
    enum Methods
    {
        ByName = Qt::UserRole + 1,
        ByAbsoluteValue,
        ByRelativeValue,
        ByStandardDeviation,
        ByConfidenceInterval
    };
    Q_ENUM(Methods)
};

class ScaleResultModel : public QAbstractListModel {
    Q_OBJECT
public:
    ScaleResultModel(NumberCruncher* statistics_source, bool for_dps, QObject* parent = nullptr);
    ~ScaleResultModel();

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
    bool for_dps;
    QMap<ScaleResultSorting::Methods, SortDirection> sorting_methods;
    QList<ScaleResult*> scale_results;
    ScaleResultSorting::Methods current_sorting_method;

    void select_new_method(const ScaleResultSorting::Methods new_method);
    int get_current_sorting_method() const;
};
