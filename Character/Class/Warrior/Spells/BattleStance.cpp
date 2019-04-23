#include "BattleStance.h"

#include "Warrior.h"

BattleStance::BattleStance(Character* pchar) :
    Spell("Battle Stance", "Assets/ability/Ability_warrior_offensivestance.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Rage, 0),
    warr(dynamic_cast<Warrior*>(pchar))
{}

SpellStatus BattleStance::is_ready_spell_specific() const {
    if (warr->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warr->on_stance_cooldown())
        return SpellStatus::OnStanceCooldown;

    return SpellStatus::Available;
}

void BattleStance::spell_effect() {
    warr->switch_to_battle_stance();
}
