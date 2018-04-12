
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

MeleeWeapon* Equipment::get_mainhand(void) {
    return mainhand;
}

MeleeWeapon* Equipment::get_offhand(void) {
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
    MeleeWeapon* weapon = db->get_melee_weapon(name);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::MAINHAND,
                                       WeaponSlots::ONEHAND,
                                       WeaponSlots::TWOHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot()))
        return;

    this->mainhand = weapon;

    if (weapon->get_weapon_slot() == WeaponSlots::TWOHAND)
        this->offhand = nullptr;
}

void Equipment::set_offhand(const QString &name) {
    MeleeWeapon* weapon = db->get_melee_weapon(name);

    if (weapon == nullptr)
        return;

    QSet<int> accepted_weapon_slots = {WeaponSlots::ONEHAND,
                                       WeaponSlots::OFFHAND};

    if (!accepted_weapon_slots.contains(weapon->get_weapon_slot()))
        return;

    this->offhand = weapon;
}

void Equipment::set_ranged(Item* item) {
    assert(item->get_item_type() == ItemSlots::RANGED);
    assert(get_relic() == nullptr);
    if (this->ranged != nullptr)
        delete this->ranged;
    this->ranged = item;
}

void Equipment::set_head(Item* item) {
    assert(item->get_item_type() == ItemSlots::HEAD);
    if (this->head != nullptr)
        delete this->head;
    this->head = item;
}

void Equipment::set_neck(Item* item) {
    assert(item->get_item_type() == ItemSlots::NECK);
    if (this->neck != nullptr)
        delete this->neck;
    this->neck = item;
}

void Equipment::set_shoulders(Item* item) {
    assert(item->get_item_type() == ItemSlots::SHOULDERS);
    if (this->shoulders != nullptr)
        delete this->shoulders;
    this->shoulders = item;
}

void Equipment::set_back(Item* item) {
    assert(item->get_item_type() == ItemSlots::BACK);
    if (this->back != nullptr)
        delete this->back;
    this->back = item;
}

void Equipment::set_chest(Item* item) {
    assert(item->get_item_type() == ItemSlots::CHEST);
    if (this->chest != nullptr)
        delete this->chest;
    this->chest = item;
}

void Equipment::set_wrist(Item* item) {
    assert(item->get_item_type() == ItemSlots::WRIST);
    if (this->wrist != nullptr)
        delete this->wrist;
    this->wrist = item;
}

void Equipment::set_gloves(Item* item) {
    assert(item->get_item_type() == ItemSlots::GLOVES);
    if (this->gloves != nullptr)
        delete this->gloves;
    this->gloves = item;
}

void Equipment::set_belt(Item* item) {
    assert(item->get_item_type() == ItemSlots::BELT);
    if (this->belt != nullptr)
        delete this->belt;
    this->belt = item;
}

void Equipment::set_legs(Item* item) {
    assert(item->get_item_type() == ItemSlots::LEGS);
    if (this->legs != nullptr)
        delete this->legs;
    this->legs = item;
}

void Equipment::set_boots(Item* item) {
    assert(item->get_item_type() == ItemSlots::BOOTS);
    if (this->boots != nullptr)
        delete this->boots;
    this->boots = item;
}

void Equipment::set_ring1(Item* item) {
    assert(item->get_item_type() == ItemSlots::RING);
    if (this->ring1 != nullptr)
        delete this->ring1;
    this->ring1 = item;
}

void Equipment::set_ring2(Item* item) {
    assert(item->get_item_type() == ItemSlots::RING);
    if (this->ring2 != nullptr)
        delete this->ring2;
    this->ring2 = item;
}

void Equipment::set_trinket1(Item* item) {
    assert(item->get_item_type() == ItemSlots::TRINKET);
    if (this->trinket1 != nullptr)
        delete this->trinket1;
    this->trinket1 = item;
}

void Equipment::set_trinket2(Item* item) {
    assert(item->get_item_type() == ItemSlots::TRINKET);
    if (this->trinket2 != nullptr)
        delete this->trinket2;
    this->trinket2 = item;
}

void Equipment::set_caster_offhand(Item* item) {
    assert(item->get_item_type() == ItemSlots::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    if (this->caster_offhand != nullptr)
        delete this->caster_offhand;
    this->caster_offhand = item;
}

void Equipment::set_relic(Item* item) {
    assert(item->get_item_type() == ItemSlots::RELIC);
    assert(get_ranged() == nullptr);
    if (this->relic != nullptr)
        delete this->relic;
    this->relic = item;
}

void Equipment::patch_changed() {
    if (get_mainhand()) {
        if (db->item_valid_for_current_patch(get_mainhand()->get_patch()))
            this->mainhand = nullptr;
    }

    if (get_offhand()) {
        if (db->item_valid_for_current_patch(get_offhand()->get_patch()))
            this->offhand = nullptr;
    }

    if (get_ranged()) {
        if (db->item_valid_for_current_patch(get_ranged()->get_patch()))
            this->ranged = nullptr;
    }

    if (get_head()) {
        if (db->item_valid_for_current_patch(get_head()->get_patch()))
            this->head = nullptr;
    }

    if (get_neck()) {
        if (db->item_valid_for_current_patch(get_neck()->get_patch()))
            this->neck = nullptr;
    }

    if (get_shoulders()) {
        if (db->item_valid_for_current_patch(get_shoulders()->get_patch()))
            this->shoulders = nullptr;
    }

    if (get_back()) {
        if (db->item_valid_for_current_patch(get_back()->get_patch()))
            this->back = nullptr;
    }

    if (get_chest()) {
        if (db->item_valid_for_current_patch(get_chest()->get_patch()))
            this->chest = nullptr;
    }

    if (get_wrist()) {
        if (db->item_valid_for_current_patch(get_wrist()->get_patch()))
            this->wrist = nullptr;
    }

    if (get_gloves()) {
        if (db->item_valid_for_current_patch(get_gloves()->get_patch()))
            this->gloves = nullptr;
    }

    if (get_belt()) {
        if (db->item_valid_for_current_patch(get_belt()->get_patch()))
            this->belt = nullptr;
    }

    if (get_legs()) {
        if (db->item_valid_for_current_patch(get_legs()->get_patch()))
            this->legs = nullptr;
    }

    if (get_boots()) {
        if (db->item_valid_for_current_patch(get_boots()->get_patch()))
            this->boots = nullptr;
    }

    if (get_ring1()) {
        if (db->item_valid_for_current_patch(get_ring1()->get_patch()))
            this->ring1 = nullptr;
    }

    if (get_ring2()) {
        if (db->item_valid_for_current_patch(get_ring2()->get_patch()))
            this->ring2 = nullptr;
    }

    if (get_trinket1()) {
        if (db->item_valid_for_current_patch(get_trinket1()->get_patch()))
            this->trinket1 = nullptr;
    }

    if (get_trinket2()) {
        if (db->item_valid_for_current_patch(get_trinket2()->get_patch()))
            this->trinket2 = nullptr;
    }

    if (get_caster_offhand()) {
        if (db->item_valid_for_current_patch(get_caster_offhand()->get_patch()))
            this->caster_offhand = nullptr;
    }

    if (get_relic()) {
        if (db->item_valid_for_current_patch(get_relic()->get_patch()))
            this->relic = nullptr;
    }
}

EquipmentDb* Equipment::get_db() const {
    return this->db;
}
