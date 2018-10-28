#ifndef DRUIDSPELLS_H
#define DRUIDSPELLS_H

#include "Spells.h"

class Druid;

class DruidSpells: public Spells {
public:
    DruidSpells(Druid *druid);
    virtual ~DruidSpells() override;

private:
    Druid* druid;
};

#endif // DRUIDSPELLS_H
