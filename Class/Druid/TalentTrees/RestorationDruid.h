#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class RestorationDruid: public TalentTree {
public:
    RestorationDruid(Druid* druid);

private:
    Druid* druid;
    DruidSpells* spells;
};
