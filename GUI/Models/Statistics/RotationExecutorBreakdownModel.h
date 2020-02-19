#pragma once

#include <QAbstractListModel>
#include <QVector>

class ExecutorOutcome;
class NumberCruncher;
class RotationExecutorListModel;
class StatisticsRotationExecutor;
enum class EventType : int;
enum class SortDirection : int;

class RotationExecutorBreakdownSorting : public QObject {
    Q_OBJECT
public:
    enum Methods
    {
        ByExecutor = Qt::UserRole + 1,
        BySpellStatus,
        ByValue,
    };
    Q_ENUM(Methods)
};

class RotationExecutorBreakdownModel : public QAbstractListModel {
    Q_OBJECT
public:
    RotationExecutorBreakdownModel(RotationExecutorListModel* data_source, QObject* parent = nullptr);

    Q_INVOKABLE void selectSort(const int method);

    void set_index(const int index);
    void update_statistics();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    Q_PROPERTY(int currentSortingMethod READ get_current_sorting_method NOTIFY sortingMethodChanged)
    Q_SIGNAL void sortingMethodChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    RotationExecutorListModel* data_source;
    int executor_index {0};
    RotationExecutorBreakdownSorting::Methods current_sorting_method;
    QMap<RotationExecutorBreakdownSorting::Methods, SortDirection> sorting_methods;

    void select_new_method(const RotationExecutorBreakdownSorting::Methods new_method);
    int get_current_sorting_method() const;
};
