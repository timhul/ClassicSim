#ifndef SWORDSPECIALIZATION_H
#define SWORDSPECIALIZATION_H

#include "Proc.h"

class Warrior;
class Weapon;

class SwordSpecialization: public Proc {
public:
    SwordSpecialization(Engine* engine, Character* pchar, CombatRoll* roll);
    ~SwordSpecialization() override;

    void proc_effect() override;
    void increase_effect_via_talent() override;
    void decrease_effect_via_talent() override;

    bool proc_specific_conditions_fulfilled() const override;
protected:
private:
    Warrior* warr;


    bool weapon_is_sword(Weapon*) const;
};

#endif // SWORDSPECIALIZATION_H
