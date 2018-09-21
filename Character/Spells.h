#ifndef SPELLS_H
#define SPELLS_H

#include <QObject>
#include <QVector>

class Berserking;
class BloodFury;
class Character;
class Spell;
class MainhandAttack;
class OffhandAttack;

class Spells: public QObject {
    Q_OBJECT

public:
    Spells(Character* pchar, QObject* parent = nullptr);
    virtual ~Spells();

    virtual void reset() = 0;

    virtual void start_attack();
    virtual void mh_auto_attack(const int);
    virtual void oh_auto_attack(const int);
    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);

    void add_statistics();

    virtual MainhandAttack* get_mh_attack() const;
    virtual OffhandAttack* get_oh_attack() const;

    Berserking* get_berserking() const;
    BloodFury* get_blood_fury() const;

protected:
    Character* pchar;
    QVector<Spell*> spells;

    MainhandAttack* mh_attack;
    OffhandAttack* oh_attack;

    Berserking* berserking;
    BloodFury* blood_fury;

private:
};

#endif // SPELLS_H
