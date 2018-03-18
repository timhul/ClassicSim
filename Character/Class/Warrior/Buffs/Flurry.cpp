
#include "Flurry.h"
#include "Warrior.h"

void Flurry::buff_effect_when_applied() {
    // TODO: Remove assumption player has 5/5 Flurry
    pchar->increase_ias(30);
}

void Flurry::buff_effect_when_removed() {
    // TODO: Remove assumption player has 5/5 Flurry
    pchar->decrease_ias(30);
}
