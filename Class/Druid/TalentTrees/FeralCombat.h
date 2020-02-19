#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class FeralCombat : public TalentTree {
public:
    FeralCombat(Druid* druid);

private:
    Druid* druid;
    DruidSpells* spells;

    void add_feral_aggression(QMap<QString, Talent*>& talent_tier);
    void add_sharpened_claws(QMap<QString, Talent*>& talent_tier);
    void add_improved_shred(QMap<QString, Talent*>& talent_tier);
    void add_predatory_strikes(QMap<QString, Talent*>& talent_tier);
    void add_blood_frenzy(QMap<QString, Talent*>& talent_tier);
    void add_heart_of_the_wild(QMap<QString, Talent*>& talent_tier);
    void add_leader_of_the_pack(QMap<QString, Talent*>& talent_tier);
};
