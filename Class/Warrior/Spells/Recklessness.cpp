#include "Recklessness.h"

#include "CooldownControl.h"
#include "RecklessnessBuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Recklessness::Recklessness(Warrior* warrior, WarriorSpells* spells) :
    Spell("Recklessness", "Assets/ability/Ability_criticalstrike.png", warrior, new CooldownControl(warrior, 1800.0), RestrictedByGcd::Yes, ResourceType::Rage, 0),
    warrior(warrior),
    spells(spells)
{}

Recklessness::~Recklessness() {
    delete cooldown;
}

void Recklessness::spell_effect() {
    spells->get_recklessness_buff()->apply_buff();

    cooldown->add_gcd_event();
    cooldown->add_spell_cd_event();
}

SpellStatus Recklessness::is_ready_spell_specific() const {
    if (warrior->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warrior->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    return warrior->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}
