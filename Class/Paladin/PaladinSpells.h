#pragma once

#include "CharacterSpells.h"

class Paladin;
class PaladinSeal;

class PaladinSpells: public CharacterSpells {
public:
    PaladinSpells(Paladin *paladin);

    void apply_seal(PaladinSeal* new_seal);
    void judge_seal(PaladinSeal* seal);

    PaladinSeal* get_active_seal() const;
    PaladinSeal* get_judged_seal() const;

private:
    Paladin* paladin;
    PaladinSeal* active_seal {nullptr};
    PaladinSeal* judged_seal {nullptr};
};
