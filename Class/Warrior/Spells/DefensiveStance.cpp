#include "DefensiveStance.h"

#include "CooldownControl.h"
#include "Warrior.h"

DefensiveStance::DefensiveStance(Warrior* warrior) :
    Spell("Defensive Stance",
          "Assets/ability/Ability_racial_avatar.png",
          warrior,
          new CooldownControl(warrior, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Rage,
          0),
    warrior(warrior) {}

DefensiveStance::~DefensiveStance() {
    delete cooldown;
}

SpellStatus DefensiveStance::is_ready_spell_specific() const {
    if (warrior->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    return warrior->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void DefensiveStance::spell_effect() {
    warrior->switch_to_defensive_stance();
}
