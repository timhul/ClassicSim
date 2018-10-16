
#include "Weapon.h"
#include "Enchant.h"
#include "EnchantProc.h"
#include "EnchantStatic.h"

#include <utility>

Weapon::Weapon(QString name, int type, int weapon_slot, unsigned min, unsigned max, double speed,
       QVector<QPair<QString, QString> > stats,
       QMap<QString, QString> info,
       QVector<QMap<QString, QString>> procs):
    Item(std::move(name), stats, std::move(info), std::move(procs)),
    random(new Random(min, max)),
    weapon_type(type),
    weapon_slot(weapon_slot),
    min_dmg(min),
    max_dmg(max),
    weapon_speed(speed),
    temporary_enchant(nullptr)
{}

Weapon::Weapon(const Weapon* weapon):
    Item(weapon),
    temporary_enchant(nullptr)
{
    this->random = new Random(weapon->min_dmg, weapon->max_dmg);
    this->weapon_type = weapon->weapon_type;
    this->weapon_slot = weapon->weapon_slot;
    this->min_dmg = weapon->min_dmg;
    this->max_dmg = weapon->max_dmg;
    this->weapon_speed = weapon->weapon_speed;
}

Weapon::~Weapon() {
    delete random;
    delete temporary_enchant;
}

int Weapon::get_weapon_slot() const {
    return weapon_slot;
}

int Weapon::get_weapon_type() const {
    return weapon_type;
}

unsigned Weapon::get_min_dmg() const {
    return min_dmg;
}

unsigned Weapon::get_max_dmg() const {
    return max_dmg;
}

unsigned Weapon::get_random_dmg() const {
    const unsigned roll = random->get_roll();
    assert(roll >= min_dmg);
    assert(roll <= max_dmg);
    return roll;
}

double Weapon::get_base_weapon_speed() const {
    return weapon_speed;
}

double Weapon::get_wpn_dps() const {
    return (double(min_dmg + max_dmg) / 2) / weapon_speed;
}

bool Weapon::has_temporary_enchant() const {
    return temporary_enchant != nullptr;
}

void Weapon::apply_enchant(EnchantName::Name enchant_name, Character *pchar) {
    delete enchant;

    switch (enchant_name) {
    case EnchantName::Crusader:
    case EnchantName::FieryWeapon:
        enchant = new EnchantProc(enchant_name, pchar, slot);
        break;
    default:
        enchant = new EnchantStatic(enchant_name, pchar);
    }
}

void Weapon::apply_temporary_enchant(EnchantName::Name enchant_name, Character *pchar) {
    delete temporary_enchant;
    switch (enchant_name) {
    case EnchantName::WindfuryTotem:
        temporary_enchant = new EnchantProc(enchant_name, pchar, slot);
        break;
    default:
        assert(false);
    }
}

void Weapon::clear_temporary_enchant() {
    delete temporary_enchant;
    temporary_enchant = nullptr;
}

QString Weapon::get_temporary_enchant_name() const {
    return temporary_enchant != nullptr ? temporary_enchant->get_name() : "";
}

QString Weapon::get_temporary_enchant_effect() const {
    return temporary_enchant != nullptr ? temporary_enchant->get_effect() : "";
}

bool Weapon::is_2hand() const {
    return weapon_slot == WeaponSlots::TWOHAND;
}

QString Weapon::get_weapon_type_string() const {
    switch (weapon_type) {
    case WeaponTypes::AXE:
        return "Axe";
    case WeaponTypes::TWOHAND_AXE:
        return "2h Axe";
    case WeaponTypes::DAGGER:
        return "Dagger";
    case WeaponTypes::FIST:
        return "Fist";
    case WeaponTypes::MACE:
        return "Mace";
    case WeaponTypes::TWOHAND_MACE:
        return "2h Mace";
    case WeaponTypes::POLEARM:
        return "Polearm";
    case WeaponTypes::STAFF:
        return "Staff";
    case WeaponTypes::SWORD:
        return "Sword";
    case WeaponTypes::TWOHAND_SWORD:
        return "2h Sword";
    case WeaponTypes::BOW:
        return "Bow";
    case WeaponTypes::CROSSBOW:
        return "Crossbow";
    case WeaponTypes::GUN:
        return "Gun";
    case WeaponTypes::THROWN:
        return "Thrown";
    case WeaponTypes::WAND:
        return "Wand";
    case WeaponTypes::IDOL:
        return "Idol";
    case WeaponTypes::LIBRAM:
        return "Libram";
    case WeaponTypes::TOTEM:
        return "Totem";
    case WeaponTypes::SHIELD:
        return "Shield";
    case WeaponTypes::CASTER_OFFHAND:
        return "Offhand";
    default:
        return "Unknown";
    }
}
