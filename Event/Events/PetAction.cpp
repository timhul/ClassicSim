#include "PetAction.h"

#include "Pet.h"

PetAction::PetAction(Pet* pet, const double timestamp):
    Event(Events::PetAction)
{
    this->pet = pet;
    this->priority = timestamp;
    this->name = "PetAction";
}

void PetAction::act() {
    pet->use_resource();
}
