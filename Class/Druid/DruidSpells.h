#pragma once

#include "CharacterSpells.h"

class Druid;

class DruidSpells: public CharacterSpells {
public:
    DruidSpells(Druid *druid);
    ~DruidSpells() override;

private:
    Druid* druid;
};
