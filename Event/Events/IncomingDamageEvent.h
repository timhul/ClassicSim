#pragma once

#include "Character.h"
#include "Event.h"

class Engine;

class IncomingDamageEvent : public Event {
public:
  IncomingDamageEvent(Character *character, Engine *engine,
                      const int timestamp);

  void act() override;

private:
  Engine *engine;
  Character *character;
  CombatRoll *roll;
};
