
#include "Warlock.h"
#include "Weapon.h"

QString Warlock::get_name(void) const {
    return "Warlock";
}

QString Warlock::get_class_color() const {
    return "#9482C9";
}

int Warlock::get_strength_modifier(void) const {
    return 0;
}

int Warlock::get_agility_modifier(void) const {
    return 0;
}

int Warlock::get_stamina_modifier(void) const {
    return 1;
}

int Warlock::get_intellect_modifier(void) const {
    return 2;
}

int Warlock::get_spirit_modifier(void) const {
    return 2;
}

int Warlock::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Warlock::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Warlock::get_ap_per_strength() const {
    return 1;
}

int Warlock::get_ap_per_agi() const {
    return 1;
}

float Warlock::global_cooldown() const {
    return 1.5;
}

void Warlock::initialize_talents() {

}

int Warlock::get_highest_possible_armor_type() const {
    return ArmorTypes::CLOTH;
}

QVector<int> Warlock::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::SWORD, WeaponTypes::STAFF});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::WAND});
    default:
        assert(false);
        return QVector<int>();
    }
}
