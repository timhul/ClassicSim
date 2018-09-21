#ifndef DRUIDSPELLS_H
#define DRUIDSPELLS_H

#include "Spells.h"

class Druid;

class DruidSpells: public Spells {
    Q_OBJECT

public:
    DruidSpells(Druid *druid);
    virtual ~DruidSpells() override;

    void reset() override;

private:
    Druid* druid;
};

#endif // DRUIDSPELLS_H
