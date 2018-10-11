#ifndef WARRIORROTATION_H
#define WARRIORROTATION_H

#include "Rotation.h"

class Spell;
class Warrior;

class WarriorRotation: public Rotation {
public:
    WarriorRotation(QObject* parent = nullptr);

private:
    Warrior* warrior;

    Spell* get_spell_from_name(const QString& spell_name) const override;
    Buff* get_buff_from_name(const QString &buff_name) const override;
};

#endif // WARRIORROTATION_H
