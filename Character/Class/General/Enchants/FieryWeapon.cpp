
#include "FieryWeapon.h"
#include "FieryWeaponAttack.h"

FieryWeapon::FieryWeapon(Engine* engine, Character* pchar, CombatRoll* roll, const int weapon) :
    ProcPPM("Fiery Weapon", weapon, 6.0, 0.0, false, QVector<Proc*>(),
            QVector<ProcInfo::Source>(), engine, pchar, roll),
    fiery_weapon_attack(new FieryWeaponAttack(engine, pchar, roll))
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
    fiery_weapon_attack->perform(0);
}
