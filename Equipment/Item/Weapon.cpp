#include "Weapon.h"

#include <utility>

#include "Enchant.h"
#include "EnchantProc.h"
#include "EnchantStatic.h"
#include "InstantPoison.h"
#include "Rogue.h"
#include "Utils/Check.h"

Weapon::Weapon(QString name,
               int item_id,
               Content::Phase phase,
               int type,
               int weapon_slot,
               unsigned min,
               unsigned max,
               double speed,
               EnchantInfo* enchant_info,
               QMap<QString, QString> info,
               QVector<QPair<QString, QString>> stats,
               QVector<QMap<QString, QString>> procs,
               QVector<QMap<QString, QString>> uses,
               QVector<QString> special_equip_effects,
               QSet<int> mutex_item_ids,
               QVector<int> random_affixes) :
    Item(std::move(name),
         item_id,
         phase,
         enchant_info,
         std::move(info),
         std::move(stats),
         std::move(procs),
         std::move(uses),
         QVector<QString> {},
         std::move(special_equip_effects),
         std::move(mutex_item_ids),
         std::move(random_affixes)),
    random(new Random(min, max)),
    weapon_type(type),
    weapon_slot(weapon_slot),
    min_dmg(min),
    max_dmg(max),
    weapon_speed(speed),
    temporary_enchant(nullptr) {}

Weapon::Weapon(const Weapon* weapon) : Item(weapon), temporary_enchant(nullptr) {
    this->random = new Random(weapon->min_dmg, weapon->max_dmg);
    this->weapon_type = weapon->weapon_type;
    this->weapon_slot = weapon->weapon_slot;
    this->min_dmg = weapon->min_dmg;
    this->max_dmg = weapon->max_dmg;
    this->weapon_speed = weapon->weapon_speed;
}

Weapon::~Weapon() {
    delete random;
    clear_temporary_enchant();
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
    check((roll >= min_dmg && roll <= max_dmg), "Weapon damage roll outside range");
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

void Weapon::apply_enchant(EnchantName::Name enchant_name, Character* pchar, const int weapon_slot) {
    if (enchant_name == EnchantName::Name::NoEnchant)
        return;

    delete enchant;

    QSet<int> melee_weapon_slots = {WeaponSlots::ONEHAND, WeaponSlots::MAINHAND, WeaponSlots::OFFHAND, WeaponSlots::TWOHAND};
    if (melee_weapon_slots.contains(weapon_slot)) {
        int enchant_slot = weapon_slot == WeaponSlots::OFFHAND ? EnchantSlot::OFFHAND : EnchantSlot::MAINHAND;
        switch (enchant_name) {
        case EnchantName::Name::Crusader:
        case EnchantName::Name::FieryWeapon:
            enchant = new EnchantProc(enchant_name, pchar, enchant_info, enchant_slot);
            break;
        default:
            enchant = new EnchantStatic(enchant_name, pchar, enchant_info, enchant_slot);
        }
    } else if (weapon_slot == WeaponSlots::RANGED) {
        enchant = new EnchantStatic(enchant_name, pchar, enchant_info, EnchantSlot::RANGED);
    } else {
        check(false, QString("Tried to apply weapon enchant on unsupported slot %1").arg(weapon_slot).toStdString());
    }
}

void Weapon::apply_temporary_enchant(EnchantName::Name enchant_name, Character* pchar, const int enchant_slot) {
    if (enchant_name == EnchantName::Name::NoEnchant)
        return;

    clear_temporary_enchant();

    QSet<int> melee_enchant_slots = {EnchantSlot::MAINHAND, EnchantSlot::OFFHAND};
    if (!melee_enchant_slots.contains(enchant_slot))
        check(false, QString("Tried to apply temporary weapon enchant on unsupported slot %1").arg(enchant_slot).toStdString());

    switch (enchant_name) {
    case EnchantName::Name::ShadowOil:
    case EnchantName::Name::WindfuryTotem:
        temporary_enchant = new EnchantProc(enchant_name, pchar, enchant_info, enchant_slot);
        break;
    case EnchantName::Name::BrilliantManaOil:
    case EnchantName::Name::BrilliantWizardOil:
    case EnchantName::Name::ConsecratedSharpeningStone:
    case EnchantName::Name::DenseSharpeningStone:
    case EnchantName::Name::ElementalSharpeningStone:
    case EnchantName::Name::LesserManaOil:
    case EnchantName::Name::SolidWeightstone:
    case EnchantName::Name::DenseWeightstone:
        temporary_enchant = new EnchantStatic(enchant_name, pchar, enchant_info, enchant_slot);
        break;
    case EnchantName::Name::InstantPoison:
        temporary_enchant = enchant_slot == EnchantSlot::MAINHAND ? static_cast<Rogue*>(pchar)->get_mh_instant_poison() :
                                                                    static_cast<Rogue*>(pchar)->get_oh_instant_poison();
        static_cast<InstantPoison*>(temporary_enchant)->enable();
        break;
    default:
        check(false, "Weapon::apply_temporary_enchant reached end of switch");
    }
}

void Weapon::clear_temporary_enchant() {
    EnchantName::Name enchant = get_temporary_enchant_enum_value();

    switch (enchant) {
    case EnchantName::Name::InstantPoison:
        static_cast<InstantPoison*>(temporary_enchant)->disable();
        break;
    default:
        delete temporary_enchant;
    }

    temporary_enchant = nullptr;
}

void Weapon::enable_druid_form_enchants(Character* pchar, const EnchantName::Name enchant_name, const EnchantName::Name temp_enchant_name) {
    switch (enchant_name) {
    case EnchantName::Name::Crusader:
    case EnchantName::Name::FieryWeapon:
        static_cast<EnchantProc*>(enchant)->enable_proc();
        break;
    case EnchantName::Name::SuperiorStriking:
        apply_enchant(enchant_name, pchar, EnchantSlot::MAINHAND);
        break;
    default:
        break;
    }

    switch (temp_enchant_name) {
    case EnchantName::Name::ShadowOil:
    case EnchantName::Name::WindfuryTotem:
        static_cast<EnchantProc*>(enchant)->enable_proc();
        break;
    case EnchantName::Name::DenseSharpeningStone:
        temporary_enchant = new EnchantStatic(enchant_name, pchar, enchant_info, EnchantSlot::MAINHAND);
        break;
    default:
        break;
    }
}

void Weapon::disable_druid_form_enchants() {
    switch (get_enchant_enum_value()) {
    case EnchantName::Name::Crusader:
    case EnchantName::Name::FieryWeapon:
        static_cast<EnchantProc*>(enchant)->disable_proc();
        break;
    case EnchantName::Name::SuperiorStriking:
        clear_enchant();
        break;
    default:
        break;
    }

    switch (get_temporary_enchant_enum_value()) {
    case EnchantName::Name::ShadowOil:
    case EnchantName::Name::WindfuryTotem:
        static_cast<EnchantProc*>(enchant)->disable_proc();
        break;
    case EnchantName::Name::DenseSharpeningStone:
        clear_temporary_enchant();
        break;
    default:
        break;
    }
}

void Weapon::clear_windfury() {
    if (temporary_enchant != nullptr && temporary_enchant->get_enum_name() == EnchantName::Name::WindfuryTotem)
        clear_temporary_enchant();
}

QString Weapon::get_temporary_enchant_effect() const {
    return temporary_enchant != nullptr ? temporary_enchant->get_effect() : "";
}

EnchantName::Name Weapon::get_temporary_enchant_enum_value() const {
    return temporary_enchant != nullptr ? temporary_enchant->get_enum_name() : EnchantName::Name::NoEnchant;
}

QString Weapon::get_temporary_enchant_unique_name() const {
    return temporary_enchant != nullptr ? enchant_info->get_unique_name(temporary_enchant->get_enum_name()) : "";
}

Enchant* Weapon::get_temporary_enchant() const {
    return this->temporary_enchant;
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
