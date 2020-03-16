#pragma once

#include "TalentTree.h"

class Warrior;
class WarriorSpells;

class Protection : public TalentTree {
public:
    Protection(Warrior* pchar);

private:
    Warrior* warrior;
    WarriorSpells* spells;

    void add_improved_shield_block(QMap<QString, Talent*>& talent_tier);
    void add_improved_sunder_armor(QMap<QString, Talent*>& talent_tier);
};
