
#include "FlatWeaponDamageBuff.h"
#include "Character.h"
#include "CharacterStats.h"

FlatWeaponDamageBuff::FlatWeaponDamageBuff(Character* pchar,
                                           const QString &name,
                                           const QString &icon,
                                           const int duration,
                                           const int base_charges,
                                           const AffectedWeaponSide wpn_side,
                                           const unsigned bonus):
    Buff(pchar, name, icon, duration, base_charges),
    wpn_side(wpn_side),
    bonus(bonus),
    active_bonus(0)
{}

void FlatWeaponDamageBuff::buff_effect_when_applied() {
    active_bonus = base_charges == 0 ? bonus : bonus * static_cast<unsigned>(base_charges);

    switch (wpn_side) {
    case AffectedWeaponSide::Mainhand:
        pchar->increase_mh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Offhand:
        pchar->increase_oh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Ranged:
        pchar->increase_ranged_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::All:
        pchar->increase_mh_flat_damage_bonus(active_bonus);
        pchar->increase_oh_flat_damage_bonus(active_bonus);
        pchar->increase_ranged_flat_damage_bonus(active_bonus);
        break;
    }
}

void FlatWeaponDamageBuff::buff_effect_when_removed() {
    switch (wpn_side) {
    case AffectedWeaponSide::Mainhand:
        pchar->decrease_mh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Offhand:
        pchar->decrease_oh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Ranged:
        pchar->decrease_ranged_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::All:
        pchar->decrease_mh_flat_damage_bonus(active_bonus);
        pchar->decrease_oh_flat_damage_bonus(active_bonus);
        pchar->decrease_ranged_flat_damage_bonus(active_bonus);
        break;
    }

    active_bonus = 0;
}

void FlatWeaponDamageBuff::charge_change_effect() {
    assert(base_charges > 0);
    assert(current_charges > 0);
    assert(active_bonus >= bonus);

    active_bonus -= bonus;

    switch (wpn_side) {
    case AffectedWeaponSide::Mainhand:
        pchar->decrease_mh_flat_damage_bonus(bonus);
        break;
    case AffectedWeaponSide::Offhand:
        pchar->decrease_oh_flat_damage_bonus(bonus);
        break;
    case AffectedWeaponSide::Ranged:
        pchar->decrease_ranged_flat_damage_bonus(bonus);
        break;
    case AffectedWeaponSide::All:
        pchar->decrease_mh_flat_damage_bonus(bonus);
        pchar->decrease_oh_flat_damage_bonus(bonus);
        pchar->decrease_ranged_flat_damage_bonus(bonus);
        break;
    }
}
