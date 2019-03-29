#include "HunterSpells.h"

#include "AimedShot.h"
#include "AspectOfTheHawk.h"
#include "AutoShot.h"
#include "Engine.h"
#include "Hunter.h"
#include "HuntersMark.h"
#include "MainhandAttack.h"
#include "MultiShot.h"
#include "OffhandAttack.h"
#include "RangedHit.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->aimed_shot = new AimedShot(hunter);
    this->aspect_of_the_hawk = new AspectOfTheHawk(hunter);
    this->auto_shot = new AutoShot(hunter);
    this->hunters_mark = new HuntersMark(hunter);
    this->mh_attack = new MainhandAttack(hunter);
    this->multi_shot = new MultiShot(hunter);
    this->oh_attack = new OffhandAttack(hunter);

    spells.append(aimed_shot);
    spells.append(aspect_of_the_hawk);
    spells.append(auto_shot);
    spells.append(hunters_mark);
    spells.append(mh_attack);
    spells.append(multi_shot);
    spells.append(oh_attack);
}

void HunterSpells::add_next_ranged_attack() {
    if (attack_mode != AttackMode::RangedAttack)
        return;

    auto* new_event = new RangedHit(this, auto_shot->get_next_expected_use(), auto_shot->get_next_iteration());
    hunter->get_engine()->add_event(new_event);
}

void HunterSpells::ranged_auto_attack(const int iteration) {
    if (!auto_shot->attack_is_valid(iteration))
        return;

    if (!is_ranged_attacking())
        return;

    auto_shot->perform();

    add_next_ranged_attack();
}

void HunterSpells::add_next_oh_attack() {
    if (attack_mode != AttackMode::MeleeAttack)
        return;

    auto* new_event = new RangedHit(this, oh_attack->get_next_expected_use(), oh_attack->get_next_iteration());
    hunter->get_engine()->add_event(new_event);
}

void HunterSpells::oh_auto_attack(const int iteration) {
    if (!oh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    oh_attack->perform();

    add_next_oh_attack();
}

AimedShot* HunterSpells::get_aimed_shot() const {
    return this->aimed_shot;
}

AspectOfTheHawk* HunterSpells::get_aspect_of_the_hawk() const {
    return this->aspect_of_the_hawk;
}

AutoShot* HunterSpells::get_auto_shot() const {
    return this->auto_shot;
}

HuntersMark* HunterSpells::get_hunters_mark() const {
    return this->hunters_mark;
}

MultiShot* HunterSpells::get_multi_shot() const {
    return this->multi_shot;
}

OffhandAttack* HunterSpells::get_oh_attack() const {
    return oh_attack;
}
