#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class RestorationShaman: public TalentTree {
public:
    RestorationShaman(Shaman* shaman);
    ~RestorationShaman() override = default;

private:
    Shaman* shaman;
    ShamanSpells* spells;

    Talent* get_ancestral_healing();
    Talent* get_healing_way();
};
