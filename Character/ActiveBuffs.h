#ifndef ACTIVEBUFFS_H
#define ACTIVEBUFFS_H

#include <QObject>
#include <QVector>

class Buff;
class Character;
class Faction;
class GeneralBuffs;

class ActiveBuffs: public QObject {
    Q_OBJECT

public:
    ActiveBuffs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~ActiveBuffs();

    void add_buff(Buff* buff);
    void remove_buff(Buff* buff);
    void reset();

    void switch_faction();

private:
    Character* pchar;
    Faction* faction;

    int next_instance_id;

    GeneralBuffs* general_buffs;

    QVector<Buff*> active_buffs;
    QVector<Buff*> alliance_only_buffs;
    QVector<Buff*> horde_only_buffs;
};

#endif // ACTIVEBUFFS_H
