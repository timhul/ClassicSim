#pragma once

#include <QAbstractListModel>
#include <QVector>

class ExecutorOutcome;
class NumberCruncher;
class RotationExecutorBreakdownModel;
class StatisticsRotationExecutor;
enum class EventType : int;

class RotationExecutorListRoles : public QObject {
    Q_OBJECT
public:
    enum Methods
    {
        Name = Qt::UserRole + 1,
        Index,
        Selected,
    };
    Q_ENUM(Methods)
};

class RotationExecutorListModel : public QAbstractListModel {
    Q_OBJECT
public:
    RotationExecutorListModel(NumberCruncher* statistics_source, QObject* parent = nullptr);
    ~RotationExecutorListModel();

    Q_INVOKABLE void selectExecutor(const int executor_index);
    void update_statistics();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    RotationExecutorBreakdownModel* executor_breakdown_model;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    friend class RotationExecutorBreakdownModel;

    NumberCruncher* statistics_source;
    int executor_index {0};
    QList<QList<ExecutorOutcome*>> executor_outcomes;

    void delete_list();
};
