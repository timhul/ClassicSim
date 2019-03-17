#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "FelstrikerBuff.h"
#include "MeleeSpecialTable.h"
#include "MeleeWhiteHitTable.h"

FelstrikerBuff::FelstrikerBuff(Character* pchar, const int duration):
    SharedBuff(pchar, "Felstriker", "Assets/items/Inv_weapon_shortblade_25.png", duration, 0)
{}

void FelstrikerBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_crit(1.0);

    set_tables_for_guaranteed_hit(pchar->get_mh_wpn_skill());
    set_tables_for_guaranteed_hit(pchar->get_oh_wpn_skill());
}

void FelstrikerBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_crit(1.0);

    pchar->get_combat_roll()->drop_tables();
}

void FelstrikerBuff::set_tables_for_guaranteed_hit(const int wpn_skill) {
    MeleeSpecialTable* special_table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    special_table->update_miss_chance(0.0);
    special_table->update_dodge_chance(0.0);
    special_table->update_parry_chance(0.0);
    special_table->update_block_chance(0.0);

    MeleeWhiteHitTable* white_table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    white_table->update_miss_chance(0.0);
    white_table->update_dodge_chance(0.0);
    white_table->update_glancing_chance(0.0);
    white_table->update_parry_chance(0.0);
    white_table->update_block_chance(0.0);
}
