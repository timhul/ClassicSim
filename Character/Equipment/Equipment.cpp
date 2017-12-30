
#include "Equipment.h"
#include <assert.h>

Equipment::Equipment() {
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

void Equipment::set_mainhand(MeleeWeapon* item) {
    assert(item->get_item_type() == ItemTypes::MAINHAND);
    this->mainhand = item;
}

void Equipment::set_offhand(MeleeWeapon* item) {
    assert(item->get_item_type() == ItemTypes::OFFHAND);
    assert(get_caster_offhand() == nullptr);
    this->offhand = item;
}

void Equipment::set_ranged(Item* item) {
    assert(item->get_item_type() == ItemTypes::RANGED);
    assert(get_relic() == nullptr);
    this->ranged = item;
}

void Equipment::set_head(Item* item) {
    assert(item->get_item_type() == ItemTypes::HEAD);
    this->head = item;
}

void Equipment::set_neck(Item* item) {
    assert(item->get_item_type() == ItemTypes::NECK);
    this->neck = item;
}

void Equipment::set_shoulders(Item* item) {
    assert(item->get_item_type() == ItemTypes::SHOULDERS);
    this->shoulders = item;
}

void Equipment::set_back(Item* item) {
    assert(item->get_item_type() == ItemTypes::BACK);
    this->back = item;
}

void Equipment::set_chest(Item* item) {
    assert(item->get_item_type() == ItemTypes::CHEST);
    this->chest = item;
}

void Equipment::set_wrist(Item* item) {
    assert(item->get_item_type() == ItemTypes::WRIST);
    this->wrist = item;
}

void Equipment::set_gloves(Item* item) {
    assert(item->get_item_type() == ItemTypes::GLOVES);
    this->gloves = item;
}

void Equipment::set_belt(Item* item) {
    assert(item->get_item_type() == ItemTypes::BELT);
    this->belt = item;
}

void Equipment::set_legs(Item* item) {
    assert(item->get_item_type() == ItemTypes::LEGS);
    this->legs = item;
}

void Equipment::set_boots(Item* item) {
    assert(item->get_item_type() == ItemTypes::BOOTS);
    this->boots = item;
}

void Equipment::set_ring1(Item* item) {
    assert(item->get_item_type() == ItemTypes::RING);
    this->ring1 = item;
}

void Equipment::set_ring2(Item* item) {
    assert(item->get_item_type() == ItemTypes::RING);
    this->ring2 = item;
}

void Equipment::set_trinket1(Item* item) {
    assert(item->get_item_type() == ItemTypes::TRINKET);
    this->trinket1 = item;
}

void Equipment::set_trinket2(Item* item) {
    assert(item->get_item_type() == ItemTypes::TRINKET);
    this->trinket2 = item;
}

void Equipment::set_caster_offhand(Item* item) {
    assert(item->get_item_type() == ItemTypes::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    this->caster_offhand = item;
}

void Equipment::set_relic(Item* item) {
    assert(item->get_item_type() == ItemTypes::RELIC);
    assert(get_ranged() == nullptr);
    this->relic = item;
}
