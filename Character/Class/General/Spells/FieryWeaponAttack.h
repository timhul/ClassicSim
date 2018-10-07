#ifndef FIERYWEAPONATTACK_H
#define FIERYWEAPONATTACK_H

#include "Spell.h"

class FieryWeaponAttack: public Spell {
public:
    FieryWeaponAttack(Character* pchar);


protected:
private:
    void spell_effect() override;
};

#endif // FIERYWEAPONATTACK_H
