#ifndef OFFHANDATTACK_H
#define OFFHANDATTACK_H

#include "Spell.h"

class OffhandAttack: public Spell {
public:
    OffhandAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Offhand Attack", engine, pchar, roll, 10.0, 0) {}

protected:
private:
    int spell_effect(const int) const override;
    void add_success_stats(std::string, const int, const int) const;
};

#endif // OFFHANDATTACK_H
