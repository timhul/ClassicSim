
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Warrior.h"

DeathWish::DeathWish(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Death Wish", engine, pchar, roll, true, 180, 10)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    this->is_enabled_externally = true;
    this->enabled = false;
}

void DeathWish::spell_effect() {
    pchar->get_death_wish_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    pchar->lose_rage(resource_cost);
}
