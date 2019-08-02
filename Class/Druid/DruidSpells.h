#pragma once

#include "CharacterSpells.h"

class Buff;
class ClearcastingDruid;
class Druid;
class Proc;

class DruidSpells: public CharacterSpells {
public:
    DruidSpells(Druid* druid);
    ~DruidSpells() override;

    Buff* get_natures_grace() const;
    Proc* get_omen_of_clarity() const;

    bool omen_of_clarity_active() const;

private:
    Druid* druid;

    Buff* natures_grace;
    ClearcastingDruid* omen_of_clarity;
};
