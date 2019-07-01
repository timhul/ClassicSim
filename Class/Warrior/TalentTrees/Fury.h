#pragma once

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Fury: public TalentTree {
public:
    Fury(Warrior* pchar);

private:
    Warrior* warrior;
    WarriorSpells* spells;

    void add_booming_voice(QMap<QString, Talent*>& talent_tier);
    void add_unbridled_wrath(QMap<QString, Talent*>& talent_tier);
    void add_improved_battle_shout(QMap<QString, Talent*>& talent_tier);
    void add_dual_wield_specialization(QMap<QString, Talent*>& talent_tier);
    void add_improved_execute(QMap<QString, Talent*>& talent_tier);
    void add_improved_slam(QMap<QString, Talent*>& talent_tier);
    void add_death_wish(QMap<QString, Talent*>& talent_tier);
    void add_improved_berserker_rage(QMap<QString, Talent*>& talent_tier);
    void add_flurry_talent(QMap<QString, Talent*>& talent_tier);
    void add_bloodthirst(QMap<QString, Talent*>& talent_tier);
};
