
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
    if (this->mainhand != nullptr)
        delete this->mainhand;
    this->mainhand = item;
}

void Equipment::set_offhand(MeleeWeapon* item) {
    assert(item->get_item_type() == ItemTypes::OFFHAND);
    assert(get_caster_offhand() == nullptr);
    if (this->offhand != nullptr)
        delete this->offhand;
    this->offhand = item;
}

void Equipment::set_ranged(Item* item) {
    assert(item->get_item_type() == ItemTypes::RANGED);
    assert(get_relic() == nullptr);
    if (this->ranged != nullptr)
        delete this->ranged;
    this->ranged = item;
}

void Equipment::set_head(Item* item) {
    assert(item->get_item_type() == ItemTypes::HEAD);
    if (this->head != nullptr)
        delete this->head;
    this->head = item;
}

void Equipment::set_neck(Item* item) {
    assert(item->get_item_type() == ItemTypes::NECK);
    if (this->neck != nullptr)
        delete this->neck;
    this->neck = item;
}

void Equipment::set_shoulders(Item* item) {
    assert(item->get_item_type() == ItemTypes::SHOULDERS);
    if (this->shoulders != nullptr)
        delete this->shoulders;
    this->shoulders = item;
}

void Equipment::set_back(Item* item) {
    assert(item->get_item_type() == ItemTypes::BACK);
    if (this->back != nullptr)
        delete this->back;
    this->back = item;
}

void Equipment::set_chest(Item* item) {
    assert(item->get_item_type() == ItemTypes::CHEST);
    if (this->chest != nullptr)
        delete this->chest;
    this->chest = item;
}

void Equipment::set_wrist(Item* item) {
    assert(item->get_item_type() == ItemTypes::WRIST);
    if (this->wrist != nullptr)
        delete this->wrist;
    this->wrist = item;
}

void Equipment::set_gloves(Item* item) {
    assert(item->get_item_type() == ItemTypes::GLOVES);
    if (this->gloves != nullptr)
        delete this->gloves;
    this->gloves = item;
}

void Equipment::set_belt(Item* item) {
    assert(item->get_item_type() == ItemTypes::BELT);
    if (this->belt != nullptr)
        delete this->belt;
    this->belt = item;
}

void Equipment::set_legs(Item* item) {
    assert(item->get_item_type() == ItemTypes::LEGS);
    if (this->legs != nullptr)
        delete this->legs;
    this->legs = item;
}

void Equipment::set_boots(Item* item) {
    assert(item->get_item_type() == ItemTypes::BOOTS);
    if (this->boots != nullptr)
        delete this->boots;
    this->boots = item;
}

void Equipment::set_ring1(Item* item) {
    assert(item->get_item_type() == ItemTypes::RING);
    if (this->ring1 != nullptr)
        delete this->ring1;
    this->ring1 = item;
}

void Equipment::set_ring2(Item* item) {
    assert(item->get_item_type() == ItemTypes::RING);
    if (this->ring2 != nullptr)
        delete this->ring2;
    this->ring2 = item;
}

void Equipment::set_trinket1(Item* item) {
    assert(item->get_item_type() == ItemTypes::TRINKET);
    if (this->trinket1 != nullptr)
        delete this->trinket1;
    this->trinket1 = item;
}

void Equipment::set_trinket2(Item* item) {
    assert(item->get_item_type() == ItemTypes::TRINKET);
    if (this->trinket2 != nullptr)
        delete this->trinket2;
    this->trinket2 = item;
}

void Equipment::set_caster_offhand(Item* item) {
    assert(item->get_item_type() == ItemTypes::CASTER_OFFHAND);
    assert(get_offhand() == nullptr);
    if (this->caster_offhand != nullptr)
        delete this->caster_offhand;
    this->caster_offhand = item;
}

void Equipment::set_relic(Item* item) {
    assert(item->get_item_type() == ItemTypes::RELIC);
    assert(get_ranged() == nullptr);
    if (this->relic != nullptr)
        delete this->relic;
    this->relic = item;
}
