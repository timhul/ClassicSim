#include "FlatWeaponDamageBuff.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Utils/Check.h"

FlatWeaponDamageBuff::FlatWeaponDamageBuff(Character* pchar,
                                           const QString &name,
                                           const QString &icon,
                                           const int duration,
                                           const int base_charges,
                                           const AffectedWeaponSide wpn_side,
                                           const unsigned bonus):
    SelfBuff(pchar, name, icon, duration, base_charges),
    wpn_side(wpn_side),
    bonus(bonus),
    active_bonus(0)
{}

void FlatWeaponDamageBuff::buff_effect_when_applied() {
    active_bonus = base_charges == 0 ? bonus : bonus * static_cast<unsigned>(base_charges);

    switch (wpn_side) {
    case AffectedWeaponSide::Mainhand:
        pchar->get_stats()->increase_mh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Offhand:
        pchar->get_stats()->increase_oh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Ranged:
        pchar->get_stats()->increase_ranged_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::All:
        pchar->get_stats()->increase_mh_flat_damage_bonus(active_bonus);
        pchar->get_stats()->increase_oh_flat_damage_bonus(active_bonus);
        pchar->get_stats()->increase_ranged_flat_damage_bonus(active_bonus);
        break;
    }
}

void FlatWeaponDamageBuff::buff_effect_when_removed() {
    switch (wpn_side) {
    case AffectedWeaponSide::Mainhand:
        pchar->get_stats()->decrease_mh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Offhand:
        pchar->get_stats()->decrease_oh_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::Ranged:
        pchar->get_stats()->decrease_ranged_flat_damage_bonus(active_bonus);
        break;
    case AffectedWeaponSide::All:
        pchar->get_stats()->decrease_mh_flat_damage_bonus(active_bonus);
        pchar->get_stats()->decrease_oh_flat_damage_bonus(active_bonus);
        pchar->get_stats()->decrease_ranged_flat_damage_bonus(active_bonus);
        break;
    }

    active_bonus = 0;
}

void FlatWeaponDamageBuff::charge_change_effect() {
    check((base_charges > 0), "Base charges was zero while a charge was consumed");
    check((base_charges > 0), "Current charges was zero while a charge was consumed");
    check((active_bonus >= bonus), "Underflow decrease");

    active_bonus -= bonus;

    switch (wpn_side) {
    case AffectedWeaponSide::Mainhand:
        pchar->get_stats()->decrease_mh_flat_damage_bonus(bonus);
        break;
    case AffectedWeaponSide::Offhand:
        pchar->get_stats()->decrease_oh_flat_damage_bonus(bonus);
        break;
    case AffectedWeaponSide::Ranged:
        pchar->get_stats()->decrease_ranged_flat_damage_bonus(bonus);
        break;
    case AffectedWeaponSide::All:
        pchar->get_stats()->decrease_mh_flat_damage_bonus(bonus);
        pchar->get_stats()->decrease_oh_flat_damage_bonus(bonus);
        pchar->get_stats()->decrease_ranged_flat_damage_bonus(bonus);
        break;
    }
}
