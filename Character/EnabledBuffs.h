#ifndef ENABLEDBUFFS_H
#define ENABLEDBUFFS_H

#include <QVector>

class Buff;
class SharedBuff;
class Character;
class Faction;
class GeneralBuffs;

class EnabledBuffs {
public:
    EnabledBuffs(Character* pchar, Faction* faction);
    ~EnabledBuffs();

    void add_buff(Buff* buff);
    void remove_buff(Buff* buff);
    SharedBuff* use_shared_buff(const QString& name) const;
    void return_shared_buff(Buff* shared_buff);

    void switch_faction();
    GeneralBuffs* get_general_buffs();
    QVector<QString> get_active_external_buffs();
    QVector<QString> get_active_external_debuffs();

    Buff* get_buff_by_name(const QString& name) const;

    void reset();
    void clear_all();
    void prepare_set_of_combat_iterations();

    void add_pre_combat_buff(Buff* buff);
    void remove_pre_combat_buff(Buff* buff);
    void apply_pre_combat_buffs();

private:
    Character* pchar;
    Faction* faction;

    int next_instance_id;

    GeneralBuffs* general_buffs;

    QVector<Buff*> pre_combat_buffs;
    QVector<Buff*> enabled_buffs;
    QVector<Buff*> alliance_only_buffs;
    QVector<Buff*> horde_only_buffs;

    void remove_buff(Buff* buff, QVector<Buff*>& buffs);
};

#endif // ENABLEDBUFFS_H
