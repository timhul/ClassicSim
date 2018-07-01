#ifndef FIERYWEAPONATTACK_H
#define FIERYWEAPONATTACK_H

#include "Spell.h"

class FieryWeaponAttack: public Spell {
public:
    FieryWeaponAttack(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;

protected:
private:
};

#endif // FIERYWEAPONATTACK_H
