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
};
