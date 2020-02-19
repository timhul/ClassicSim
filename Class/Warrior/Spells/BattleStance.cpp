#include "BattleStance.h"

#include "CooldownControl.h"
#include "Warrior.h"

BattleStance::BattleStance(Warrior* warrior) :
    Spell("Battle Stance",
          "Assets/ability/Ability_warrior_offensivestance.png",
          warrior,
          new CooldownControl(warrior, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Rage,
          0),
    warrior(warrior) {}

BattleStance::~BattleStance() {
    delete cooldown;
}

SpellStatus BattleStance::is_ready_spell_specific() const {
    if (warrior->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warrior->on_stance_cooldown())
        return SpellStatus::OnStanceCooldown;

    return SpellStatus::Available;
}

void BattleStance::spell_effect() {
    warrior->switch_to_battle_stance();
}
