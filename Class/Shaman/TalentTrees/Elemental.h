#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class Elemental: public TalentTree {
public:
    Elemental(Shaman* shaman);
    ~Elemental() override = default;

private:
    Shaman* shaman;
    ShamanSpells* spells;

    Talent* get_convection();
    Talent* get_concussion();
    Talent* get_call_of_thunder();
    Talent* get_eye_of_storm();
    Talent* get_lightning_mastery();
};
