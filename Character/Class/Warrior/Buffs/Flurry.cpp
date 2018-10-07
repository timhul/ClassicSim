
#include "Flurry.h"
#include "Warrior.h"

Flurry::Flurry(Character* pchar): Buff(pchar, "Flurry", 15.0, 3) {
    rank_talents = {0, 10, 15, 20, 25, 30};
    max_rank_talent = 5;
}

void Flurry::buff_effect_when_applied() {
    pchar->increase_attack_speed(rank_talents[rank_talent]);
}

void Flurry::buff_effect_when_removed() {
    pchar->decrease_attack_speed(rank_talents[rank_talent]);
}
