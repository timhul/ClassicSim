#ifndef DRUIDSPELLS_H
#define DRUIDSPELLS_H

#include "Spells.h"

class Druid;

class DruidSpells: public Spells {
    Q_OBJECT

public:
    DruidSpells(Druid *pchar);
    virtual ~DruidSpells() override;

    void reset() override;

private:
    Druid* pchar;
};

#endif // DRUIDSPELLS_H
