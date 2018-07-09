
#include "Berserking.h"
#include "BerserkingBuff.h"
#include "Race.h"
#include "Character.h"

Berserking::Berserking(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Berserking", engine, pchar, roll, true, 180, 0)
{
    this->is_enabled_externally = true;
    this->enabled = false;
}

void Berserking::spell_effect() {
    pchar->get_berserking_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();
}

void Berserking::enable_spell_effect() {
    pchar->get_berserking_buff()->enable_buff();
}

void Berserking::disable_spell_effect() {
    pchar->get_berserking_buff()->disable_buff();
}
