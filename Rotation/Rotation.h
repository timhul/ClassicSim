#ifndef ROTATION_H
#define ROTATION_H

#include <QObject>
#include <QMap>
#include <QVector>

class CastIf;
class Character;
class Buff;
class Spell;

class Rotation: public QObject {
    Q_OBJECT
public:
    Rotation(Character* pchar, QObject* parent = nullptr);
    virtual ~Rotation();

    void perform_rotation() const;

    void set_class(const QString class_name);
    void set_name(const QString name);
    void set_description(const QString desc);
    void add_variable(const QString var, const QString value);
    void add_prerequisite(const QString key, const QString value);
    void add_cast_if(CastIf* cast_if);

    QString get_class() const;
    QString get_name() const;
    QString get_description() const;

    void link_spells();
    void add_conditionals(const int index);

    void dump();

protected:
    virtual Spell* get_spell_from_name(const QString& spell_name) const = 0;
    virtual Buff* get_buff_from_name(const QString& buff_name) const = 0;
    int get_builtin_variable(const QString& var_name) const;

private:
    Character* pchar;
    QString class_name;
    QString name;
    QString description;
    QMap<QString, QString> defined_variables;
    QMap<QString, QString> prerequisites;
    QVector<CastIf*> cast_ifs;
};

#endif // ROTATION_H
