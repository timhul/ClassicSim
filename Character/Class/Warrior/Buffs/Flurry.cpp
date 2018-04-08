
#include "Flurry.h"
#include "Warrior.h"

void Flurry::buff_effect_when_applied() {
    pchar->increase_attack_speed(ranks[rank - 1]);
}

void Flurry::buff_effect_when_removed() {
    pchar->decrease_attack_speed(ranks[rank - 1]);
}
