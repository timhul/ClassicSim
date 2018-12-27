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

    mainhand = {nullptr, nullptr, nullptr};
    offhand = {nullptr, nullptr, nullptr};
    ranged = {nullptr, nullptr, nullptr};
    head = {nullptr, nullptr, nullptr};
    neck = {nullptr, nullptr, nullptr};
    shoulders = {nullptr, nullptr, nullptr};
    back = {nullptr, nullptr, nullptr};
    chest = {nullptr, nullptr, nullptr};
    wrist = {nullptr, nullptr, nullptr};
    gloves = {nullptr, nullptr, nullptr};
    belt = {nullptr, nullptr, nullptr};
    legs = {nullptr, nullptr, nullptr};
    boots = {nullptr, nullptr, nullptr};
    ring1 = {nullptr, nullptr, nullptr};
    ring2 = {nullptr, nullptr, nullptr};
    trinket1 = {nullptr, nullptr, nullptr};
    trinket2 = {nullptr, nullptr, nullptr};
    caster_offhand = {nullptr, nullptr, nullptr};
    relic = {nullptr, nullptr, nullptr};
}

Equipment::~Equipment() {
    remove_proc_effects_from_current_setup();

    for (auto & i : stats_from_equipped_gear) {
        delete i;
    }

    for (auto & item : mainhand)
        delete item;

    for (auto & item : offhand)
        delete item;

    for (auto & item : ranged)
        delete item;

    for (auto & item : head)
        delete item;

    for (auto & item : neck)
        delete item;

    for (auto & item : shoulders)
        delete item;

    for (auto & item : back)
        delete item;

    for (auto & item : chest)
        delete item;

    for (auto & item : wrist)
        delete item;

    for (auto & item : gloves)
        delete item;

    for (auto & item : belt)
        delete item;

    for (auto & item : legs)
        delete item;

    for (auto & item : boots)
        delete item;

    for (auto & item : ring1)
        delete item;

    for (auto & item : ring2)
        delete item;

    for (auto & item : trinket1)
        delete item;

    for (auto & item : trinket2)
        delete item;

    for (auto & item : caster_offhand)
        delete item;

    for (auto & item : relic)
        delete item;
}

void Equipment::change_setup(const int index) {
    if (index < 0 || index >= stats_from_equipped_gear.size())
        return;

    remove_proc_effects_from_current_setup();

    setup_index = index;

    add_proc_effects_from_current_setup();
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

void Equipment::add_proc_effects_from_current_setup() {
    add_proc_effect_from_item(get_mainhand(), EquipmentSlot::MAINHAND);
    add_proc_effect_from_item(get_offhand(), EquipmentSlot::OFFHAND);
    add_proc_effect_from_item(get_ranged(), EquipmentSlot::RANGED);
    add_proc_effect_from_item(get_head(), EquipmentSlot::HEAD);
    add_proc_effect_from_item(get_neck(), EquipmentSlot::NECK);
    add_proc_effect_from_item(get_shoulders(), EquipmentSlot::SHOULDERS);
    add_proc_effect_from_item(get_back(), EquipmentSlot::BACK);
    add_proc_effect_from_item(get_chest(), EquipmentSlot::CHEST);
    add_proc_effect_from_item(get_wrist(), EquipmentSlot::WRIST);
    add_proc_effect_from_item(get_gloves(), EquipmentSlot::GLOVES);
    add_proc_effect_from_item(get_belt(), EquipmentSlot::BELT);
    add_proc_effect_from_item(get_legs(), EquipmentSlot::LEGS);
    add_proc_effect_from_item(get_boots(), EquipmentSlot::BOOTS);
    add_proc_effect_from_item(get_ring1(), EquipmentSlot::RING1);
    add_proc_effect_from_item(get_ring2(), EquipmentSlot::RING2);
    add_proc_effect_from_item(get_trinket1(), EquipmentSlot::TRINKET1);
    add_proc_effect_from_item(get_trinket2(), EquipmentSlot::TRINKET2);
}

void Equipment::remove_proc_effects_from_current_setup() {
    remove_proc_effect_from_item(get_mainhand());
    remove_proc_effect_from_item(get_offhand());
    remove_proc_effect_from_item(get_ranged());
    remove_proc_effect_from_item(get_head());
    remove_proc_effect_from_item(get_neck());
    remove_proc_effect_from_item(get_shoulders());
    remove_proc_effect_from_item(get_back());
    remove_proc_effect_from_item(get_chest());
    remove_proc_effect_from_item(get_wrist());
    remove_proc_effect_from_item(get_gloves());
    remove_proc_effect_from_item(get_belt());
    remove_proc_effect_from_item(get_legs());
    remove_proc_effect_from_item(get_boots());
    remove_proc_effect_from_item(get_ring1());
    remove_proc_effect_from_item(get_ring2());
    remove_proc_effect_from_item(get_trinket1());
    remove_proc_effect_from_item(get_trinket2());
}

void Equipment::add_proc_effect_from_item(Item* item, const int eq_slot) {
    if (item != nullptr)
        item->apply_equip_effect(pchar, eq_slot);
}

void Equipment::remove_proc_effect_from_item(Item* item) {
    if (item != nullptr)
        item->remove_equip_effect();
}

bool Equipment::is_dual_wielding() {
    return offhand[setup_index] != nullptr;
}

const Stats* Equipment::get_stats() const {
    return this->stats_from_equipped_gear[setup_index];
}

Weapon* Equipment::get_mainhand() const {
    return mainhand[setup_index];
}

Weapon* Equipment::get_offhand() const {
    return offhand[setup_index];
}

Item* Equipment::get_ranged() const {
    return ranged[setup_index];
}

Item* Equipment::get_head() const {
    return head[setup_index];
}

Item* Equipment::get_neck() const {
    return neck[setup_index];
}

Item* Equipment::get_shoulders() const {
    return shoulders[setup_index];
}

Item* Equipment::get_back() const {
    return back[setup_index];
}

Item* Equipment::get_chest() const {
    return chest[setup_index];
}

Item* Equipment::get_wrist() const {
    return wrist[setup_index];
}

Item* Equipment::get_gloves() const {
    return gloves[setup_index];
}

Item* Equipment::get_belt() const {
    return belt[setup_index];
}

Item* Equipment::get_legs() const {
    return legs[setup_index];
}

Item* Equipment::get_boots() const {
    return boots[setup_index];
}

Item* Equipment::get_ring1() const {
    return ring1[setup_index];
}

Item* Equipment::get_ring2() const {
    return ring2[setup_index];
}

Item* Equipment::get_trinket1() const {
    return trinket1[setup_index];
}

Item* Equipment::get_trinket2() const {
    return trinket2[setup_index];
}

Item* Equipment::get_caster_offhand() const {
    return caster_offhand[setup_index];
}

Item* Equipment::get_relic() const {
    return relic[setup_index];
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
        unequip(offhand);
    else if (weapon->get_value("unique") == "yes") {
        if (get_offhand() != nullptr && get_offhand()->get_item_id() == weapon->get_item_id()) {
            unequip(offhand);
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
            unequip(mainhand);
        else if (weapon->get_value("unique") == "yes") {
            if (get_mainhand()->get_item_id() == weapon->get_item_id())
                unequip(mainhand);
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
            unequip(ring2);
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
            unequip(ring1);
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
            unequip(trinket2);
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
            unequip(trinket1);
            if (get_trinket2() != nullptr)
                set_trinket1(get_trinket2()->get_item_id());
        }
    }

    equip(trinket2, item, EquipmentSlot::TRINKET2);
}

void Equipment::set_caster_offhand(const int item_id) {
    // CSIM-74: Get caster offhand.
    Item* item = db->get_ranged(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    equip(caster_offhand, item, EquipmentSlot::RANGED);
}

void Equipment::set_relic(const int item_id) {
    Item* item = db->get_ranged(item_id);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RELIC);
    assert(get_ranged() == nullptr);
    equip(relic, item, EquipmentSlot::RANGED);
}

void Equipment::clear_mainhand() {
    unequip(mainhand);
}

void Equipment::clear_offhand() {
    unequip(offhand);
}

void Equipment::clear_ranged() {
    unequip(ranged);
}

void Equipment::clear_head() {
    unequip(head);
}

void Equipment::clear_neck() {
    unequip(neck);
}

void Equipment::clear_shoulders() {
    unequip(shoulders);
}

void Equipment::clear_back() {
    unequip(back);
}

void Equipment::clear_chest() {
    unequip(chest);
}

void Equipment::clear_wrist() {
    unequip(wrist);
}

void Equipment::clear_gloves() {
    unequip(gloves);
}

void Equipment::clear_belt() {
    unequip(belt);
}

void Equipment::clear_legs() {
    unequip(legs);
}

void Equipment::clear_boots() {
    unequip(boots);
}

void Equipment::clear_ring1() {
    unequip(ring1);
}

void Equipment::clear_ring2() {
    unequip(ring2);
}

void Equipment::clear_trinket1() {
    unequip(trinket1);
}

void Equipment::clear_trinket2() {
    unequip(trinket2);
}

void Equipment::clear_caster_offhand() {
    unequip(caster_offhand);
}

void Equipment::clear_relic() {
    unequip(relic);
}

void Equipment::reequip_items() {
    if (get_mainhand()) {
        int item_id = get_mainhand()->get_item_id();
        clear_mainhand();
        set_mainhand(item_id);
    }

    if (get_offhand()) {
        int item_id = get_offhand()->get_item_id();
        clear_offhand();
        set_offhand(item_id);
    }

    if (get_ranged()) {
        int item_id = get_ranged()->get_item_id();
        clear_ranged();
        set_ranged(item_id);
    }

    if (get_head()) {
        int item_id = get_head()->get_item_id();
        clear_head();
        set_head(item_id);
    }

    if (get_neck()) {
        int item_id = get_neck()->get_item_id();
        clear_neck();
        set_neck(item_id);
    }

    if (get_shoulders()) {
        int item_id = get_shoulders()->get_item_id();
        clear_shoulders();
        set_shoulders(item_id);
    }

    if (get_back()) {
        int item_id = get_back()->get_item_id();
        clear_back();
        set_back(item_id);
    }

    if (get_chest()) {
        int item_id = get_chest()->get_item_id();
        clear_chest();
        set_chest(item_id);
    }

    if (get_wrist()) {
        int item_id = get_wrist()->get_item_id();
        clear_wrist();
        set_wrist(item_id);
    }

    if (get_gloves()) {
        int item_id = get_gloves()->get_item_id();
        clear_gloves();
        set_gloves(item_id);
    }

    if (get_belt()) {
        int item_id = get_belt()->get_item_id();
        clear_belt();
        set_belt(item_id);
    }

    if (get_legs()) {
        int item_id = get_legs()->get_item_id();
        clear_legs();
        set_legs(item_id);
    }

    if (get_boots()) {
        int item_id = get_boots()->get_item_id();
        clear_boots();
        set_boots(item_id);
    }

    if (get_ring1()) {
        int item_id = get_ring1()->get_item_id();
        clear_ring1();
        set_ring1(item_id);
    }

    if (get_ring2()) {
        int item_id = get_ring2()->get_item_id();
        clear_ring2();
        set_ring2(item_id);
    }

    if (get_trinket1()) {
        int item_id = get_trinket1()->get_item_id();
        clear_trinket1();
        set_trinket1(item_id);
    }

    if (get_trinket2()) {
        int item_id = get_trinket2()->get_item_id();
        clear_trinket2();
        set_trinket2(item_id);
    }

    if (get_caster_offhand()) {
        int item_id = get_caster_offhand()->get_item_id();
        clear_caster_offhand();
        set_caster_offhand(item_id);
    }

    if (get_relic()) {
        int item_id = get_relic()->get_item_id();
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

void Equipment::equip(QVector<Item*>& current, Item*& next, const int eq_slot) {
    assert(next != nullptr);

    unequip(current);
    current[setup_index] = next;
    current[setup_index]->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current[setup_index]->get_stats());
}

void Equipment::unequip(QVector<Item*>& item) {
    if (item[setup_index] == nullptr)
        return;

    item[setup_index]->remove_equip_effect();
    stats_from_equipped_gear[setup_index]->remove(item[setup_index]->get_stats());
    delete item[setup_index];
    item[setup_index] = nullptr;
}

void Equipment::equip(QVector<Weapon*>& current, Weapon*& next, const int eq_slot) {
    assert(next != nullptr);

    unequip(current);
    current[setup_index] = next;
    current[setup_index]->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current[setup_index]->get_stats());
}

void Equipment::unequip(QVector<Weapon*>& item) {
    if (item[setup_index] == nullptr)
        return;

    item[setup_index]->remove_equip_effect();
    stats_from_equipped_gear[setup_index]->remove(item[setup_index]->get_stats());
    delete item[setup_index];
    item[setup_index] = nullptr;
}
