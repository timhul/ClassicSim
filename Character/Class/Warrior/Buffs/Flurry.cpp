
#include "Flurry.h"
#include "Warrior.h"

Flurry::Flurry(Character* pchar):
    Buff(pchar, "Flurry", "Assets/warrior/fury/tier6/Ability_ghoulfrenzy.png", 15.0, 3),
    TalentRequirer(5, DisabledAtZero::Yes)
{
    rank_talents = {0, 10, 15, 20, 25, 30};
}

void Flurry::buff_effect_when_applied() {
    pchar->increase_attack_speed(attack_speed_increase);
}

void Flurry::buff_effect_when_removed() {
    pchar->decrease_attack_speed(attack_speed_increase);
}

void Flurry::increase_talent_rank_effect(const QString&) {
    attack_speed_increase = rank_talents[curr_talent_rank];
}

void Flurry::decrease_talent_rank_effect(const QString&) {
    attack_speed_increase = rank_talents[curr_talent_rank];
}
