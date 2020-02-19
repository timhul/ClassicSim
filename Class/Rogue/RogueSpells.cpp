#include "RogueSpells.h"

#include "AdrenalineRush.h"
#include "Backstab.h"
#include "Berserking.h"
#include "BladeFlurry.h"
#include "Engine.h"
#include "Eviscerate.h"
#include "Hemorrhage.h"
#include "MainhandAttack.h"
#include "OffhandAttackRogue.h"
#include "Rogue.h"
#include "SinisterStrike.h"
#include "SliceAndDice.h"
#include "ThistleTea.h"

RogueSpells::RogueSpells(Rogue* rogue) : CharacterSpells(rogue), rogue(rogue) {
    this->berserking = new Berserking(pchar, ResourceType::Energy, 10);
    add_spell_group({berserking});

    this->mh_attack = new MainhandAttack(rogue);
    this->oh_attack = new OffhandAttackRogue(rogue);

    add_spell_group({new AdrenalineRush(rogue)});
    add_spell_group({new Backstab(rogue)});
    add_spell_group({new BladeFlurry(rogue)});
    add_spell_group({new Eviscerate(rogue)});
    add_spell_group({new Hemorrhage(rogue)});
    add_spell_group({mh_attack});
    add_spell_group({oh_attack});
    add_spell_group({new SinisterStrike(rogue)});
    add_spell_group({new SliceAndDice(rogue)});
    add_spell_group({new ThistleTea(rogue)});
}

void RogueSpells::oh_auto_attack(const int iteration) {
    if (!oh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    oh_attack->perform();

    add_next_oh_attack();
}

void RogueSpells::add_next_oh_attack() {
    oh_attack->add_next_oh_attack();
}

OffhandAttack* RogueSpells::get_oh_attack() const {
    return oh_attack;
}
