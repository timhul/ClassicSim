#include "BerserkerStance.h"

#include "CooldownControl.h"
#include "Warrior.h"

BerserkerStance::BerserkerStance(Character* pchar) :
    Spell("Berserker Stance", "Assets/ability/Ability_racial_avatar.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 0),
    warr(dynamic_cast<Warrior*>(pchar))
{}

BerserkerStance::~BerserkerStance() {
    delete cooldown;
}

SpellStatus BerserkerStance::is_ready_spell_specific() const {
    if (warr->in_berserker_stance())
        return SpellStatus::InBerserkerStance;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void BerserkerStance::spell_effect() {
    warr->switch_to_berserker_stance();
}
