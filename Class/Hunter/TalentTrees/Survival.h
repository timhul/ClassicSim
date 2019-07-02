#pragma once

#include "TalentTree.h"

class Hunter;
class HunterSpells;

class Survival: public TalentTree {
public:
    Survival(Hunter* pchar);
    ~Survival() override = default;

private:
    Hunter* hunter;
    HunterSpells* spells;

    void add_monster_slaying(QMap<QString, Talent*>& talent_tier);
    void add_humanoid_slaying(QMap<QString, Talent*>& talent_tier);
    void add_surefooted(QMap<QString, Talent*>& talent_tier);
    void add_killer_instinct(QMap<QString, Talent*>& talent_tier);
    void add_lightning_reflexes(QMap<QString, Talent*>& talent_tier);
};
