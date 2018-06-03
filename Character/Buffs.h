#ifndef BUFFS_H
#define BUFFS_H

#include <QObject>
#include <QVector>

class Buff;
class Character;
class Faction;

class Buffs: public QObject {
    Q_OBJECT

public:
    Buffs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~Buffs();

    void add_buff(Buff* buff);
    void remove_buff(Buff* buff);
    void reset();

    void switch_faction();

private:
    Character* pchar;
    Faction* faction;

    int next_instance_id;

    QVector<Buff*> buffs;
    QVector<Buff*> alliance_only_buffs;
    QVector<Buff*> horde_only_buffs;
};

#endif // BUFFS_H
