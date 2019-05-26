#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class Enhancement: public TalentTree {
public:
    Enhancement(Shaman* shaman);
    ~Enhancement() override = default;

    Talent* get_stormstrike();

private:
    Shaman* shaman;
    ShamanSpells* spells;

    Talent* get_elemental_weapons();
};
