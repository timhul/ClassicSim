#include "PetMeleeHit.h"

#include "Pet.h"

PetMeleeHit::PetMeleeHit(Pet* pet, const int iteration, const double timestamp):
    Event(Events::PetMeleeHit, timestamp, "PetMeleeHit"),
    pet(pet),
    iteration(iteration)
{}

void PetMeleeHit::act() {
    pet->auto_attack(iteration);
}
