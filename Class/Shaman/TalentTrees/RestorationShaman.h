#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class RestorationShaman : public TalentTree {
public:
    RestorationShaman(Shaman* shaman);
    ~RestorationShaman() override = default;

private:
    Shaman* shaman;
    ShamanSpells* spells;

    void add_natures_guidance(QMap<QString, Talent*>& talent_tier);
    void add_tidal_mastery(QMap<QString, Talent*>& talent_tier);
    void add_ancestral_healing(QMap<QString, Talent*>& talent_tier);
    void add_healing_way(QMap<QString, Talent*>& talent_tier);
};
