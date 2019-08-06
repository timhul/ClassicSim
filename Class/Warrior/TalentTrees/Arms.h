#pragma once

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Arms: public TalentTree {
public:
    Arms(Warrior* pchar);

    Talent* get_mortal_strike();

private:
    Warrior* warr;
    WarriorSpells* spells;

    void add_improved_heroic_strike(QMap<QString, Talent*>& talent_tier);
    void add_improved_rend(QMap<QString, Talent*>& talent_tier);
    void add_improved_overpower(QMap<QString, Talent*>& talent_tier);
    void add_anger_management(QMap<QString, Talent*>& talent_tier);
    void add_deep_wounds(QMap<QString, Talent*>& talent_tier);
    void add_sword_specialization(QMap<QString, Talent*>& talent_tier);
};
