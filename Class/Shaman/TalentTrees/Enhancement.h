#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class Enhancement: public TalentTree {
public:
    Enhancement(Shaman* shaman);
    ~Enhancement() override = default;

    Talent* get_thundering_strikes();
    Talent* get_flurry();
    Talent* get_elemental_weapons();
    Talent* get_weapon_mastery();
    Talent* get_stormstrike();

private:
    Shaman* shaman;
    ShamanSpells* spells;
};
