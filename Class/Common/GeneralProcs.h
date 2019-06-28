#pragma once

#include <QVector>

class Character;
class Proc;
class Faction;

class GeneralProcs {
public:
    GeneralProcs(Character* pchar, Faction* faction);

    void switch_faction() const;

private:
    Character* pchar;
    Faction* faction;

    QVector<Proc*> alliance_only_procs;
    QVector<Proc*> horde_only_procs;
};
