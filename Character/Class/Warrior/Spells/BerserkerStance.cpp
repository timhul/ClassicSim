
#include "BerserkerStance.h"
#include "Warrior.h"

BerserkerStance::BerserkerStance(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Berserker Stance", engine, pchar, roll, true, 0.0, 0),
    pchar(dynamic_cast<Warrior*>(pchar))
{}

bool BerserkerStance::is_ready_spell_specific() const {
    return !pchar->in_berserker_stance() && !pchar->on_stance_cooldown();
}

void BerserkerStance::spell_effect() {
    pchar->switch_to_berserker_stance();
}
