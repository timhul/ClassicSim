#include "PriestSpells.h"

#include "Berserking.h"
#include "MainhandAttack.h"
#include "Priest.h"

PriestSpells::PriestSpells(Priest* priest) :
    CharacterSpells(priest),
    priest(priest)
{
    this->berserking = new Berserking(pchar, ResourceType::Mana, 110);
    add_spell_group({berserking});

    this->mh_attack = new MainhandAttack(priest);
    add_spell_group({mh_attack});
}

PriestSpells::~PriestSpells() = default;
