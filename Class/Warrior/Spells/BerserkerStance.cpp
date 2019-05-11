#include "BerserkerStance.h"

#include "Warrior.h"

BerserkerStance::BerserkerStance(Character* pchar) :
    Spell("Berserker Stance", "Assets/ability/Ability_racial_avatar.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Rage, 0),
    warr(dynamic_cast<Warrior*>(pchar))
{}

SpellStatus BerserkerStance::is_ready_spell_specific() const {
    if (warr->in_berserker_stance())
        return SpellStatus::InBerserkerStance;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void BerserkerStance::spell_effect() {
    warr->switch_to_berserker_stance();
}
