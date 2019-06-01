#ifndef SHAMANSPELLS_H
#define SHAMANSPELLS_H

#include "CharacterSpells.h"

class Buff;
class ClearcastingShaman;
class Proc;
class Shaman;

class ShamanSpells: public CharacterSpells {
public:
    ShamanSpells(Shaman *shaman);
    ~ShamanSpells() override;

    Buff* get_elemental_devastation() const;
    Buff* get_flurry() const;
    Proc* get_clearcasting() const;

    bool clearcasting_active() const;
    void roll_clearcasting();

private:
    Shaman* shaman;
    ClearcastingShaman* clearcasting;
    Buff* elemental_devastation;
    Buff* flurry;
};

#endif // SHAMANSPELLS_H
