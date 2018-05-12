#ifndef SPELLS_H
#define SPELLS_H

#include <QObject>
#include <QVector>

class Character;
class Spell;
class MainhandAttack;
class OffhandAttack;
class FieryWeaponAttack;

class Spells: public QObject {
    Q_OBJECT

public:
    Spells(Character* pchar, QObject* parent = 0);
    virtual ~Spells();

    virtual void reset() = 0;

    virtual void rotation(void) = 0;
    virtual void mh_auto_attack(const int) = 0;
    virtual void oh_auto_attack(const int) = 0;
    virtual void start_attack();
    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);

    void add_statistics();

    virtual MainhandAttack* get_mh_attack() const;
    virtual OffhandAttack* get_oh_attack() const;
    FieryWeaponAttack* get_fiery_weapon() const;

protected:
    Character* pchar;
    QVector<Spell*> spells;

    MainhandAttack* mh_attack;
    OffhandAttack* oh_attack;
    FieryWeaponAttack* fiery_weapon_attack;

private:
};

#endif // SPELLS_H
