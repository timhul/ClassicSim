#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"

class CharacterSpells;

class PlayerAction: public Event {
public:
    PlayerAction(CharacterSpells* spells, const double timestamp);

    void act() override;

private:
    CharacterSpells* spells;
};

#endif // PLAYERACTION_H
