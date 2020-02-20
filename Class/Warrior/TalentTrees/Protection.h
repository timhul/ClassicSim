#pragma once

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Protection : public TalentTree {
public:
    Protection(Warrior* pchar);

    void add_shield_slam(QMap<QString, Talent*>& talent_tier);

private:
    Warrior* warrior;
    WarriorSpells* spells;

    void add_improved_shield_block(QMap<QString, Talent*>& talent_tier);
    void add_improved_sunder_armor(QMap<QString, Talent*>& talent_tier);
};
