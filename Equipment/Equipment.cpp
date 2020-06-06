#include "Equipment.h"

#include <QSet>

#include "RandomAffix.h"
#include "Character.h"
#include "CharacterEnchants.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "Hunter.h"
#include "Item.h"
#include "Projectile.h"
#include "Quiver.h"
#include "RandomAffixes.h"
#include "SetBonusControl.h"
#include "Stats.h"
#include "Utils/Check.h"
#include "Weapon.h"

Equipment::Equipment(EquipmentDb* equipment_db, Character* pchar) :
    pchar(pchar),
    db(equipment_db),
    random_affixes(new RandomAffixes()),
    set_bonuses(new SetBonusControl(equipment_db, pchar)),
    stats_from_equipped_gear({nullptr, nullptr, nullptr}) {
    setup_index = 0;

    for (auto& i : stats_from_equipped_gear) {
        i = new Stats();
    }

    item_setups = {{}, {}, {}};
    for (auto& setup : item_setups) {
        setup = {
            NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM,
        };
    }
    check((stats_from_equipped_gear.size() == item_setups.size()), "Different size vectors");

    item_affixes = {{}, {}, {}};
    for (auto& setup : item_affixes) {
        setup = {
            NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM, NO_EQUIPPED_ITEM,
        };
    }
    check((stats_from_equipped_gear.size() == item_affixes.size()), "Different size vectors");

    item_enchants = {{}, {}, {}};
    for (auto& setup : item_enchants) {
        setup = {
            EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant,
            EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant,
            EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant,
            EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant, EnchantName::NoEnchant,
        };
    }
    check((stats_from_equipped_gear.size() == item_enchants.size()), "Different size vectors");

    item_temp_enchants = {{}, {}, {}};
    for (auto& setup : item_temp_enchants) {
        setup = {
            EnchantName::NoEnchant,
            EnchantName::NoEnchant,
            EnchantName::NoEnchant,
        };
    }

    mainhand = nullptr;
    offhand = nullptr;
    ranged = nullptr;
    head = nullptr;
    neck = nullptr;
    shoulders = nullptr;
    back = nullptr;
    chest = nullptr;
    wrist = nullptr;
    gloves = nullptr;
    belt = nullptr;
    legs = nullptr;
    boots = nullptr;
    ring1 = nullptr;
    ring2 = nullptr;
    trinket1 = nullptr;
    trinket2 = nullptr;
    caster_offhand = nullptr;
    relic = nullptr;
    projectile = nullptr;
    quiver = nullptr;
}

Equipment::~Equipment() {
    unequip_all();

    for (const auto& i : stats_from_equipped_gear) {
        delete i;
    }

    delete set_bonuses;
}

void Equipment::change_setup(const int index) {
    if (index < 0 || index >= stats_from_equipped_gear.size())
        return;

    QVector<int> preserved_setup = item_setups[setup_index];
    QVector<int> preserved_affixes = item_affixes[setup_index];
    store_current_enchants();
    unequip_all();
    item_setups[setup_index] = preserved_setup;
    item_affixes[setup_index] = preserved_affixes;

    setup_index = index;

    reequip_items();
    apply_current_enchants();
}

void Equipment::unequip_all() {
    if (druid_form_mh_storage)
        druid_switch_to_normal_weapon();

    clear_mainhand();
    clear_offhand();
    clear_ranged();
    clear_head();
    clear_neck();
    clear_shoulders();
    clear_back();
    clear_chest();
    clear_wrist();
    clear_gloves();
    clear_belt();
    clear_legs();
    clear_boots();
    clear_ring1();
    clear_ring2();
    clear_trinket1();
    clear_trinket2();
    clear_caster_offhand();
    clear_relic();
    clear_projectile();
    clear_quiver();
}

int Equipment::get_stored_item_id_for_slot(const int equipment_slot) const {
    return item_setups[setup_index][equipment_slot];
}

int Equipment::get_stored_random_affix_id_for_slot(const int equipment_slot) const {
    return item_affixes[setup_index][equipment_slot];
}

void Equipment::apply_current_enchants() {
    if (get_mainhand())
        get_mainhand()->apply_enchant(item_enchants[setup_index][EquipmentSlot::MAINHAND], pchar, WeaponSlots::MAINHAND);
    if (get_mainhand())
        get_mainhand()->apply_temporary_enchant(item_temp_enchants[setup_index][EquipmentSlot::MAINHAND], pchar, EnchantSlot::MAINHAND);
    if (get_offhand())
        get_offhand()->apply_enchant(item_enchants[setup_index][EquipmentSlot::OFFHAND], pchar, WeaponSlots::OFFHAND);
    if (get_offhand())
        get_offhand()->apply_temporary_enchant(item_temp_enchants[setup_index][EquipmentSlot::OFFHAND], pchar, EnchantSlot::OFFHAND);
    if (get_ranged())
        get_ranged()->apply_enchant(item_enchants[setup_index][EquipmentSlot::RANGED], pchar, WeaponSlots::RANGED);
    if (get_head())
        get_head()->apply_enchant(item_enchants[setup_index][EquipmentSlot::HEAD], pchar);
    if (get_shoulders())
        get_shoulders()->apply_enchant(item_enchants[setup_index][EquipmentSlot::SHOULDERS], pchar);
    if (get_back())
        get_back()->apply_enchant(item_enchants[setup_index][EquipmentSlot::BACK], pchar);
    if (get_chest())
        get_chest()->apply_enchant(item_enchants[setup_index][EquipmentSlot::CHEST], pchar);
    if (get_wrist())
        get_wrist()->apply_enchant(item_enchants[setup_index][EquipmentSlot::WRIST], pchar);
    if (get_gloves())
        get_gloves()->apply_enchant(item_enchants[setup_index][EquipmentSlot::GLOVES], pchar);
    if (get_legs())
        get_legs()->apply_enchant(item_enchants[setup_index][EquipmentSlot::LEGS], pchar);
    if (get_boots())
        get_boots()->apply_enchant(item_enchants[setup_index][EquipmentSlot::BOOTS], pchar);
}

void Equipment::store_current_enchants() {
    item_enchants[setup_index][EquipmentSlot::MAINHAND] = get_current_enchant_enum_value(get_mainhand());
    item_enchants[setup_index][EquipmentSlot::OFFHAND] = get_current_enchant_enum_value(get_offhand());
    item_enchants[setup_index][EquipmentSlot::RANGED] = get_current_enchant_enum_value(get_ranged());
    item_enchants[setup_index][EquipmentSlot::HEAD] = get_current_enchant_enum_value(get_head());
    item_enchants[setup_index][EquipmentSlot::NECK] = get_current_enchant_enum_value(get_neck());
    item_enchants[setup_index][EquipmentSlot::SHOULDERS] = get_current_enchant_enum_value(get_shoulders());
    item_enchants[setup_index][EquipmentSlot::BACK] = get_current_enchant_enum_value(get_back());
    item_enchants[setup_index][EquipmentSlot::CHEST] = get_current_enchant_enum_value(get_chest());
    item_enchants[setup_index][EquipmentSlot::WRIST] = get_current_enchant_enum_value(get_wrist());
    item_enchants[setup_index][EquipmentSlot::GLOVES] = get_current_enchant_enum_value(get_gloves());
    item_enchants[setup_index][EquipmentSlot::BELT] = get_current_enchant_enum_value(get_belt());
    item_enchants[setup_index][EquipmentSlot::LEGS] = get_current_enchant_enum_value(get_legs());
    item_enchants[setup_index][EquipmentSlot::BOOTS] = get_current_enchant_enum_value(get_boots());

    item_temp_enchants[setup_index][EquipmentSlot::MAINHAND] = get_current_temp_enchant_enum_value(get_mainhand());
    item_temp_enchants[setup_index][EquipmentSlot::OFFHAND] = get_current_temp_enchant_enum_value(get_offhand());
    item_temp_enchants[setup_index][EquipmentSlot::RANGED] = get_current_temp_enchant_enum_value(get_ranged());
}

EnchantName::Name Equipment::get_current_enchant_enum_value(Item* item) const {
    return item ? item->get_enchant_enum_value() : EnchantName::NoEnchant;
}

EnchantName::Name Equipment::get_current_temp_enchant_enum_value(Weapon* weapon) const {
    return weapon ? weapon->get_temporary_enchant_enum_value() : EnchantName::NoEnchant;
}

bool Equipment::is_dual_wielding() {
    if (offhand == nullptr)
        return false;

    switch (offhand->get_weapon_type()) {
    case WeaponTypes::CASTER_OFFHAND:
    case WeaponTypes::SHIELD:
        return false;
    default:
        return true;
    }
}

const Stats* Equipment::get_stats() const {
    return this->stats_from_equipped_gear[setup_index];
}

Weapon* Equipment::get_mainhand() const {
    return mainhand;
}

Weapon* Equipment::get_offhand() const {
    return offhand;
}

Weapon* Equipment::get_ranged() const {
    return ranged;
}

Item* Equipment::get_head() const {
    return head;
}

Item* Equipment::get_neck() const {
    return neck;
}

Item* Equipment::get_shoulders() const {
    return shoulders;
}

Item* Equipment::get_back() const {
    return back;
}

Item* Equipment::get_chest() const {
    return chest;
}

Item* Equipment::get_wrist() const {
    return wrist;
}

Item* Equipment::get_gloves() const {
    return gloves;
}

Item* Equipment::get_belt() const {
    return belt;
}

Item* Equipment::get_legs() const {
    return legs;
}

Item* Equipment::get_boots() const {
    return boots;
}

Item* Equipment::get_ring1() const {
    return ring1;
}

Item* Equipment::get_ring2() const {
    return ring2;
}

Item* Equipment::get_trinket1() const {
    return trinket1;
}

Item* Equipment::get_trinket2() const {
    return trinket2;
}

Item* Equipment::get_caster_offhand() const {
    return caster_offhand;
}

Item* Equipment::get_relic() const {
    return relic;
}

Projectile* Equipment::get_projectile() const {
    return projectile;
}

Quiver* Equipment::get_quiver() const {
    return quiver;
}

void Equipment::set_mainhand(const int item_id, RandomAffix* random_affix) {
    Weapon* weapon = db->get_melee_weapon(item_id);

    if (weapon == nullptr)
        return;

    if (random_affix)
        weapon->set_random_affix(random_affix);

    QSet<int> accepted_weapon_slots = {WeaponSlots::MAINHAND, WeaponSlots::ONEHAND, WeaponSlots::TWOHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot())) {
        delete weapon;
        return;
    }

    if (weapon->get_weapon_slot() == WeaponSlots::TWOHAND)
        clear_offhand();
    else if (weapon->get_value("unique") == "yes") {
        if (get_offhand() != nullptr && get_offhand()->item_id == weapon->item_id) {
            clear_offhand();
            if (get_mainhand() != nullptr)
                set_offhand(get_mainhand()->item_id);
        }
    }

    equip(mainhand, weapon, EquipmentSlot::MAINHAND);
}

void Equipment::set_offhand(const int item_id, RandomAffix* random_affix) {
    Weapon* weapon = db->get_melee_weapon(item_id);

    if (weapon == nullptr)
        return;

    if (random_affix)
        weapon->set_random_affix(random_affix);

    QSet<int> accepted_weapon_slots = {WeaponSlots::ONEHAND, WeaponSlots::OFFHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot())) {
        delete weapon;
        return;
    }

    if (get_mainhand() != nullptr) {
        if (get_mainhand()->get_weapon_slot() == WeaponSlots::TWOHAND)
            clear_mainhand();
        else if (weapon->get_value("unique") == "yes") {
            if (get_mainhand()->item_id == weapon->item_id)
                clear_mainhand();
        }
    }

    equip(offhand, weapon, EquipmentSlot::OFFHAND);
}

void Equipment::set_ranged(const int item_id, RandomAffix* random_affix) {
    Weapon* weapon = db->get_ranged(item_id);

    if (weapon == nullptr)
        return;

    if (random_affix)
        weapon->set_random_affix(random_affix);

    if (projectile && !projectile->valid_for_weapon(weapon))
        clear_projectile();

    if (quiver && !quiver->valid_for_weapon(weapon))
        clear_quiver();

    check((weapon->get_item_slot() == ItemSlots::RANGED), QString("'%1' has incorrect slot").arg(weapon->name).toStdString());
    check((get_relic() == nullptr), "Relic is equipped while equipping a ranged weapon");
    equip(ranged, weapon, EquipmentSlot::RANGED);
}

void Equipment::set_head(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_head(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::HEAD), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(head, item, EquipmentSlot::HEAD);
}

void Equipment::set_neck(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_neck(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::NECK), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(neck, item, EquipmentSlot::NECK);
}

void Equipment::set_shoulders(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_shoulders(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::SHOULDERS), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(shoulders, item, EquipmentSlot::SHOULDERS);
}

void Equipment::set_back(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_back(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::BACK), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(back, item, EquipmentSlot::BACK);
}

void Equipment::set_chest(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_chest(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::CHEST), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(chest, item, EquipmentSlot::CHEST);
}

void Equipment::set_wrist(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_wrist(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::WRIST), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(wrist, item, EquipmentSlot::WRIST);
}

void Equipment::set_gloves(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_gloves(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::GLOVES), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(gloves, item, EquipmentSlot::GLOVES);
}

void Equipment::set_belt(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_belt(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::BELT), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(belt, item, EquipmentSlot::BELT);
}

void Equipment::set_legs(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_legs(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::LEGS), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(legs, item, EquipmentSlot::LEGS);
}

void Equipment::set_boots(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_boots(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::BOOTS), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(boots, item, EquipmentSlot::BOOTS);
}

void Equipment::set_ring1(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_ring(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::RING), QString("'%1' has incorrect slot").arg(item->name).toStdString());

    if (item->get_value("unique") == "yes") {
        if (get_ring2() != nullptr && get_ring2()->item_id == item->item_id) {
            clear_ring2();
            if (get_ring1() != nullptr)
                set_ring2(get_ring1()->item_id);
        }
    }

    equip(ring1, item, EquipmentSlot::RING1);
}

void Equipment::set_ring2(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_ring(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::RING), QString("'%1' has incorrect slot").arg(item->name).toStdString());

    if (item->get_value("unique") == "yes") {
        if (get_ring1() != nullptr && get_ring1()->item_id == item->item_id) {
            clear_ring1();
            if (get_ring2() != nullptr)
                set_ring1(get_ring2()->item_id);
        }
    }

    equip(ring2, item, EquipmentSlot::RING2);
}

void Equipment::set_trinket1(const int item_id) {
    Item* item = db->get_trinket(item_id);

    if (item == nullptr)
        return;

    check((item->get_item_slot() == ItemSlots::TRINKET), QString("'%1' has incorrect slot").arg(item->name).toStdString());

    if (item->get_value("unique") == "yes") {
        if (get_trinket2() != nullptr && get_trinket2()->item_id == item->item_id) {
            clear_trinket2();
            if (get_trinket1() != nullptr)
                set_trinket2(get_trinket1()->item_id);
        }
    }

    equip(trinket1, item, EquipmentSlot::TRINKET1);
}

void Equipment::set_trinket2(const int item_id) {
    Item* item = db->get_trinket(item_id);

    if (item == nullptr)
        return;

    check((item->get_item_slot() == ItemSlots::TRINKET), QString("'%1' has incorrect slot").arg(item->name).toStdString());

    if (item->get_value("unique") == "yes") {
        if (get_trinket1() != nullptr && get_trinket1()->item_id == item->item_id) {
            clear_trinket1();
            if (get_trinket2() != nullptr)
                set_trinket1(get_trinket2()->item_id);
        }
    }

    equip(trinket2, item, EquipmentSlot::TRINKET2);
}

void Equipment::set_caster_offhand(const int item_id, RandomAffix* random_affix) {
    Item* item = db->get_caster_offhand(item_id);

    if (item == nullptr)
        return;

    if (random_affix)
        item->set_random_affix(random_affix);

    check((item->get_item_slot() == ItemSlots::CASTER_OFFHAND), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(caster_offhand, item, EquipmentSlot::RANGED);
}

void Equipment::set_relic(const int item_id) {
    Item* item = db->get_relic(item_id);

    if (item == nullptr)
        return;

    check((item->get_item_slot() == ItemSlots::RELIC), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(relic, item, EquipmentSlot::RANGED);
}

void Equipment::set_projectile(const int item_id) {
    Projectile* item = db->get_projectile(item_id);

    if (item == nullptr)
        return;

    if (ranged && !item->valid_for_weapon(ranged))
        clear_ranged();

    if (quiver && !item->valid_for_quiver(quiver))
        clear_quiver();

    check((item->get_item_slot() == ItemSlots::PROJECTILE), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(projectile, item, EquipmentSlot::PROJECTILE);
}

void Equipment::set_quiver(const int item_id) {
    Quiver* item = db->get_quiver(item_id);

    if (item == nullptr)
        return;

    if (ranged && !item->valid_for_weapon(ranged))
        clear_ranged();

    if (projectile && !item->valid_for_projectile(projectile))
        clear_projectile();

    check((item->get_item_slot() == ItemSlots::QUIVER), QString("'%1' has incorrect slot").arg(item->name).toStdString());
    equip(quiver, item, EquipmentSlot::QUIVER);
}

void Equipment::clear_mainhand() {
    unequip(mainhand, EquipmentSlot::MAINHAND);
}

void Equipment::clear_offhand() {
    unequip(offhand, EquipmentSlot::OFFHAND);
}

void Equipment::clear_ranged() {
    unequip(ranged, EquipmentSlot::RANGED);
}

void Equipment::clear_head() {
    unequip(head, EquipmentSlot::HEAD);
}

void Equipment::clear_neck() {
    unequip(neck, EquipmentSlot::NECK);
}

void Equipment::clear_shoulders() {
    unequip(shoulders, EquipmentSlot::SHOULDERS);
}

void Equipment::clear_back() {
    unequip(back, EquipmentSlot::BACK);
}

void Equipment::clear_chest() {
    unequip(chest, EquipmentSlot::CHEST);
}

void Equipment::clear_wrist() {
    unequip(wrist, EquipmentSlot::WRIST);
}

void Equipment::clear_gloves() {
    unequip(gloves, EquipmentSlot::GLOVES);
}

void Equipment::clear_belt() {
    unequip(belt, EquipmentSlot::BELT);
}

void Equipment::clear_legs() {
    unequip(legs, EquipmentSlot::LEGS);
}

void Equipment::clear_boots() {
    unequip(boots, EquipmentSlot::BOOTS);
}

void Equipment::clear_ring1() {
    unequip(ring1, EquipmentSlot::RING1);
}

void Equipment::clear_ring2() {
    unequip(ring2, EquipmentSlot::RING2);
}

void Equipment::clear_trinket1() {
    unequip(trinket1, EquipmentSlot::TRINKET1);
}

void Equipment::clear_trinket2() {
    unequip(trinket2, EquipmentSlot::TRINKET2);
}

void Equipment::clear_caster_offhand() {
    unequip(caster_offhand, EquipmentSlot::OFFHAND);
}

void Equipment::clear_relic() {
    unequip(relic, EquipmentSlot::RANGED);
}

void Equipment::clear_projectile() {
    unequip(projectile, EquipmentSlot::PROJECTILE);
}

void Equipment::clear_quiver() {
    unequip(quiver, EquipmentSlot::QUIVER);
}

void Equipment::reequip_items() {
    int item_id = get_stored_item_id_for_slot(EquipmentSlot::MAINHAND);
    int random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::MAINHAND);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_mainhand();
        set_mainhand(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::OFFHAND);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::OFFHAND);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_offhand();
        set_offhand(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RANGED);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::RANGED);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_ranged();
        set_ranged(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::HEAD);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::HEAD);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_head();
        set_head(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::NECK);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::NECK);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_neck();
        set_neck(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::SHOULDERS);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::SHOULDERS);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_shoulders();
        set_shoulders(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::BACK);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::BACK);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_back();
        set_back(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::CHEST);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::CHEST);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_chest();
        set_chest(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::WRIST);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::WRIST);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_wrist();
        set_wrist(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::GLOVES);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::GLOVES);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_gloves();
        set_gloves(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::BELT);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::BELT);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_belt();
        set_belt(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::LEGS);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::LEGS);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_legs();
        set_legs(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::BOOTS);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::BOOTS);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_boots();
        set_boots(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RING1);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::RING1);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_ring1();
        set_ring1(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RING2);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::RING2);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_ring2();
        set_ring2(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::TRINKET1);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_trinket1();
        set_trinket1(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::TRINKET2);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_trinket2();
        set_trinket2(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RANGED);
    random_affix_id = get_stored_random_affix_id_for_slot(EquipmentSlot::RANGED);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_caster_offhand();
        set_caster_offhand(item_id, random_affixes->get_affix(random_affix_id));
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RANGED);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_relic();
        set_relic(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::PROJECTILE);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_projectile();
        set_projectile(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::QUIVER);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_quiver();
        set_quiver(item_id);
    }
}

void Equipment::clear_items_not_available_for_faction() {
    const AvailableFactions::Name faction = pchar->get_faction()->get_faction_as_enum();

    if (get_mainhand() && !get_mainhand()->available_for_faction(faction))
        clear_mainhand();

    if (get_offhand() && !get_offhand()->available_for_faction(faction))
        clear_offhand();

    if (get_ranged() && !get_ranged()->available_for_faction(faction))
        clear_ranged();

    if (get_head() && !get_head()->available_for_faction(faction))
        clear_head();

    if (get_neck() && !get_neck()->available_for_faction(faction))
        clear_neck();

    if (get_shoulders() && !get_shoulders()->available_for_faction(faction))
        clear_shoulders();

    if (get_back() && !get_back()->available_for_faction(faction))
        clear_back();

    if (get_chest() && !get_chest()->available_for_faction(faction))
        clear_chest();

    if (get_wrist() && !get_wrist()->available_for_faction(faction))
        clear_wrist();

    if (get_gloves() && !get_gloves()->available_for_faction(faction))
        clear_gloves();

    if (get_belt() && !get_belt()->available_for_faction(faction))
        clear_belt();

    if (get_legs() && !get_legs()->available_for_faction(faction))
        clear_legs();

    if (get_boots() && !get_boots()->available_for_faction(faction))
        clear_boots();

    if (get_ring1() && !get_ring1()->available_for_faction(faction))
        clear_ring1();

    if (get_ring2() && !get_ring2()->available_for_faction(faction))
        clear_ring2();

    if (get_trinket1() && !get_trinket1()->available_for_faction(faction))
        clear_trinket1();

    if (get_trinket2() && !get_trinket2()->available_for_faction(faction))
        clear_trinket2();

    if (get_caster_offhand() && !get_caster_offhand()->available_for_faction(faction))
        clear_caster_offhand();

    if (get_relic() && !get_relic()->available_for_faction(faction))
        clear_relic();

    if (get_projectile() && !get_projectile()->available_for_faction(faction))
        clear_projectile();

    if (get_quiver() && !get_quiver()->available_for_faction(faction))
        clear_quiver();
}

SetBonusControl* Equipment::get_set_bonus_control() const {
    return this->set_bonuses;
}

void Equipment::equip(Item*& current, Item* next, const int eq_slot) {
    check((next != nullptr), "next nullptr");

    EnchantName::Name current_enchant = current != nullptr ? current->get_enchant_enum_value() : EnchantName::NoEnchant;

    unequip(current, eq_slot);
    current = next;
    current->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current->get_stats());
    item_setups[setup_index][eq_slot] = current->item_id;
    set_bonuses->equip_item(current->item_id);
    if (current->get_random_affix() != nullptr)
        item_affixes[setup_index][eq_slot] = current->get_random_affix()->id;

    current->apply_enchant(current_enchant, pchar);
}

void Equipment::unequip(Item*& item, const int eq_slot) {
    if (item == nullptr)
        return;

    set_bonuses->unequip_item(item->item_id);
    stats_from_equipped_gear[setup_index]->remove(item->get_stats());
    item_setups[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    item_affixes[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    delete item;
    item = nullptr;
}

void Equipment::equip(Weapon*& current, Weapon* next, const int eq_slot) {
    check((next != nullptr), "next nullptr");

    EnchantName::Name current_enchant = current != nullptr ? current->get_enchant_enum_value() : EnchantName::NoEnchant;
    EnchantName::Name current_temp_enchant = current != nullptr ? current->get_temporary_enchant_enum_value() : EnchantName::NoEnchant;

    unequip(current, eq_slot);

    current = next;
    current->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current->get_stats());
    item_setups[setup_index][eq_slot] = current->item_id;
    set_bonuses->equip_item(current->item_id);
    if (current->get_random_affix() != nullptr)
        item_affixes[setup_index][eq_slot] = current->get_random_affix()->id;

    if (pchar->get_enchants()->enchant_valid(current_enchant, current->get_weapon_slot()))
        current->apply_enchant(current_enchant, pchar, current->get_weapon_slot());

    int enchant_slot = eq_slot == EquipmentSlot::MAINHAND ? EnchantSlot::MAINHAND : EnchantSlot::OFFHAND;
    if (pchar->get_enchants()->temp_enchant_valid(current_temp_enchant, current->get_weapon_slot(), eq_slot))
        current->apply_temporary_enchant(current_temp_enchant, pchar, enchant_slot);
}

void Equipment::unequip(Weapon*& item, const int eq_slot) {
    if (item == nullptr)
        return;

    set_bonuses->unequip_item(item->item_id);
    stats_from_equipped_gear[setup_index]->remove(item->get_stats());
    item_setups[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    item_affixes[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    delete item;
    item = nullptr;
}

void Equipment::equip(Projectile*& current, Projectile* next, const int eq_slot) {
    check((next != nullptr), "next nullptr");

    unequip(current, eq_slot);
    current = next;
    item_setups[setup_index][eq_slot] = current->item_id;
    static_cast<Hunter*>(pchar)->set_projectile_dps(current->get_projectile_dps());
}

void Equipment::unequip(Projectile*& item, const int eq_slot) {
    if (item == nullptr)
        return;

    static_cast<Hunter*>(pchar)->set_projectile_dps(0.0);
    item_setups[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    delete item;
    item = nullptr;
}

void Equipment::equip(Quiver*& current, Quiver* next, const int eq_slot) {
    check((next != nullptr), "next nullptr");

    unequip(current, eq_slot);
    current = next;
    current->apply_equip_effect(pchar, eq_slot);
    pchar->increase_ranged_attack_speed(current->get_stats()->get_ranged_attack_speed_percent());
    stats_from_equipped_gear[setup_index]->add(current->get_stats());
    item_setups[setup_index][eq_slot] = current->item_id;
}

void Equipment::unequip(Quiver*& current, const int eq_slot) {
    if (current == nullptr)
        return;

    pchar->decrease_ranged_attack_speed(current->get_stats()->get_ranged_attack_speed_percent());
    stats_from_equipped_gear[setup_index]->remove(current->get_stats());
    item_setups[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    delete current;
    current = nullptr;
}

void Equipment::druid_bear_form_switch_to_paws() {
    mh_enchant = get_current_enchant_enum_value(mainhand);
    mh_temp_enchant = get_current_temp_enchant_enum_value(mainhand);

    if (mainhand) {
        mainhand->disable_proc_effects();
        mainhand->disable_druid_form_enchants();
    }

    druid_form_mh_storage = mainhand;
    druid_form_oh_storage = offhand;

    mainhand = nullptr;
    offhand = nullptr;

    // Druid paws are created as hidden items with an item id of 11223400 + clvl
    set_mainhand(11223400 + static_cast<int>(pchar->get_clvl()));
}

void Equipment::druid_cat_form_switch_to_claws() {
    mh_enchant = get_current_enchant_enum_value(mainhand);
    mh_temp_enchant = get_current_temp_enchant_enum_value(mainhand);

    if (mainhand) {
        mainhand->disable_proc_effects();
        mainhand->disable_druid_form_enchants();
    }

    druid_form_mh_storage = mainhand;
    druid_form_oh_storage = offhand;

    mainhand = nullptr;
    offhand = nullptr;

    // Druid claws are created as hidden items with an item id of 11223300 + clvl
    set_mainhand(11223300 + static_cast<int>(pchar->get_clvl()));
}

void Equipment::druid_switch_to_normal_weapon() {
    delete mainhand;
    delete offhand;

    mainhand = druid_form_mh_storage;
    offhand = druid_form_oh_storage;

    druid_form_mh_storage = nullptr;
    druid_form_oh_storage = nullptr;

    if (mainhand) {
        mainhand->enable_proc_effects();
        mainhand->enable_druid_form_enchants(pchar, mh_enchant, mh_temp_enchant);
    }
}

void Equipment::clear_item_id_if_equipped_in_any_slot(const int item_id) {
    if (get_mainhand() && get_mainhand()->item_id == item_id)
        clear_mainhand();

    if (get_offhand() && get_offhand()->item_id == item_id)
        clear_offhand();

    if (get_ranged() && get_ranged()->item_id == item_id)
        clear_ranged();

    if (get_head() && get_head()->item_id == item_id)
        clear_head();

    if (get_neck() && get_neck()->item_id == item_id)
        clear_neck();

    if (get_shoulders() && get_shoulders()->item_id == item_id)
        clear_shoulders();

    if (get_back() && get_back()->item_id == item_id)
        clear_back();

    if (get_chest() && get_chest()->item_id == item_id)
        clear_chest();

    if (get_wrist() && get_wrist()->item_id == item_id)
        clear_wrist();

    if (get_gloves() && get_gloves()->item_id == item_id)
        clear_gloves();

    if (get_belt() && get_belt()->item_id == item_id)
        clear_belt();

    if (get_legs() && get_legs()->item_id == item_id)
        clear_legs();

    if (get_boots() && get_boots()->item_id == item_id)
        clear_boots();

    if (get_ring1() && get_ring1()->item_id == item_id)
        clear_ring1();

    if (get_ring2() && get_ring2()->item_id == item_id)
        clear_ring2();

    if (get_trinket1() && get_trinket1()->item_id == item_id)
        clear_trinket1();

    if (get_trinket2() && get_trinket2()->item_id == item_id)
        clear_trinket2();

    if (get_caster_offhand() && get_caster_offhand()->item_id == item_id)
        clear_caster_offhand();

    if (get_relic() && get_relic()->item_id == item_id)
        clear_relic();

    if (get_projectile() && get_projectile()->item_id == item_id)
        clear_projectile();

    if (get_quiver() && get_quiver()->item_id == item_id)
        clear_quiver();
}
