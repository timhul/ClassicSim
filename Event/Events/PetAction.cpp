#include "PetAction.h"

#include "Pet.h"

PetAction::PetAction(Pet* pet, const double timestamp):
    Event(Events::PetAction, timestamp, "PetAction"),
    pet(pet)
{}

void PetAction::act() {
    pet->use_resource();
}
