#ifndef CASTIF_H
#define CASTIF_H

#include <QObject>
#include <QMap>
#include <QVector>

#include <functional>

class Condition;
class Sentence;
class Spell;

class CastIf: public QObject {
    Q_OBJECT
public:
    CastIf(QString spell_name, QObject* parent = nullptr);
    ~CastIf();

    void add_sentence(Sentence* sentence);
    void add_condition(const QVector<Condition *>& condition);

    void add_variable_assignment(const QString& var, const QString& value);
    QMap<QString, QString>& get_variable_assignments();

    void attempt_cast();

    QString get_spell_name() const;

    Spell* get_spell() const;
    void set_spell(Spell*);

    void dump();

    QVector<Sentence*> sentences;
    QVector<QVector<Condition*>> condition_groups;

private:
    QString spell_name;

    QMap<QString, QString> variable_assignments;
    Spell* spell;

    std::function<bool()> spell_available;

    bool condition_group_fulfilled(const int index) const;

};

#endif // CASTIF_H
