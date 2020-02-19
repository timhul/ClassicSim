#include "PlayerAction.h"

#include "CharacterSpells.h"

PlayerAction::PlayerAction(CharacterSpells* spells, const double timestamp) : Event(EventType::PlayerAction, timestamp), spells(spells) {}

void PlayerAction::act() {
    spells->perform_rotation();
}
