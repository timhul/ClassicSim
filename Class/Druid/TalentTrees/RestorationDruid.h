#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class RestorationDruid : public TalentTree {
public:
    RestorationDruid(Druid* druid);

private:
    Druid* druid;
    DruidSpells* spells;

    void add_furor(QMap<QString, Talent*>& talent_tier);
    void add_reflection(QMap<QString, Talent*>& talent_tier);
};
