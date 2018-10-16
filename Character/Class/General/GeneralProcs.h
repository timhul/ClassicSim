#ifndef GENERALPROCS_H
#define GENERALPROCS_H

#include <QVector>

class Character;
class Proc;
class Faction;

class GeneralProcs {
public:
    GeneralProcs(Character* pchar, Faction* faction);
    ~GeneralProcs();

    void switch_faction() const;

private:
    Character* pchar;
    Faction* faction;

    QVector<Proc*> alliance_only_procs;
    QVector<Proc*> horde_only_procs;
};

#endif // GENERALPROCS_H
