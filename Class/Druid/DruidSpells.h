#pragma once

#include "CharacterSpells.h"

class Buff;
class Druid;

class DruidSpells: public CharacterSpells {
public:
    DruidSpells(Druid* druid);
    ~DruidSpells() override;

    Buff* get_natures_grace() const;

private:
    Druid* druid;

    Buff* natures_grace;
};
