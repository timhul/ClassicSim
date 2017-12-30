#ifndef HEROICSTRIKE_H
#define HEROICSTRIKE_H

#include "Spell.h"

class HeroicStrike: public Spell {
public:
    HeroicStrike(Engine* engine, Character* pchar) :
        Spell("Heroic Strike", engine, pchar, 0, 13) {}

    int spell_effect(const int) const override;
protected:
private:
};

#endif // HEROICSTRIKE_H
