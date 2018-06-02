
#include "GeneralProcs.h"
#include "Character.h"
#include "Faction.h"
#include "Crusader.h"
#include "FieryWeapon.h"
#include "WindfuryTotemAttack.h"

GeneralProcs::GeneralProcs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction)
{
    create_weapon_enchants(mh_enchants, EnchantSlot::MAINHAND);
    mh_enchants.insert(Enchant::Weapon::WindfuryTotem, new WindfuryTotemAttack(pchar->get_engine(), pchar, pchar->get_combat_roll()));

    create_weapon_enchants(oh_enchants, EnchantSlot::OFFHAND);
}

GeneralProcs::~GeneralProcs()
{
    for (auto it : mh_enchants.keys()) {
        delete mh_enchants.value(it);
    }

    for (auto it : oh_enchants.keys()) {
        delete oh_enchants.value(it);
    }
}

void GeneralProcs::switch_faction() const {
    if (faction->is_alliance())
        mh_enchants[Enchant::Weapon::WindfuryTotem]->disable_proc();
}

Proc* GeneralProcs::get_mh_enchant(const Enchant::Weapon enchant) const {
    assert(mh_enchants.contains(enchant));

    return mh_enchants[enchant];
}

Proc* GeneralProcs::get_oh_enchant(const Enchant::Weapon enchant) const {
    assert(oh_enchants.contains(enchant));

    return oh_enchants[enchant];
}

void GeneralProcs::create_weapon_enchants(QMap<Enchant::Weapon, Proc*>& enchants, const int slot) {
    enchants.insert(Enchant::Weapon::Crusader, new Crusader(pchar->get_engine(), pchar, pchar->get_combat_roll(), slot));
    enchants.insert(Enchant::Weapon::FieryWeapon, new FieryWeapon(pchar->get_engine(), pchar, pchar->get_combat_roll(), slot));
}
