#ifndef DRUIDSPELLS_H
#define DRUIDSPELLS_H

#include "CharacterSpells.h"

class Druid;

class DruidSpells: public CharacterSpells {
public:
    DruidSpells(Druid *druid);
    ~DruidSpells() override;

private:
    Druid* druid;
};

#endif // DRUIDSPELLS_H
