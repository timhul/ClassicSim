
#include "Flurry.h"
#include "Warrior.h"
#include <QDebug>
void Flurry::buff_effect_when_applied() {
    // TODO: Remove assumption player has 5/5 Flurry, or has Flurry at all
    pchar->increase_attack_speed(30);
}

void Flurry::buff_effect_when_removed() {
    // TODO: Remove assumption player has 5/5 Flurry, or has Flurry at all
    pchar->decrease_attack_speed(30);
}
