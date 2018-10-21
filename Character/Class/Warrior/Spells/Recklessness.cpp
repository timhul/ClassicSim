
#include "Recklessness.h"
#include "Warrior.h"
#include "RecklessnessBuff.h"

Recklessness::Recklessness(Character* pchar) :
    Spell("Recklessness", "Assets/warrior/Ability_criticalstrike.png", pchar, true, 1800.0, 0)
{}

void Recklessness::spell_effect() {
    dynamic_cast<Warrior*>(pchar)->get_recklessness_buff()->apply_buff();

    add_gcd_event();
    add_spell_cd_event();
}

bool Recklessness::is_ready_spell_specific() const {
    return dynamic_cast<Warrior*>(pchar)->in_berserker_stance();
}
