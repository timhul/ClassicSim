#ifndef GENERALBUFFS_H
#define GENERALBUFFS_H

#include <QObject>
#include <QVector>

class Character;
class ExternalBuff;
class Faction;
class Buff;
class HolyStrength;

class SunderArmorBuff;

class GeneralBuffs: public QObject {
    Q_OBJECT

public:
    GeneralBuffs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~GeneralBuffs();

    void switch_faction();

    HolyStrength* get_holy_strength_mh() const;
    HolyStrength* get_holy_strength_oh() const;

    QVector<ExternalBuff*> get_external_buffs() const;
    QVector<ExternalBuff*> get_external_debuffs() const;
    void toggle_external_buff(const QString& buff_name);
    void toggle_external_debuff(const QString& debuff_name);
    bool buff_active(const QString& buff_name) const;
    bool debuff_active(const QString& debuff_name) const;
    void change_setup(const int setup);

private:
    Character* pchar;
    Faction* faction;
    int current_setup;

    QVector<Buff*> buffs;
    QVector<Buff*> alliance_only_buffs;
    QVector<Buff*> horde_only_buffs;
    QVector<QVector<QPair<bool, ExternalBuff*>>> external_buffs;
    QVector<QVector<QPair<bool, ExternalBuff*>>> external_debuffs;

    HolyStrength* holy_strength_mh;
    HolyStrength* holy_strength_oh;

    void toggle_external(const QString& name, QVector<QVector<QPair<bool, ExternalBuff *> > > &vec);
    bool external_buff_active(const QString& name, const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec) const;
    void deactivate_buffs_for_current_setup();
    void activate_buffs_for_current_setup();
    void activate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec);
    void deactivate_externals(const QVector<QVector<QPair<bool, ExternalBuff*>>>& vec);
};

#endif // GENERALBUFFS_H
