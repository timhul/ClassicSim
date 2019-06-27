#pragma once

#include "Event.h"

class Engine;

class EncounterEnd: public Event {
public:
    EncounterEnd(Engine* engine, const int combat_length);

    void act() override;

private:
    Engine* engine;
};
