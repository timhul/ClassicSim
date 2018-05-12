
#include "Equipment.h"
#include "EquipmentDb.h"
#include <QSet>
#include <assert.h>
#include "Stats.h"

Equipment::Equipment() {
    setup_index = 0;
    db = new EquipmentDb();

    stats_from_equipped_gear = {nullptr, nullptr, nullptr};
    for (int i = 0; i < stats_from_equipped_gear.size(); ++i) {
        stats_from_equipped_gear[i] = new Stats();
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
    delete db;
    for (int i = 0; i < stats_from_equipped_gear.size(); ++i) {
        delete stats_from_equipped_gear[i];
    }
}

void Equipment::change_setup(const int index) {
    if (index < 0 || index >= stats_from_equipped_gear.size())
        return;

    setup_index = index;
    clear_items_not_available_on_patch();
}

bool Equipment::is_dual_wielding(void) {
    return offhand[setup_index] != nullptr;
}

const Stats* Equipment::get_stats() const {
    return this->stats_from_equipped_gear[setup_index];
}

Weapon* Equipment::get_mainhand(void) {
    return mainhand[setup_index];
}

Weapon* Equipment::get_offhand(void) {
    return offhand[setup_index];
}

Item* Equipment::get_ranged(void) {
    return ranged[setup_index];
}

Item* Equipment::get_head(void) {
    return head[setup_index];
}

Item* Equipment::get_neck(void) {
    return neck[setup_index];
}

Item* Equipment::get_shoulders(void) {
    return shoulders[setup_index];
}

Item* Equipment::get_back(void) {
    return back[setup_index];
}

Item* Equipment::get_chest(void) {
    return chest[setup_index];
}

Item* Equipment::get_wrist(void) {
    return wrist[setup_index];
}

Item* Equipment::get_gloves(void) {
    return gloves[setup_index];
}

Item* Equipment::get_belt(void) {
    return belt[setup_index];
}

Item* Equipment::get_legs(void) {
    return legs[setup_index];
}

Item* Equipment::get_boots(void) {
    return boots[setup_index];
}

Item* Equipment::get_ring1(void) {
    return ring1[setup_index];
}

Item* Equipment::get_ring2(void) {
    return ring2[setup_index];
}

Item* Equipment::get_trinket1(void) {
    return trinket1[setup_index];
}

Item* Equipment::get_trinket2(void) {
    return trinket2[setup_index];
}

Item* Equipment::get_caster_offhand(void) {
    return caster_offhand[setup_index];
}

Item* Equipment::get_relic(void) {
    return relic[setup_index];
}

void Equipment::set_mainhand(const QString &name) {
    Weapon* weapon = db->get_melee_weapon(name);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::MAINHAND,
                                       WeaponSlots::ONEHAND,
                                       WeaponSlots::TWOHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot()))
        return;

    if (weapon->get_weapon_slot() == WeaponSlots::TWOHAND)
        unequip(offhand);
    else if (weapon->get_value("unique") == "yes") {
        if (get_offhand() != nullptr && get_offhand()->get_name() == weapon->get_name()) {
            unequip(offhand);
            if (get_mainhand() != nullptr)
                set_offhand(get_mainhand()->get_name());
        }
    }

    equip(mainhand, weapon);
}

void Equipment::set_offhand(const QString &name) {
    Weapon* weapon = db->get_melee_weapon(name);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::ONEHAND,
                                       WeaponSlots::OFFHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot()))
        return;

    if (get_mainhand() != nullptr) {
        if (get_mainhand()->get_weapon_slot() == WeaponSlots::TWOHAND)
            unequip(mainhand);
        else if (weapon->get_value("unique") == "yes") {
            if (get_mainhand()->get_name() == weapon->get_name())
                unequip(mainhand);
        }
    }

    equip(offhand, weapon);
}

void Equipment::set_ranged(const QString &name) {
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RANGED);
    assert(get_relic() == nullptr);
    equip(ranged, item);
}

void Equipment::set_head(const QString &name) {
    Item* item = db->get_head(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::HEAD);
    equip(head, item);
}

void Equipment::set_neck(const QString &name) {
    Item* item = db->get_neck(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::NECK);
    equip(neck, item);
}

void Equipment::set_shoulders(const QString &name) {
    Item* item = db->get_shoulders(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::SHOULDERS);
    equip(shoulders, item);
}

void Equipment::set_back(const QString &name) {
    Item* item = db->get_back(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BACK);
    equip(back, item);
}

void Equipment::set_chest(const QString &name) {
    Item* item = db->get_chest(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CHEST);
    equip(chest, item);
}

void Equipment::set_wrist(const QString &name) {
    Item* item = db->get_wrist(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::WRIST);
    equip(wrist, item);
}

void Equipment::set_gloves(const QString &name) {
    Item* item = db->get_gloves(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::GLOVES);
    equip(gloves, item);
}

void Equipment::set_belt(const QString &name) {
    Item* item = db->get_belt(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BELT);
    equip(belt, item);
}

void Equipment::set_legs(const QString &name) {
    Item* item = db->get_legs(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::LEGS);
    equip(legs, item);
}

void Equipment::set_boots(const QString &name) {
    Item* item = db->get_boots(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BOOTS);
    equip(boots, item);
}

void Equipment::set_ring1(const QString &name) {
    Item* item = db->get_ring(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (get_ring2() != nullptr && get_ring2()->get_name() == item->get_name()) {
            unequip(ring2);
            if (get_ring1() != nullptr)
                set_ring2(get_ring1()->get_name());
        }
    }

    equip(ring1, item);
}

void Equipment::set_ring2(const QString &name) {
    Item* item = db->get_ring(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (get_ring1() != nullptr && get_ring1()->get_name() == item->get_name()) {
            unequip(ring1);
            if (get_ring2() != nullptr)
                set_ring1(get_ring2()->get_name());
        }
    }

    equip(ring2, item);
}

void Equipment::set_trinket1(const QString &name) {
    Item* item = db->get_trinket(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (get_trinket2() != nullptr && get_trinket2()->get_name() == item->get_name()) {
            unequip(trinket2);
            if (get_trinket1() != nullptr)
                set_trinket2(get_trinket1()->get_name());
        }
    }

    equip(trinket1, item);
}

void Equipment::set_trinket2(const QString &name) {
    Item* item = db->get_trinket(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (get_trinket1() != nullptr && get_trinket1()->get_name() == item->get_name()) {
            unequip(trinket1);
            if (get_trinket2() != nullptr)
                set_trinket1(get_trinket2()->get_name());
        }
    }

    equip(trinket2, item);
}

void Equipment::set_caster_offhand(const QString &name) {
    // TODO: Get caster offhand.
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    equip(caster_offhand, item);
}

void Equipment::set_relic(const QString &name) {
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RELIC);
    assert(get_ranged() == nullptr);
    equip(relic, item);
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

void Equipment::clear_items_not_available_on_patch() {
    if (get_mainhand()) {
        if (!db->item_valid_for_current_patch(get_mainhand()->get_value("patch")))
            unequip(mainhand);
    }

    if (get_offhand()) {
        if (!db->item_valid_for_current_patch(get_offhand()->get_value("patch")))
            unequip(offhand);
    }

    if (get_ranged()) {
        if (!db->item_valid_for_current_patch(get_ranged()->get_value("patch")))
            unequip(ranged);
    }

    if (get_head()) {
        if (!db->item_valid_for_current_patch(get_head()->get_value("patch")))
            unequip(head);
    }

    if (get_neck()) {
        if (!db->item_valid_for_current_patch(get_neck()->get_value("patch")))
            unequip(neck);
    }

    if (get_shoulders()) {
        if (!db->item_valid_for_current_patch(get_shoulders()->get_value("patch")))
            unequip(shoulders);
    }

    if (get_back()) {
        if (!db->item_valid_for_current_patch(get_back()->get_value("patch")))
            unequip(back);
    }

    if (get_chest()) {
        if (!db->item_valid_for_current_patch(get_chest()->get_value("patch")))
            unequip(chest);
    }

    if (get_wrist()) {
        if (!db->item_valid_for_current_patch(get_wrist()->get_value("patch")))
            unequip(wrist);
    }

    if (get_gloves()) {
        if (!db->item_valid_for_current_patch(get_gloves()->get_value("patch")))
            unequip(gloves);
    }

    if (get_belt()) {
        if (!db->item_valid_for_current_patch(get_belt()->get_value("patch")))
            unequip(belt);
    }

    if (get_legs()) {
        if (!db->item_valid_for_current_patch(get_legs()->get_value("patch")))
            unequip(legs);
    }

    if (get_boots()) {
        if (!db->item_valid_for_current_patch(get_boots()->get_value("patch")))
            unequip(boots);
    }

    if (get_ring1()) {
        if (!db->item_valid_for_current_patch(get_ring1()->get_value("patch")))
            unequip(ring1);
    }

    if (get_ring2()) {
        if (!db->item_valid_for_current_patch(get_ring2()->get_value("patch")))
            unequip(ring2);
    }

    if (get_trinket1()) {
        if (!db->item_valid_for_current_patch(get_trinket1()->get_value("patch")))
            unequip(trinket1);
    }

    if (get_trinket2()) {
        if (!db->item_valid_for_current_patch(get_trinket2()->get_value("patch")))
            unequip(trinket2);
    }

    if (get_caster_offhand()) {
        if (!db->item_valid_for_current_patch(get_caster_offhand()->get_value("patch")))
            unequip(caster_offhand);
    }

    if (get_relic()) {
        if (!db->item_valid_for_current_patch(get_relic()->get_value("patch")))
            unequip(relic);
    }
}

EquipmentDb* Equipment::get_db() const {
    return this->db;
}

void Equipment::equip(QVector<Item*>& current, Item*& next) {
    assert(next != nullptr);

    unequip(current);
    current[setup_index] = next;
    stats_from_equipped_gear[setup_index]->add(current[setup_index]->get_stats());
}

void Equipment::unequip(QVector<Item*>& item) {
    if (item[setup_index] == nullptr)
        return;

    stats_from_equipped_gear[setup_index]->remove(item[setup_index]->get_stats());
    item[setup_index] = nullptr;
}

void Equipment::equip(QVector<Weapon*>& current, Weapon*& next) {
    assert(next != nullptr);

    unequip(current);
    current[setup_index] = next;
    stats_from_equipped_gear[setup_index]->add(current[setup_index]->get_stats());
}

void Equipment::unequip(QVector<Weapon*>& item) {
    if (item[setup_index] == nullptr)
        return;

    stats_from_equipped_gear[setup_index]->remove(item[setup_index]->get_stats());
    item[setup_index] = nullptr;
}
