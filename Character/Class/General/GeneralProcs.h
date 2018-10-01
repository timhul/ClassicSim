#ifndef GENERALPROCS_H
#define GENERALPROCS_H

#include <QObject>
#include <QVector>
#include <QMap>

class Character;
class Proc;
class Faction;

namespace Enchant {
enum Weapon {
    Crusader = 0,
    FieryWeapon,
    WindfuryTotem
};
}

class GeneralProcs: public QObject {
    Q_OBJECT

public:
    GeneralProcs(Character* pchar, Faction* faction, QObject* parent = nullptr);
    ~GeneralProcs();

    void switch_faction() const;

    Proc* get_mh_enchant(const Enchant::Weapon) const;
    Proc* get_oh_enchant(const Enchant::Weapon) const;

private:
    Character* pchar;
    Faction* faction;

    QMap<Enchant::Weapon, Proc*> mh_enchants;
    QMap<Enchant::Weapon, Proc*> oh_enchants;

    void create_weapon_enchants(QMap<Enchant::Weapon, Proc*>& enchants, const int slot);
    void delete_objects(const QMap<Enchant::Weapon, Proc*>& map);

    QVector<Proc*> alliance_only_procs;
    QVector<Proc*> horde_only_procs;
};

#endif // GENERALPROCS_H
