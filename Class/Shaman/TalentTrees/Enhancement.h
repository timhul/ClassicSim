#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class Enhancement: public TalentTree {
public:
    Enhancement(Shaman* shaman);
    ~Enhancement() override = default;

    Talent* get_stormstrike();
    Talent* get_elemental_weapons();

private:
    Shaman* shaman;
    ShamanSpells* spells;
};
