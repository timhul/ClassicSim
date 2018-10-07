#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "Spell.h"

class Warrior;

class Whirlwind: public Spell {
public:
    Whirlwind(Character* pchar);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;
};



#endif // WHIRLWIND_H
