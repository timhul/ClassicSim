#ifndef ACTIVEBUFFS_H
#define ACTIVEBUFFS_H

#include <QObject>
#include <QVector>

class Buff;
class SharedBuff;
class Character;
class Faction;
class GeneralBuffs;

class ActiveBuffs: public QObject {
    Q_OBJECT

public:
    ActiveBuffs(Character* pchar, Faction* faction, QObject* parent = nullptr);
    ~ActiveBuffs();

    void add_buff(Buff* buff);
    void remove_buff(Buff* buff);
    SharedBuff* use_shared_buff(const QString& name) const;
    void return_shared_buff(Buff* shared_buff);

    void switch_faction();
    GeneralBuffs* get_general_buffs();
    QVector<QString> get_active_external_buffs();

    void reset();
    void prepare_set_of_combat_iterations();

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
