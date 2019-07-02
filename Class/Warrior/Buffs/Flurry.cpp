#include "Flurry.h"

#include "Character.h"

Flurry::Flurry(Character* pchar):
    SelfBuff(pchar, "Flurry", "Assets/ability/Ability_ghoulfrenzy.png", 15, 3),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Flurry", 5, DisabledAtZero::Yes)}),
    rank_talents({0, 10, 15, 20, 25, 30})
{}

void Flurry::buff_effect_when_applied() {
    pchar->increase_melee_attack_speed(attack_speed_increase);
}

void Flurry::buff_effect_when_removed() {
    pchar->decrease_melee_attack_speed(attack_speed_increase);
}

void Flurry::increase_talent_rank_effect(const QString&, const int curr) {
    attack_speed_increase = rank_talents[curr];
}

void Flurry::decrease_talent_rank_effect(const QString&, const int curr) {
    attack_speed_increase = rank_talents[curr];
}
