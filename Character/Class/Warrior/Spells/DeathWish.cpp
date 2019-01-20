
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Warrior.h"

DeathWish::DeathWish(Character* pchar) :
    Spell("Death Wish", "Assets/spell/Spell_shadow_deathpact.png", pchar, RestrictedByGcd::Yes, 180, ResourceType::Rage, 10),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Death Wish", 1, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
}

void DeathWish::spell_effect() {
    warr->get_death_wish_buff()->apply_buff();

    add_spell_cd_event();
    add_gcd_event();

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}

void DeathWish::increase_talent_rank_effect(const QString&, const int) {
}

void DeathWish::decrease_talent_rank_effect(const QString&, const int) {
}
