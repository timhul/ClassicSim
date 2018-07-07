
#include "Recklessness.h"
#include "Warrior.h"
#include "RecklessnessBuff.h"

void Recklessness::spell_effect() {
    dynamic_cast<Warrior*>(pchar)->get_recklessness_buff()->apply_buff();

    add_gcd_event();
    add_spell_cd_event();
}
