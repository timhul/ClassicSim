#include "Equipment.h"

#include <cassert>
#include <QSet>

#include "Character.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "Item.h"
#include "Stats.h"
#include "Weapon.h"

Equipment::Equipment(EquipmentDb *equipment_db, Character* pchar):
    db(equipment_db),
    pchar(pchar)
{
    setup_index = 0;

    stats_from_equipped_gear = {nullptr, nullptr, nullptr};
    for (auto & i : stats_from_equipped_gear) {
        i = new Stats();
    }

    item_setups = {QVector<int>(), QVector<int>(), QVector<int>()};
    for (int i = 0; i < item_setups.size(); ++i) {
        item_setups[i] = {
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM,
            NO_EQUIPPED_ITEM
        };
    }
    assert(stats_from_equipped_gear.size() == item_setups.size());

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
}

Equipment::~Equipment() {
    unequip_all();

    for (auto & i : stats_from_equipped_gear) {
        delete i;
    }
}

void Equipment::change_setup(const int index) {
    if (index < 0 || index >= stats_from_equipped_gear.size())
        return;

    QVector<int> preserved_setup = item_setups[setup_index];
    unequip_all();
    item_setups[setup_index] = preserved_setup;

    setup_index = index;

    reequip_items();
}

void Equipment::unequip_all() {
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
}

int Equipment::get_stored_item_id_for_slot(const int equipment_slot) const {
    return item_setups[setup_index][equipment_slot];
}

bool Equipment::is_dual_wielding() {
    return offhand != nullptr;
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

Item* Equipment::get_ranged() const {
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

void Equipment::set_mainhand(const int item_id) {
    Weapon* weapon = db->get_melee_weapon(item_id);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::MAINHAND,
                                       WeaponSlots::ONEHAND,
                                       WeaponSlots::TWOHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot())) {
        delete weapon;
        return;
    }

    if (weapon->get_weapon_slot() == WeaponSlots::TWOHAND)
        clear_offhand();
    else if (weapon->get_value("unique") == "yes") {
        if (get_offhand() != nullptr && get_offhand()->get_item_id() == weapon->get_item_id()) {
            clear_offhand();
            if (get_mainhand() != nullptr)
                set_offhand(get_mainhand()->get_item_id());
        }
    }

    equip(mainhand, weapon, EquipmentSlot::MAINHAND);
}

void Equipment::set_offhand(const int item_id) {
    Weapon* weapon = db->get_melee_weapon(item_id);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::ONEHAND,
                                       WeaponSlots::OFFHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot())) {
        delete weapon;
        return;
    }

    if (get_mainhand() != nullptr) {
        if (get_mainhand()->get_weapon_slot() == WeaponSlots::TWOHAND)
            clear_mainhand();
        else if (weapon->get_value("unique") == "yes") {
            if (get_mainhand()->get_item_id() == weapon->get_item_id())
                clear_mainhand();
        }
    }

    equip(offhand, weapon, EquipmentSlot::OFFHAND);
}

void Equipment::set_ranged(const int item_id) {
    Item* item = db->get_ranged(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RANGED);
    assert(get_relic() == nullptr);
    equip(ranged, item, EquipmentSlot::RANGED);
}

void Equipment::set_head(const int item_id) {
    Item* item = db->get_head(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::HEAD);
    equip(head, item, EquipmentSlot::HEAD);
}

void Equipment::set_neck(const int item_id) {
    Item* item = db->get_neck(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::NECK);
    equip(neck, item, EquipmentSlot::NECK);
}

void Equipment::set_shoulders(const int item_id) {
    Item* item = db->get_shoulders(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::SHOULDERS);
    equip(shoulders, item, EquipmentSlot::SHOULDERS);
}

void Equipment::set_back(const int item_id) {
    Item* item = db->get_back(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BACK);
    equip(back, item, EquipmentSlot::BACK);
}

void Equipment::set_chest(const int item_id) {
    Item* item = db->get_chest(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CHEST);
    equip(chest, item, EquipmentSlot::CHEST);
}

void Equipment::set_wrist(const int item_id) {
    Item* item = db->get_wrist(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::WRIST);
    equip(wrist, item, EquipmentSlot::WRIST);
}

void Equipment::set_gloves(const int item_id) {
    Item* item = db->get_gloves(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::GLOVES);
    equip(gloves, item, EquipmentSlot::GLOVES);
}

void Equipment::set_belt(const int item_id) {
    Item* item = db->get_belt(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BELT);
    equip(belt, item, EquipmentSlot::BELT);
}

void Equipment::set_legs(const int item_id) {
    Item* item = db->get_legs(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::LEGS);
    equip(legs, item, EquipmentSlot::LEGS);
}

void Equipment::set_boots(const int item_id) {
    Item* item = db->get_boots(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BOOTS);
    equip(boots, item, EquipmentSlot::BOOTS);
}

void Equipment::set_ring1(const int item_id) {
    Item* item = db->get_ring(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (get_ring2() != nullptr && get_ring2()->get_item_id() == item->get_item_id()) {
            clear_ring1();
            if (get_ring1() != nullptr)
                set_ring2(get_ring1()->get_item_id());
        }
    }

    equip(ring1, item, EquipmentSlot::RING1);
}

void Equipment::set_ring2(const int item_id) {
    Item* item = db->get_ring(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (get_ring1() != nullptr && get_ring1()->get_item_id() == item->get_item_id()) {
            clear_ring1();
            if (get_ring2() != nullptr)
                set_ring1(get_ring2()->get_item_id());
        }
    }

    equip(ring2, item, EquipmentSlot::RING2);
}

void Equipment::set_trinket1(const int item_id) {
    Item* item = db->get_trinket(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (get_trinket2() != nullptr && get_trinket2()->get_item_id() == item->get_item_id()) {
            clear_trinket2();
            if (get_trinket1() != nullptr)
                set_trinket2(get_trinket1()->get_item_id());
        }
    }

    equip(trinket1, item, EquipmentSlot::TRINKET1);
}

void Equipment::set_trinket2(const int item_id) {
    Item* item = db->get_trinket(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (get_trinket1() != nullptr && get_trinket1()->get_item_id() == item->get_item_id()) {
            clear_trinket1();
            if (get_trinket2() != nullptr)
                set_trinket1(get_trinket2()->get_item_id());
        }
    }

    equip(trinket2, item, EquipmentSlot::TRINKET2);
}

void Equipment::set_caster_offhand(const int item_id) {
    Item* item = db->get_caster_offhand(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CASTER_OFFHAND);
    equip(caster_offhand, item, EquipmentSlot::RANGED);
}

void Equipment::set_relic(const int item_id) {
    Item* item = db->get_relic(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RELIC);
    equip(relic, item, EquipmentSlot::RANGED);
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

void Equipment::reequip_items() {
    int item_id = get_stored_item_id_for_slot(EquipmentSlot::MAINHAND);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_mainhand();
        set_mainhand(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::OFFHAND);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_offhand();
        set_offhand(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RANGED);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_ranged();
        set_ranged(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::HEAD);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_head();
        set_head(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::NECK);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_neck();
        set_neck(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::SHOULDERS);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_shoulders();
        set_shoulders(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::BACK);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_back();
        set_back(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::CHEST);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_chest();
        set_chest(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::WRIST);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_wrist();
        set_wrist(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::GLOVES);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_gloves();
        set_gloves(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::BELT);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_belt();
        set_belt(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::LEGS);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_legs();
        set_legs(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::BOOTS);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_boots();
        set_boots(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RING1);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_ring1();
        set_ring1(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RING2);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_ring2();
        set_ring2(item_id);
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
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_caster_offhand();
        set_caster_offhand(item_id);
    }

    item_id = get_stored_item_id_for_slot(EquipmentSlot::RANGED);
    if (item_id != NO_EQUIPPED_ITEM) {
        clear_relic();
        set_relic(item_id);
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
}

EquipmentDb* Equipment::get_db() const {
    return this->db;
}

void Equipment::equip(Item*& current, Item* next, const int eq_slot) {
    assert(next != nullptr);

    unequip(current, eq_slot);
    current = next;
    current->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current->get_stats());
    item_setups[setup_index][eq_slot] = current->get_item_id();
}

void Equipment::unequip(Item*& item, const int eq_slot) {
    if (item == nullptr)
        return;

    item->remove_equip_effect();
    stats_from_equipped_gear[setup_index]->remove(item->get_stats());
    item_setups[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    delete item;
    item = nullptr;
}

void Equipment::equip(Weapon*& current, Weapon *next, const int eq_slot) {
    assert(next != nullptr);

    unequip(current, eq_slot);
    current = next;
    current->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current->get_stats());
    item_setups[setup_index][eq_slot] = current->get_item_id();
}

void Equipment::unequip(Weapon*& item, const int eq_slot) {
    if (item == nullptr)
        return;

    item->remove_equip_effect();
    stats_from_equipped_gear[setup_index]->remove(item->get_stats());
    item_setups[setup_index][eq_slot] = NO_EQUIPPED_ITEM;
    delete item;
    item = nullptr;
}
