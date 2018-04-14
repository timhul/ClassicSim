
#include "Equipment.h"
#include "EquipmentDb.h"
#include <QSet>
#include <assert.h>

Equipment::Equipment() {
    db = new EquipmentDb();
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
    delete db;
}

bool Equipment::is_dual_wielding(void) {
    return offhand != nullptr;
}

Weapon* Equipment::get_mainhand(void) {
    return mainhand;
}

Weapon* Equipment::get_offhand(void) {
    return offhand;
}

Item* Equipment::get_ranged(void) {
    return ranged;
}

Item* Equipment::get_head(void) {
    return head;
}

Item* Equipment::get_neck(void) {
    return neck;
}

Item* Equipment::get_shoulders(void) {
    return shoulders;
}

Item* Equipment::get_back(void) {
    return back;
}

Item* Equipment::get_chest(void) {
    return chest;
}

Item* Equipment::get_wrist(void) {
    return wrist;
}

Item* Equipment::get_gloves(void) {
    return gloves;
}

Item* Equipment::get_belt(void) {
    return belt;
}

Item* Equipment::get_legs(void) {
    return legs;
}

Item* Equipment::get_boots(void) {
    return boots;
}

Item* Equipment::get_ring1(void) {
    return ring1;
}

Item* Equipment::get_ring2(void) {
    return ring2;
}

Item* Equipment::get_trinket1(void) {
    return trinket1;
}

Item* Equipment::get_trinket2(void) {
    return trinket2;
}

Item* Equipment::get_caster_offhand(void) {
    return caster_offhand;
}

Item* Equipment::get_relic(void) {
    return relic;
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

    if (weapon->get_value("unique") == "yes") {
        if (offhand != nullptr && offhand->get_name() == weapon->get_name()) {
            offhand = nullptr;
            if (mainhand != nullptr)
                set_offhand(mainhand->get_name());
        }
    }

    this->mainhand = weapon;

    if (weapon->get_weapon_slot() == WeaponSlots::TWOHAND)
        this->offhand = nullptr;
}

void Equipment::set_offhand(const QString &name) {
    Weapon* weapon = db->get_melee_weapon(name);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::ONEHAND,
                                       WeaponSlots::OFFHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot()))
        return;

    if (weapon->get_value("unique") == "yes") {
        if (mainhand != nullptr && mainhand->get_name() == weapon->get_name())
            mainhand = nullptr;
    }

    if (mainhand != nullptr && mainhand->get_weapon_slot() == WeaponSlots::TWOHAND)
        mainhand = nullptr;

    this->offhand = weapon;
}

void Equipment::set_ranged(const QString &name) {
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RANGED);
    assert(get_relic() == nullptr);
    this->ranged = item;
}

void Equipment::set_head(const QString &name) {
    Item* item = db->get_head(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::HEAD);
    this->head = item;
}

void Equipment::set_neck(const QString &name) {
    Item* item = db->get_neck(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::NECK);
    this->neck = item;
}

void Equipment::set_shoulders(const QString &name) {
    Item* item = db->get_shoulders(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::SHOULDERS);
    this->shoulders = item;
}

void Equipment::set_back(const QString &name) {
    Item* item = db->get_back(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BACK);
    this->back = item;
}

void Equipment::set_chest(const QString &name) {
    Item* item = db->get_chest(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CHEST);
    this->chest = item;
}

void Equipment::set_wrist(const QString &name) {
    Item* item = db->get_wrist(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::WRIST);
    this->wrist = item;
}

void Equipment::set_gloves(const QString &name) {
    Item* item = db->get_gloves(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::GLOVES);
    this->gloves = item;
}

void Equipment::set_belt(const QString &name) {
    Item* item = db->get_belt(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BELT);
    this->belt = item;
}

void Equipment::set_legs(const QString &name) {
    Item* item = db->get_legs(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::LEGS);
    this->legs = item;
}

void Equipment::set_boots(const QString &name) {
    Item* item = db->get_boots(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::BOOTS);
    this->boots = item;
}

void Equipment::set_ring1(const QString &name) {
    Item* item = db->get_ring(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (ring2 != nullptr && ring2->get_name() == item->get_name()) {
            ring2 = nullptr;
            if (ring1 != nullptr)
                set_ring2(ring1->get_name());
        }
    }

    this->ring1 = item;
}

void Equipment::set_ring2(const QString &name) {
    Item* item = db->get_ring(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RING);

    if (item->get_value("unique") == "yes") {
        if (ring1 != nullptr && ring1->get_name() == item->get_name()) {
            ring1 = nullptr;
            if (ring2 != nullptr)
                set_ring1(ring2->get_name());
        }
    }

    this->ring2 = item;
}

void Equipment::set_trinket1(const QString &name) {
    Item* item = db->get_trinket(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (trinket2 != nullptr && trinket2->get_name() == item->get_name()) {
            trinket2 = nullptr;
            if (trinket1 != nullptr)
                set_trinket2(trinket1->get_name());
        }
    }

    this->trinket1 = item;
}

void Equipment::set_trinket2(const QString &name) {
    Item* item = db->get_trinket(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::TRINKET);

    if (item->get_value("unique") == "yes") {
        if (trinket1 != nullptr && trinket1->get_name() == item->get_name()) {
            trinket1 = nullptr;
            if (trinket2 != nullptr)
                set_trinket1(trinket2->get_name());
        }
    }

    this->trinket2 = item;
}

void Equipment::set_caster_offhand(const QString &name) {
    // TODO: Get caster offhand.
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    this->caster_offhand = item;
}

void Equipment::set_relic(const QString &name) {
    Item* item = db->get_ranged(name);

    if (item == nullptr)
        return;

    assert(item->get_item_slot() == ItemSlots::RELIC);
    assert(get_ranged() == nullptr);
    this->relic = item;
}

void Equipment::clear_mainhand() {
    this->mainhand = nullptr;
}

void Equipment::clear_offhand() {
    this->offhand = nullptr;
}

void Equipment::clear_ranged() {
    this->ranged = nullptr;
}

void Equipment::clear_head() {
    this->head = nullptr;
}

void Equipment::clear_neck() {
    this->neck = nullptr;
}

void Equipment::clear_shoulders() {
    this->shoulders = nullptr;
}

void Equipment::clear_back() {
    this->back = nullptr;
}

void Equipment::clear_chest() {
    this->chest = nullptr;
}

void Equipment::clear_wrist() {
    this->wrist = nullptr;
}

void Equipment::clear_gloves() {
    this->gloves = nullptr;
}

void Equipment::clear_belt() {
    this->belt = nullptr;
}

void Equipment::clear_legs() {
    this->legs = nullptr;
}

void Equipment::clear_boots() {
    this->boots = nullptr;
}

void Equipment::clear_ring1() {
    this->ring1 = nullptr;
}

void Equipment::clear_ring2() {
    this->ring2 = nullptr;
}

void Equipment::clear_trinket1() {
    this->trinket1 = nullptr;
}

void Equipment::clear_trinket2() {
    this->trinket2 = nullptr;
}

void Equipment::clear_caster_offhand() {
    this->caster_offhand = nullptr;
}

void Equipment::clear_relic() {
    this->relic = nullptr;
}

void Equipment::patch_changed() {
    if (get_mainhand()) {
        if (db->item_valid_for_current_patch(get_mainhand()->get_value("patch")))
            this->mainhand = nullptr;
    }

    if (get_offhand()) {
        if (db->item_valid_for_current_patch(get_offhand()->get_value("patch")))
            this->offhand = nullptr;
    }

    if (get_ranged()) {
        if (db->item_valid_for_current_patch(get_ranged()->get_value("patch")))
            this->ranged = nullptr;
    }

    if (get_head()) {
        if (db->item_valid_for_current_patch(get_head()->get_value("patch")))
            this->head = nullptr;
    }

    if (get_neck()) {
        if (db->item_valid_for_current_patch(get_neck()->get_value("patch")))
            this->neck = nullptr;
    }

    if (get_shoulders()) {
        if (db->item_valid_for_current_patch(get_shoulders()->get_value("patch")))
            this->shoulders = nullptr;
    }

    if (get_back()) {
        if (db->item_valid_for_current_patch(get_back()->get_value("patch")))
            this->back = nullptr;
    }

    if (get_chest()) {
        if (db->item_valid_for_current_patch(get_chest()->get_value("patch")))
            this->chest = nullptr;
    }

    if (get_wrist()) {
        if (db->item_valid_for_current_patch(get_wrist()->get_value("patch")))
            this->wrist = nullptr;
    }

    if (get_gloves()) {
        if (db->item_valid_for_current_patch(get_gloves()->get_value("patch")))
            this->gloves = nullptr;
    }

    if (get_belt()) {
        if (db->item_valid_for_current_patch(get_belt()->get_value("patch")))
            this->belt = nullptr;
    }

    if (get_legs()) {
        if (db->item_valid_for_current_patch(get_legs()->get_value("patch")))
            this->legs = nullptr;
    }

    if (get_boots()) {
        if (db->item_valid_for_current_patch(get_boots()->get_value("patch")))
            this->boots = nullptr;
    }

    if (get_ring1()) {
        if (db->item_valid_for_current_patch(get_ring1()->get_value("patch")))
            this->ring1 = nullptr;
    }

    if (get_ring2()) {
        if (db->item_valid_for_current_patch(get_ring2()->get_value("patch")))
            this->ring2 = nullptr;
    }

    if (get_trinket1()) {
        if (db->item_valid_for_current_patch(get_trinket1()->get_value("patch")))
            this->trinket1 = nullptr;
    }

    if (get_trinket2()) {
        if (db->item_valid_for_current_patch(get_trinket2()->get_value("patch")))
            this->trinket2 = nullptr;
    }

    if (get_caster_offhand()) {
        if (db->item_valid_for_current_patch(get_caster_offhand()->get_value("patch")))
            this->caster_offhand = nullptr;
    }

    if (get_relic()) {
        if (db->item_valid_for_current_patch(get_relic()->get_value("patch")))
            this->relic = nullptr;
    }
}

EquipmentDb* Equipment::get_db() const {
    return this->db;
}
