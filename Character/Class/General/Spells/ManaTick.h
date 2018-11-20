#ifndef MANATICK_H
#define MANATICK_H

#include "Spell.h"

class Mana;


class ManaTick : public Spell {
public:
    ManaTick(Character* pchar, class Mana* mana);

    void perform_periodic() override;

private:
    class Mana* mana;

    void spell_effect() override;
};

#endif // MANATICK_H
