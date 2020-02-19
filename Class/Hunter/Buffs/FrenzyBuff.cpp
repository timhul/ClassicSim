#include "FrenzyBuff.h"

#include "CharacterStats.h"
#include "Hunter.h"
#include "Pet.h"

FrenzyBuff::FrenzyBuff(Character* pchar, Pet* pet) :
    SelfBuff(pchar, QString("Frenzy (%1)").arg(pet->get_name()), "Assets/items/Inv_misc_monsterclaw_03.png", 8, 0) {}

void FrenzyBuff::buff_effect_when_applied() {
    pchar->get_pet()->increase_attack_speed(30);
}

void FrenzyBuff::buff_effect_when_removed() {
    pchar->get_pet()->decrease_attack_speed(30);
}
