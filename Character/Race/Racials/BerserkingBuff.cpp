#include "BerserkingBuff.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Random.h"

BerserkingBuff::BerserkingBuff(Character* pchar):
    SelfBuff(pchar, "Berserking", "Assets/races/Racial_troll_berserk.png", 10, 0),
    random(new Random(0, 30)),
    curr_buff(0)
{}

BerserkingBuff::~BerserkingBuff() {
    delete random;
}

void BerserkingBuff::buff_effect_when_applied() {
    pchar->increase_melee_attack_speed(10);
    pchar->increase_ranged_attack_speed(10);

    curr_buff = random->get_roll();
    if (curr_buff == 0)
        return;

    pchar->increase_melee_attack_speed(curr_buff);
    pchar->increase_ranged_attack_speed(curr_buff);
}

void BerserkingBuff::buff_effect_when_removed() {
    pchar->decrease_melee_attack_speed(10);
    pchar->decrease_ranged_attack_speed(10);

    if (curr_buff == 0)
        return;

    pchar->decrease_melee_attack_speed(curr_buff);
    pchar->decrease_ranged_attack_speed(curr_buff);
}
