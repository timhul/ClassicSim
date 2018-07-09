#ifndef BLOODFURY_H
#define BLOODFURY_H

#include "Spell.h"

class Warrior;

class BloodFury: public Spell {
public:
    BloodFury(Engine* engine, Character* pchar, CombatRoll* roll);

    bool is_ready_spell_specific() const override;
    void spell_effect() override;

protected:
private:
    Warrior* pchar;

};

#endif // BLOODFURY_H
