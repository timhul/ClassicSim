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

    void add_convection(QMap<QString, Talent*>& talent_tier);
    void add_concussion(QMap<QString, Talent*>& talent_tier);
    void add_elemental_focus(QMap<QString, Talent*>& talent_tier);
    void add_call_of_thunder(QMap<QString, Talent*>& talent_tier);
    void add_eye_of_storm(QMap<QString, Talent*>& talent_tier);
    void add_elemental_devastation(QMap<QString, Talent*>& talent_tier);
    void add_lightning_mastery(QMap<QString, Talent*>& talent_tier);
};
