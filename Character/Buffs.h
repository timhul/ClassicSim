#ifndef BUFFS_H
#define BUFFS_H

#include <QObject>
#include <QVector>

class Character;
class Faction;
class Buff;
class HolyStrength;

class Buffs: public QObject {
    Q_OBJECT

public:
    Buffs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~Buffs();

    void add_buff(Buff* buff);
    void remove_one_buff(Buff* buff);
    void reset();

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

#endif // BUFFS_H
