
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Warrior.h"

DeathWish::DeathWish(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Death Wish", engine, pchar, roll, 180, 10)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int DeathWish::spell_effect(const int) {
    pchar->get_death_wish_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    return resource_cost;
}
