
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Item.h"
#include "Weapon.h"
#include "Stats.h"
#include <cassert>
#include <QSet>

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
    clean_item_proc_state();

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

    clean_item_proc_state();

    setup_index = index;

    add_proc_effects_from_current_setup();
    clear_items_not_available_on_patch();
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

void Equipment::clean_item_proc_state() {
    remove_proc_effect_from_item(get_mainhand(), EquipmentSlot::MAINHAND);
    remove_proc_effect_from_item(get_offhand(), EquipmentSlot::OFFHAND);
    remove_proc_effect_from_item(get_ranged(), EquipmentSlot::RANGED);
    remove_proc_effect_from_item(get_head(), EquipmentSlot::HEAD);
    remove_proc_effect_from_item(get_neck(), EquipmentSlot::NECK);
    remove_proc_effect_from_item(get_shoulders(), EquipmentSlot::SHOULDERS);
    remove_proc_effect_from_item(get_back(), EquipmentSlot::BACK);
    remove_proc_effect_from_item(get_chest(), EquipmentSlot::CHEST);
    remove_proc_effect_from_item(get_wrist(), EquipmentSlot::WRIST);
    remove_proc_effect_from_item(get_gloves(), EquipmentSlot::GLOVES);
    remove_proc_effect_from_item(get_belt(), EquipmentSlot::BELT);
    remove_proc_effect_from_item(get_legs(), EquipmentSlot::LEGS);
    remove_proc_effect_from_item(get_boots(), EquipmentSlot::BOOTS);
    remove_proc_effect_from_item(get_ring1(), EquipmentSlot::RING1);
    remove_proc_effect_from_item(get_ring2(), EquipmentSlot::RING2);
    remove_proc_effect_from_item(get_trinket1(), EquipmentSlot::TRINKET1);
    remove_proc_effect_from_item(get_trinket2(), EquipmentSlot::TRINKET2);
}

void Equipment::add_proc_effect_from_item(Item* item, const int eq_slot) {
    if (item != nullptr)
        item->apply_equip_effect(pchar, eq_slot);
}

void Equipment::remove_proc_effect_from_item(Item* item, const int eq_slot) {
    if (item != nullptr)
        item->remove_equip_effect(eq_slot);
}

bool Equipment::is_dual_wielding() {
    return offhand[setup_index] != nullptr;
}

const Stats* Equipment::get_stats() const {
    return this->stats_from_equipped_gear[setup_index];
}

Weapon* Equipment::get_mainhand() {
    return mainhand[setup_index];
}

Weapon* Equipment::get_offhand() {
    return offhand[setup_index];
}

Item* Equipment::get_ranged() {
    return ranged[setup_index];
}

Item* Equipment::get_head() {
    return head[setup_index];
}

Item* Equipment::get_neck() {
    return neck[setup_index];
}

Item* Equipment::get_shoulders() {
    return shoulders[setup_index];
}

Item* Equipment::get_back() {
    return back[setup_index];
}

Item* Equipment::get_chest() {
    return chest[setup_index];
}

Item* Equipment::get_wrist() {
    return wrist[setup_index];
}

Item* Equipment::get_gloves() {
    return gloves[setup_index];
}

Item* Equipment::get_belt() {
    return belt[setup_index];
}

Item* Equipment::get_legs() {
    return legs[setup_index];
}

Item* Equipment::get_boots() {
    return boots[setup_index];
}

Item* Equipment::get_ring1() {
    return ring1[setup_index];
}

Item* Equipment::get_ring2() {
    return ring2[setup_index];
}

Item* Equipment::get_trinket1() {
    return trinket1[setup_index];
}

Item* Equipment::get_trinket2() {
    return trinket2[setup_index];
}

Item* Equipment::get_caster_offhand() {
    return caster_offhand[setup_index];
}

Item* Equipment::get_relic() {
    return relic[setup_index];
}

void Equipment::set_mainhand(const QString &name) {
    Weapon* weapon = db->get_melee_weapon(name);

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
        unequip(offhand, EquipmentSlot::OFFHAND);
    else if (weapon->get_value("unique") == "yes") {
        if (get_offhand() != nullptr && get_offhand()->get_name() == weapon->get_name()) {
            unequip(offhand, EquipmentSlot::OFFHAND);
            if (get_mainhand() != nullptr)
                set_offhand(get_mainhand()->get_name());
        }
    }

    equip(mainhand, weapon, EquipmentSlot::MAINHAND);
}

void Equipment::set_offhand(const QString &name) {
    Weapon* weapon = db->get_melee_weapon(name);

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
            unequip(mainhand, EquipmentSlot::MAINHAND);
        else if (weapon->get_value("unique") == "yes") {
            if (get_mainhand()->get_name() == weapon->get_name())
                unequip(mainhand, EquipmentSlot::MAINHAND);
        }
    }

    equip(offhand, weapon, EquipmentSlot::OFFHAND);
}

void Equipment::set_ranged(const QString &name) {
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RANGED);
    assert(get_relic() == nullptr);
    equip(ranged, item, EquipmentSlot::RANGED);
}

void Equipment::set_head(const QString &name) {
    Item* item = db->get_head(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::HEAD);
    equip(head, item, EquipmentSlot::HEAD);
}

void Equipment::set_neck(const QString &name) {
    Item* item = db->get_neck(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::NECK);
    equip(neck, item, EquipmentSlot::NECK);
}

void Equipment::set_shoulders(const QString &name) {
    Item* item = db->get_shoulders(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::SHOULDERS);
    equip(shoulders, item, EquipmentSlot::SHOULDERS);
}

void Equipment::set_back(const QString &name) {
    Item* item = db->get_back(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BACK);
    equip(back, item, EquipmentSlot::BACK);
}

void Equipment::set_chest(const QString &name) {
    Item* item = db->get_chest(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CHEST);
    equip(chest, item, EquipmentSlot::CHEST);
}

void Equipment::set_wrist(const QString &name) {
    Item* item = db->get_wrist(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::WRIST);
    equip(wrist, item, EquipmentSlot::WRIST);
}

void Equipment::set_gloves(const QString &name) {
    Item* item = db->get_gloves(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::GLOVES);
    equip(gloves, item, EquipmentSlot::GLOVES);
}

void Equipment::set_belt(const QString &name) {
    Item* item = db->get_belt(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BELT);
    equip(belt, item, EquipmentSlot::BELT);
}

void Equipment::set_legs(const QString &name) {
    Item* item = db->get_legs(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::LEGS);
    equip(legs, item, EquipmentSlot::LEGS);
}

void Equipment::set_boots(const QString &name) {
    Item* item = db->get_boots(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BOOTS);
    equip(boots, item, EquipmentSlot::BOOTS);
}

void Equipment::set_ring1(const QString &name) {
    Item* item = db->get_ring(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (get_ring2() != nullptr && get_ring2()->get_name() == item->get_name()) {
            unequip(ring2, EquipmentSlot::RING2);
            if (get_ring1() != nullptr)
                set_ring2(get_ring1()->get_name());
        }
    }

    equip(ring1, item, EquipmentSlot::RING1);
}

void Equipment::set_ring2(const QString &name) {
    Item* item = db->get_ring(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (get_ring1() != nullptr && get_ring1()->get_name() == item->get_name()) {
            unequip(ring1, EquipmentSlot::RING1);
            if (get_ring2() != nullptr)
                set_ring1(get_ring2()->get_name());
        }
    }

    equip(ring2, item, EquipmentSlot::RING2);
}

void Equipment::set_trinket1(const QString &name) {
    Item* item = db->get_trinket(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (get_trinket2() != nullptr && get_trinket2()->get_name() == item->get_name()) {
            unequip(trinket2, EquipmentSlot::TRINKET2);
            if (get_trinket1() != nullptr)
                set_trinket2(get_trinket1()->get_name());
        }
    }

    equip(trinket1, item, EquipmentSlot::TRINKET1);
}

void Equipment::set_trinket2(const QString &name) {
    Item* item = db->get_trinket(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (get_trinket1() != nullptr && get_trinket1()->get_name() == item->get_name()) {
            unequip(trinket1, EquipmentSlot::TRINKET1);
            if (get_trinket2() != nullptr)
                set_trinket1(get_trinket2()->get_name());
        }
    }

    equip(trinket2, item, EquipmentSlot::TRINKET2);
}

void Equipment::set_caster_offhand(const QString &name) {
    // CSIM-74: Get caster offhand.
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    equip(caster_offhand, item, EquipmentSlot::RANGED);
}

void Equipment::set_relic(const QString &name) {
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RELIC);
    assert(get_ranged() == nullptr);
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

void Equipment::clear_items_not_available_on_patch() {
    if (get_mainhand()) {
        if (!db->item_valid_for_current_patch(get_mainhand()->get_value("patch")))
            clear_mainhand();
    }

    if (get_offhand()) {
        if (!db->item_valid_for_current_patch(get_offhand()->get_value("patch")))
            clear_offhand();
    }

    if (get_ranged()) {
        if (!db->item_valid_for_current_patch(get_ranged()->get_value("patch")))
            clear_ranged();
    }

    if (get_head()) {
        if (!db->item_valid_for_current_patch(get_head()->get_value("patch")))
            clear_head();
    }

    if (get_neck()) {
        if (!db->item_valid_for_current_patch(get_neck()->get_value("patch")))
            clear_neck();
    }

    if (get_shoulders()) {
        if (!db->item_valid_for_current_patch(get_shoulders()->get_value("patch")))
            clear_shoulders();
    }

    if (get_back()) {
        if (!db->item_valid_for_current_patch(get_back()->get_value("patch")))
            clear_back();
    }

    if (get_chest()) {
        if (!db->item_valid_for_current_patch(get_chest()->get_value("patch")))
            clear_chest();
    }

    if (get_wrist()) {
        if (!db->item_valid_for_current_patch(get_wrist()->get_value("patch")))
            clear_wrist();
    }

    if (get_gloves()) {
        if (!db->item_valid_for_current_patch(get_gloves()->get_value("patch")))
            clear_gloves();
    }

    if (get_belt()) {
        if (!db->item_valid_for_current_patch(get_belt()->get_value("patch")))
            clear_belt();
    }

    if (get_legs()) {
        if (!db->item_valid_for_current_patch(get_legs()->get_value("patch")))
            clear_legs();
    }

    if (get_boots()) {
        if (!db->item_valid_for_current_patch(get_boots()->get_value("patch")))
            clear_boots();
    }

    if (get_ring1()) {
        if (!db->item_valid_for_current_patch(get_ring1()->get_value("patch")))
            clear_ring1();
    }

    if (get_ring2()) {
        if (!db->item_valid_for_current_patch(get_ring2()->get_value("patch")))
            clear_ring2();
    }

    if (get_trinket1()) {
        if (!db->item_valid_for_current_patch(get_trinket1()->get_value("patch")))
            clear_trinket1();
    }

    if (get_trinket2()) {
        if (!db->item_valid_for_current_patch(get_trinket2()->get_value("patch")))
            clear_trinket2();
    }

    if (get_caster_offhand()) {
        if (!db->item_valid_for_current_patch(get_caster_offhand()->get_value("patch")))
            clear_caster_offhand();
    }

    if (get_relic()) {
        if (!db->item_valid_for_current_patch(get_relic()->get_value("patch")))
            clear_relic();
    }
}

EquipmentDb* Equipment::get_db() const {
    return this->db;
}

void Equipment::equip(QVector<Item*>& current, Item*& next, const int eq_slot) {
    assert(next != nullptr);

    unequip(current, eq_slot);
    current[setup_index] = next;
    current[setup_index]->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current[setup_index]->get_stats());
}

void Equipment::unequip(QVector<Item*>& item, const int eq_slot) {
    if (item[setup_index] == nullptr)
        return;

    item[setup_index]->remove_equip_effect(eq_slot);
    stats_from_equipped_gear[setup_index]->remove(item[setup_index]->get_stats());
    delete item[setup_index];
    item[setup_index] = nullptr;
}

void Equipment::equip(QVector<Weapon*>& current, Weapon*& next, const int eq_slot) {
    assert(next != nullptr);

    unequip(current, eq_slot);
    current[setup_index] = next;
    current[setup_index]->apply_equip_effect(pchar, eq_slot);
    stats_from_equipped_gear[setup_index]->add(current[setup_index]->get_stats());
}

void Equipment::unequip(QVector<Weapon*>& item, const int eq_slot) {
    if (item[setup_index] == nullptr)
        return;

    item[setup_index]->remove_equip_effect(eq_slot);
    stats_from_equipped_gear[setup_index]->remove(item[setup_index]->get_stats());
    delete item[setup_index];
    item[setup_index] = nullptr;
}
