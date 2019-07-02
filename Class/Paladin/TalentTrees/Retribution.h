#pragma once

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class Retribution: public TalentTree {
public:
    Retribution(Paladin* paladin);
    ~Retribution() override = default;

private:
    Paladin* paladin;
    PaladinSpells* spells;

    void add_benediction(QMap<QString, Talent*>& talent_tier);
    void add_improved_judgement(QMap<QString, Talent*>& talent_tier);
    void add_improved_seal_of_the_crusader(QMap<QString, Talent*>& talent_tier);
    void add_conviction(QMap<QString, Talent*>& talent_tier);
    void add_seal_of_command(QMap<QString, Talent*>& talent_tier);
    void add_two_handed_weapon_specialization(QMap<QString, Talent*>& talent_tier);
    void add_sanctity_aura(QMap<QString, Talent*>& talent_tier);
    void add_vengeance(QMap<QString, Talent*>& talent_tier);
};
