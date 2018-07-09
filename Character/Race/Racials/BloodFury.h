#ifndef BLOODFURY_H
#define BLOODFURY_H

#include "Spell.h"

class BloodFury: public Spell {
public:
    BloodFury(Engine* engine, Character* pchar, CombatRoll* roll);

    bool is_ready_spell_specific() const override;
    void spell_effect() override;

protected:
private:
};

#endif // BLOODFURY_H
