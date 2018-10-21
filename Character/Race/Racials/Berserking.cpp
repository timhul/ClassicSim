
#include "Berserking.h"
#include "BerserkingBuff.h"
#include "Race.h"
#include "Character.h"

Berserking::Berserking(Character* pchar) :
    Spell("Berserking", "Assets/Racial_troll_berserk.png", pchar, true, 180, 0)
{
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
