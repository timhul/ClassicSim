
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Warrior.h"

DeathWish::DeathWish(Character* pchar) :
    Spell("Death Wish", "Assets/warrior/fury/tier6/Spell_shadow_deathpact.png", pchar, true, 180, 10),
    TalentRequirer(1, DisabledAtZero::Yes),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false; //  remove this once switching default argument to enabled=false
}

void DeathWish::spell_effect() {
    warr->get_death_wish_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}

void DeathWish::increase_talent_rank_effect(const QString&) {
}

void DeathWish::decrease_talent_rank_effect(const QString&) {
}
