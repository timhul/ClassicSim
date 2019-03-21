#include "BerserkingBuff.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Random.h"

BerserkingBuff::BerserkingBuff(Character* pchar):
    Buff(pchar, "Berserking", "Assets/races/Racial_troll_berserk.png", 10, 0),
    random(new Random(10, 30)),
    curr_buff(0)
{}

void BerserkingBuff::buff_effect_when_applied() {
    curr_buff = random->get_roll();
    pchar->increase_melee_attack_speed(curr_buff);
    pchar->increase_ranged_attack_speed(curr_buff);
}

void BerserkingBuff::buff_effect_when_removed() {
    pchar->decrease_melee_attack_speed(curr_buff);
    pchar->decrease_ranged_attack_speed(curr_buff);
}
