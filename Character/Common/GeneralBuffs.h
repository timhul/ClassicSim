#ifndef GENERALBUFFS_H
#define GENERALBUFFS_H

#include <QVector>

class Character;
class Buff;
class EssenceOfTheRed;
class ExternalBuff;
class Faction;

class SunderArmorBuff;

class GeneralBuffs {
public:
    GeneralBuffs(Character* pchar, Faction* faction);
    ~GeneralBuffs();

    void switch_faction();

    QVector<ExternalBuff*> get_external_buffs() const;
    QVector<ExternalBuff*> get_external_debuffs() const;
    void toggle_external_buff(const QString& buff_name);
    void toggle_external_debuff(const QString& debuff_name);
    bool buff_active(const QString& buff_name) const;
    bool debuff_active(const QString& debuff_name) const;
    void change_setup(const int setup);

    Buff* get_general_buff_by_name(const QString& buff_name) const;

    void clear_all();

private:
    Character* pchar;
    Faction* faction;
    int current_setup;

    QVector<Buff*> buffs;
    QVector<ExternalBuff*> alliance_only_buffs;
    QVector<ExternalBuff*> horde_only_buffs;
    QVector<QVector<QPair<bool, ExternalBuff*>>> external_buffs;
    QVector<QVector<QPair<bool, ExternalBuff*>>> external_debuffs;

    void toggle_external(const QString& name, QVector<QVector<QPair<bool, ExternalBuff *> > > &vec);
    bool external_buff_active(const QString& name, const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec) const;
    void deactivate_buffs_for_current_setup();
    void activate_buffs_for_current_setup();
    void activate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec);
    void deactivate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec);

    bool character_is_mana_user() const;
};

#endif // GENERALBUFFS_H
