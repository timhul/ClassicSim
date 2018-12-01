#include "RogueSpells.h"

#include "AdrenalineRush.h"
#include "Backstab.h"
#include "Eviscerate.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "OffhandMeleeHit.h"
#include "Rogue.h"
#include "SliceAndDice.h"

RogueSpells::RogueSpells(Rogue* rogue) :
    Spells(rogue),
    rogue(rogue)
{
    this->mh_attack = new MainhandAttack(rogue);
    this->oh_attack = new OffhandAttack(rogue);
    this->adrenaline_rush = new AdrenalineRush(rogue);
    this->backstab = new Backstab(rogue);
    this->eviscerate = new Eviscerate(rogue);
    this->slice_and_dice = new SliceAndDice(rogue);

    spells.append(mh_attack);
    spells.append(oh_attack);
    spells.append(adrenaline_rush);
    spells.append(backstab);
    spells.append(eviscerate);
    spells.append(slice_and_dice);
}

RogueSpells::~RogueSpells() = default;

void RogueSpells::oh_auto_attack(const int iteration) {
    if (!oh_attack->attack_is_valid(iteration))
        return;

    if (!pchar->is_melee_attacking())
        return;

    oh_attack->perform();

    add_next_oh_attack();
}

void RogueSpells::add_next_oh_attack() {
    auto* new_event = new OffhandMeleeHit(this, oh_attack->get_next_expected_use(), oh_attack->get_next_iteration());
    rogue->get_engine()->add_event(new_event);
}

OffhandAttack* RogueSpells::get_oh_attack() const {
    return oh_attack;
}

AdrenalineRush* RogueSpells::get_adrenaline_rush() const {
    return this->adrenaline_rush;
}

Backstab* RogueSpells::get_backstab() const {
    return this->backstab;
}

Eviscerate* RogueSpells::get_eviscerate() const {
    return this->eviscerate;
}

SliceAndDice* RogueSpells::get_slice_and_dice() const {
    return this->slice_and_dice;
}
