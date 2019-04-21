#ifndef CASTIF_H
#define CASTIF_H

#include <QMap>
#include <QVector>
#include <functional>

class Condition;
class Sentence;
class Spell;
class StatisticsRotationExecutor;
enum class SpellStatus: int;

class RotationExecutor {
public:
    RotationExecutor(QString spell_name);
    ~RotationExecutor();

    void add_sentence(Sentence* sentence);
    void add_condition(const QVector<Condition *>& condition);

    void add_variable_assignment(const QString& var, const QString& value);
    QMap<QString, QString>& get_variable_assignments();

    void attempt_cast();

    QString get_spell_name() const;
    QString get_conditions_string() const;

    Spell* get_spell() const;
    void set_spell(Spell*);

    void prepare_set_of_combat_iterations(StatisticsRotationExecutor* rotation_statistics);
    void finish_set_of_combat_iterations();

    void dump();

    QVector<Sentence*> sentences;
    QVector<QVector<Condition*>> condition_groups;

private:
    Spell* spell {nullptr};
    StatisticsRotationExecutor* rotation_statistics {nullptr};
    const QString spell_name;

    unsigned successful_casts {0};
    unsigned no_condition_group_fulfilled {0};
    QMap<SpellStatus, unsigned> spell_status_statistics;
    QMap<QString, QString> variable_assignments;

    bool condition_group_fulfilled(const int index) const;
};

#endif // CASTIF_H
