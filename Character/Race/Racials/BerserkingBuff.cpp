
#include "BerserkingBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "Random.h"

BerserkingBuff::BerserkingBuff(Character* pchar):
    Buff(pchar, "Berserking", 10, 0),
    random(new Random(10, 30)),
    curr_buff(0)
{}

void BerserkingBuff::buff_effect_when_applied() {
    curr_buff = random->get_roll();
    assert(curr_buff >= 10 && curr_buff <= 30);
    dynamic_cast<Warrior*>(pchar)->increase_attack_speed(static_cast<int>(curr_buff));
}

void BerserkingBuff::buff_effect_when_removed() {
    dynamic_cast<Warrior*>(pchar)->decrease_attack_speed(static_cast<int>(curr_buff));
}
