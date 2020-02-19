#include "PetAction.h"

#include "Pet.h"

PetAction::PetAction(Pet* pet, const double timestamp) : Event(EventType::PetAction, timestamp), pet(pet) {}

void PetAction::act() {
    pet->use_resource();
}
