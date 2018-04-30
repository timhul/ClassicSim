#ifndef SPELLS_H
#define SPELLS_H

#include <QObject>
#include <QVector>

class Character;
class Spell;
class FieryWeaponAttack;

class Spells: public QObject {
    Q_OBJECT

public:
    Spells(Character* pchar, QObject* parent = 0);
    ~Spells();

    void add_spell(Spell* spell);
    void reset();

    FieryWeaponAttack* get_fiery_weapon() const;

private:
    Character* pchar;
    QVector<Spell*> spells;

    FieryWeaponAttack* fiery_weapon_attack;
};

#endif // SPELLS_H
