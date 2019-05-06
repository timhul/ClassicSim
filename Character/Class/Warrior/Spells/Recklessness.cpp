#include "Recklessness.h"

#include "RecklessnessBuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Recklessness::Recklessness(Warrior* pchar, WarriorSpells* spells) :
    Spell("Recklessness", "Assets/ability/Ability_criticalstrike.png", pchar, RestrictedByGcd::Yes, 1800.0, ResourceType::Rage, 0),
    spells(spells)
{}

void Recklessness::spell_effect() {
    spells->get_recklessness_buff()->apply_buff();

    add_gcd_event();
    add_spell_cd_event();
}

SpellStatus Recklessness::is_ready_spell_specific() const {
    auto warr = dynamic_cast<Warrior*>(pchar);

    if (warr->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warr->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}
