#ifndef GENERALBUFFS_H
#define GENERALBUFFS_H

#include <QObject>
#include <QVector>

class Character;
class Faction;
class Buff;
class HolyStrength;

class GeneralBuffs: public QObject {
    Q_OBJECT

public:
    GeneralBuffs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~GeneralBuffs();

    void switch_faction();

    HolyStrength* get_holy_strength_mh() const;
    HolyStrength* get_holy_strength_oh() const;

private:
    Character* pchar;
    Faction* faction;

    QVector<Buff*> buffs;
    QVector<Buff*> alliance_only_buffs;
    QVector<Buff*> horde_only_buffs;

    HolyStrength* holy_strength_mh;
    HolyStrength* holy_strength_oh;
};

#endif // GENERALBUFFS_H
