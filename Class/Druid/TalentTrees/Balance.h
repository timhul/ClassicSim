#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class Balance: public TalentTree {
public:
    Balance(Druid* druid);
    ~Balance() override = default;

    void add_improved_natures_grasp(QMap<QString, Talent*>& talent_tier);

private:
    Druid* druid;
    DruidSpells* spells;
};
