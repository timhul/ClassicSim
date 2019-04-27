#ifndef PALADINSPELLS_H
#define PALADINSPELLS_H

#include "CharacterSpells.h"

class Buff;
class Judgement;
class ManaPotion;
class Paladin;
class PaladinSeal;
class SealOfTheCrusader;

class PaladinSpells: public CharacterSpells {
public:
    PaladinSpells(Paladin *paladin);

    Judgement* get_judgement() const;
    ManaPotion* get_mana_potion() const;
    PaladinSeal* get_seal_of_the_crusader() const;

    void apply_seal(PaladinSeal* new_seal);
    PaladinSeal* get_seal() const;

private:
    Paladin* paladin;
    PaladinSeal* current_seal {nullptr};

    Judgement* judgement;
    ManaPotion* mana_potion;
    SealOfTheCrusader* seal_of_the_crusader;
};

#endif // PALADINSPELLS_H
