#include "ZandalarianHeroCharm.h"

#include "Character.h"
#include "CharacterStats.h"

ZandalarianHeroCharm::ZandalarianHeroCharm(Character* pchar):
    SelfBuff(pchar, "Zandalarian Hero Charm", "Assets/items/Inv_jewelry_necklace_13.png", 20, 12)
{}

void ZandalarianHeroCharm::buff_effect_when_applied() {
    spell_damage = max_spell_damage;
    pchar->get_stats()->increase_base_spell_damage(spell_damage);
}

void ZandalarianHeroCharm::buff_effect_when_removed() {
    pchar->get_stats()->decrease_base_spell_damage(spell_damage);
}

void ZandalarianHeroCharm::charge_change_effect() {
    pchar->get_stats()->decrease_base_spell_damage(17);
    spell_damage -= 17;
}
