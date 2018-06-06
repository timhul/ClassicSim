#ifndef GENERALBUFFS_H
#define GENERALBUFFS_H

#include <QObject>
#include <QVector>

class Character;
class ExternalBuff;
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

    QVector<ExternalBuff *> get_external_buffs() const;
    void toggle_external_buff(const QString& buff_name);
    bool buff_active(const QString& buff_name) const;

private:
    Character* pchar;
    Faction* faction;

    QVector<Buff*> buffs;
    QVector<Buff*> alliance_only_buffs;
    QVector<Buff*> horde_only_buffs;
    QVector<ExternalBuff*> external_buffs;

    HolyStrength* holy_strength_mh;
    HolyStrength* holy_strength_oh;
};

#endif // GENERALBUFFS_H
