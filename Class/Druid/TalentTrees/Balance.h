#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class Balance: public TalentTree {
public:
    Balance(Druid* druid);
    ~Balance() override = default;

private:
    Druid* druid;
    DruidSpells* spells;

    void add_improved_wrath(QMap<QString, Talent*>& talent_tier);
    void add_improved_natures_grasp(QMap<QString, Talent*>& talent_tier);
    void add_improved_moonfire(QMap<QString, Talent*>& talent_tier);
};
