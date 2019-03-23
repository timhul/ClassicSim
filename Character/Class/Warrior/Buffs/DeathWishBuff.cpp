#include "DeathWishBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

DeathWishBuff::DeathWishBuff(Character* pchar):
    Buff(pchar, "Death Wish", "Assets/spell/Spell_shadow_deathpact.png", 30, 0)
{}

DeathWishBuff::~DeathWishBuff() {
    if (is_enabled())
        disable_buff();
}

void DeathWishBuff::buff_effect_when_applied() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->increase_total_phys_dmg_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->add_phys_damage_taken_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->add_spell_damage_taken_mod(20);
}

void DeathWishBuff::buff_effect_when_removed() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->decrease_total_phys_dmg_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->remove_phys_damage_taken_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->remove_spell_damage_taken_mod(20);
}
