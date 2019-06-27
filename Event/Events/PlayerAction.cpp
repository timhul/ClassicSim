#include "PlayerAction.h"

#include "CharacterSpells.h"

PlayerAction::PlayerAction(CharacterSpells* spells, const double timestamp):
    Event(Events::PlayerAction, timestamp, "PlayerAction"),
    spells(spells)
{}

void PlayerAction::act() {
    spells->perform_rotation();
}
