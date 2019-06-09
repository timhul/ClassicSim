#include "BestialWrathBuff.h"

#include "CharacterStats.h"
#include "Hunter.h"
#include "Pet.h"

BestialWrathBuff::BestialWrathBuff(Character* pchar, const QString& pet_name):
    SelfBuff(pchar, QString("Bestial Wrath (%1)").arg(pet_name),
         "Assets/ability/Ability_druid_ferociousbite.png",
         18,
         0)
{}

void BestialWrathBuff::buff_effect_when_applied() {
    pchar->get_pet()->increase_damage_modifier(50);
}

void BestialWrathBuff::buff_effect_when_removed() {
    pchar->get_pet()->decrease_damage_modifier(50);
}
