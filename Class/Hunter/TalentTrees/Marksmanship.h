#pragma once

#include "TalentTree.h"

class Hunter;
class HunterSpells;
class Talent;

class Marksmanship: public TalentTree {
public:
    Marksmanship(Hunter* pchar);
    ~Marksmanship() override = default;

private:
    Hunter* hunter;
    HunterSpells* spells;

    void add_efficiency(QMap<QString, Talent*>& talent_tier);
    void add_improved_hunters_mark(QMap<QString, Talent*>& talent_tier);
    void add_lethal_shots(QMap<QString, Talent*>& talent_tier);
    void add_aimed_shot(QMap<QString, Talent*>& talent_tier);
    void add_mortal_shots(QMap<QString, Talent*>& talent_tier);
    void add_barrage(QMap<QString, Talent*>& talent_tier);
    void add_ranged_weapon_specialization(QMap<QString, Talent*>& talent_tier);
    void add_trueshot_aura(QMap<QString, Talent*>& talent_tier);
};
