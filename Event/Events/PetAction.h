#pragma once

#include "Event.h"

class Pet;

class PetAction : public Event {
public:
    PetAction(Pet* pet, const double timestamp);

    void act() override;

private:
    Pet* pet;
};
