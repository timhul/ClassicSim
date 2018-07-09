#ifndef BLOODFURY_H
#define BLOODFURY_H

#include "Spell.h"

class BloodFury: public Spell {
public:
    BloodFury(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;

protected:

    void enable_spell_effect() override;
    void disable_spell_effect() override;

private:
};

#endif // BLOODFURY_H
