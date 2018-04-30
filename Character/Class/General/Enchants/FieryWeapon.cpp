
#include "FieryWeapon.h"
#include "Character.h"
#include "FieryWeaponAttack.h"

FieryWeapon::FieryWeapon(Engine* engine, Character* pchar, CombatRoll* roll, const int weapon) :
    ProcPPM("Fiery Weapon", weapon, 6.0, 0.0, false, QVector<Proc*>(), engine, pchar, roll)
{
    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);
}

FieryWeapon::~FieryWeapon() {
}

void FieryWeapon::proc_effect() {
    switch (weapon) {
    case EnchantSlot::MAINHAND:
        add_proc_stats(1, "Mainhand Proc");
        pchar->get_fiery_weapon_attack()->perform(0);
        return;
    case EnchantSlot::OFFHAND:
        add_proc_stats(1, "Offhand Proc");
        pchar->get_fiery_weapon_attack()->perform(0);
        return;
    }
}
