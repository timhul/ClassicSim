
#include "DeathWishTalent.h"
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"

DeathWishTalent::DeathWishTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Death Wish", "5ML", "Assets/warrior/fury/tier5/Spell_shadow_deathpact.png", 1),
    death_wish(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_death_wish()),
    death_wish_buff(dynamic_cast<Warrior*>(pchar)->get_death_wish_buff())
{
    QString base_str = "When activated, increases your physical damage by 20% and makes you immune to Fear effects, but lowers your armor and all resistances by 20%. Lasts 30 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

DeathWishTalent::~DeathWishTalent() = default;

void DeathWishTalent::apply_rank_effect() {
    death_wish->increase_talent_rank(death_wish, name);
    death_wish_buff->increase_talent_rank(death_wish_buff, name);
}

void DeathWishTalent::remove_rank_effect() {
    death_wish->decrease_talent_rank(death_wish, name);
    death_wish_buff->decrease_talent_rank(death_wish_buff, name);
}
