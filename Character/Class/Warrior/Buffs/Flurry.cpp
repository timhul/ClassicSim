
#include "Flurry.h"
#include "Warrior.h"

void Flurry::buff_effect(Character* pchar) {
    // TODO: Remove assumption player has 5/5 Flurry
    pchar->increase_ias(30);
}
