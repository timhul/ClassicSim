
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Warrior.h"

DeathWish::DeathWish(Character* pchar) :
    Spell("Death Wish", pchar, true, 180, 10),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->is_enabled_externally = true;
    this->enabled = false;
}

void DeathWish::enable_spell_effect() {
    warr->get_death_wish_buff()->increase_rank();
}

void DeathWish::disable_spell_effect() {
    warr->get_death_wish_buff()->decrease_rank();
}

void DeathWish::spell_effect() {
    warr->get_death_wish_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}
