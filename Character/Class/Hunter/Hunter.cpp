
#include "Hunter.h"
#include "Weapon.h"

QString Hunter::get_name(void) const {
    return "Hunter";
}

QString Hunter::get_class_color() const {
    return "#ABD473";
}

int Hunter::get_strength_modifier(void) const {
    return 0;
}

int Hunter::get_agility_modifier(void) const {
    return 3;
}

int Hunter::get_stamina_modifier(void) const {
    return 1;
}

int Hunter::get_intellect_modifier(void) const {
    return 0;
}

int Hunter::get_spirit_modifier(void) const {
    return 1;
}

int Hunter::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Hunter::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Hunter::get_ap_per_strength() const {
    return 1;
}

int Hunter::get_ap_per_agi() const {
    return 1;
}

float Hunter::global_cooldown() const {
    return 1.5;
}

void Hunter::initialize_talents() {

}

int Hunter::get_highest_possible_armor_type() const {
    return ArmorTypes::MAIL;
}

QVector<int> Hunter::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::SWORD, WeaponTypes::POLEARM, WeaponTypes::STAFF,
                             WeaponTypes::TWOHAND_AXE, WeaponTypes::TWOHAND_SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN});
    default:
        assert(false);
        return QVector<int>();
    }
}
