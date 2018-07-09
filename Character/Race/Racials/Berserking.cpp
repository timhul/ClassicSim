
#include "Berserking.h"
#include "BerserkingBuff.h"
#include "Race.h"
#include "Character.h"

Berserking::Berserking(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Berserking", engine, pchar, roll, true, 180, 0)
{}

bool Berserking::is_ready_spell_specific() const {
    return pchar->get_race()->get_race_int() == Races::Troll;
}

void Berserking::spell_effect() {
    pchar->get_berserking_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();
}
