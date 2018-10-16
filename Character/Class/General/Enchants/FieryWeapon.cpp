
#include "FieryWeapon.h"
#include "FieryWeaponAttack.h"

FieryWeapon::FieryWeapon(Character* pchar, const QString& weapon_identifier, const int weapon) :
    ProcPPM("Fiery Weapon " + weapon_identifier, weapon, 6.0, 0.0, QVector<Proc*>(),
            QVector<ProcInfo::Source>(), pchar),
    fiery_weapon_attack(new FieryWeaponAttack(pchar))
{
    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);

    switch (weapon) {
    case EnchantSlot::MAINHAND:
        proc_sources.append({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing});
        break;
    case EnchantSlot::OFFHAND:
        proc_sources.append({ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing});
        break;
    }
}

FieryWeapon::~FieryWeapon() {
    delete fiery_weapon_attack;
}

void FieryWeapon::proc_effect() {
    fiery_weapon_attack->perform();
}
