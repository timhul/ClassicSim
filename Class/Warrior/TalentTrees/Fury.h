#pragma once

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Fury: public TalentTree {
public:
    Fury(Warrior* pchar);

    Talent* get_booming_voice();
    Talent* get_unbridled_wrath();
    Talent* get_improved_battle_shout();
    Talent* get_dual_wield_specialization();
    Talent* get_improved_execute();
    Talent* get_improved_slam();
    Talent* get_death_wish();
    Talent* get_improved_berserker_rage();
    Talent* get_flurry_talent();
    Talent* get_bloodthirst();

private:
    Warrior* warrior;
    WarriorSpells* spells;
};
