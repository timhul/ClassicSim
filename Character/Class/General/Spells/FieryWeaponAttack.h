#ifndef FIERYWEAPONATTACK_H
#define FIERYWEAPONATTACK_H

#include "Spell.h"

class FieryWeaponAttack: public Spell {
public:
    FieryWeaponAttack(Engine* engine, Character* pchar, CombatRoll* roll);


protected:
private:
    void spell_effect() override;
};

#endif // FIERYWEAPONATTACK_H
