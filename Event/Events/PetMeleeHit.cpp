#include "PetMeleeHit.h"

#include "Pet.h"

PetMeleeHit::PetMeleeHit(Pet* pet, const int iteration, const double timestamp):
    Event(Events::PetMeleeHit)
{
    this->pet = pet;
    this->iteration = iteration;
    this->priority = timestamp;
    this->name = "PetMeleeHit";
}

void PetMeleeHit::act() {
    pet->auto_attack(iteration);
}
