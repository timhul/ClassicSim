#pragma once

#include "TalentTree.h"

class Shaman;
class ShamanSpells;

class Enhancement: public TalentTree {
public:
    Enhancement(Shaman* shaman);
    ~Enhancement() override = default;

private:
    Shaman* shaman;
    ShamanSpells* spells;

    void add_thundering_strikes(QMap<QString, Talent*>& talent_tier);
    void add_flurry(QMap<QString, Talent*>& talent_tier);
    void add_elemental_weapons(QMap<QString, Talent*>& talent_tier);
    void add_weapon_mastery(QMap<QString, Talent*>& talent_tier);
    void add_stormstrike(QMap<QString, Talent*>& talent_tier);
};
