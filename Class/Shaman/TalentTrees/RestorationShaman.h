#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class RestorationShaman: public TalentTree {
public:
    RestorationShaman(Shaman* shaman);
    ~RestorationShaman() override = default;

    Talent* get_natures_guidance();
    Talent* get_tidal_mastery();

private:
    Shaman* shaman;
    ShamanSpells* spells;

    Talent* get_ancestral_healing();
    Talent* get_healing_way();
};
