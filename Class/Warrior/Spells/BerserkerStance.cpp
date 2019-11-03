#include "BerserkerStance.h"

#include "CooldownControl.h"
#include "Warrior.h"

BerserkerStance::BerserkerStance(Warrior* warrior) :
    Spell("Berserker Stance", "Assets/ability/Ability_racial_avatar.png", warrior, new CooldownControl(warrior, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 0),
    warrior(warrior)
{}

BerserkerStance::~BerserkerStance() {
    delete cooldown;
}

SpellStatus BerserkerStance::is_ready_spell_specific() const {
    if (warrior->in_berserker_stance())
        return SpellStatus::InBerserkerStance;

    return warrior->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void BerserkerStance::spell_effect() {
    warrior->switch_to_berserker_stance();
}
