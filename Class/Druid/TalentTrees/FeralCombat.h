#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class FeralCombat: public TalentTree {
public:
    FeralCombat(Druid* druid);
    ~FeralCombat() override = default;

private:
    Druid* druid;
    DruidSpells* spells;

    void add_feral_aggression(QMap<QString, Talent*>& talent_tier);
    void add_sharpened_claws(QMap<QString, Talent*>& talent_tier);
    void add_improved_shred(QMap<QString, Talent*>& talent_tier);
    void add_predatory_strikes(QMap<QString, Talent*>& talent_tier);
};
