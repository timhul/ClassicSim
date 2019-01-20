
#include "FlurryTalent.h"
#include "Flurry.h"
#include "Warrior.h"
#include "TalentRequirer.h"

FlurryTalent::FlurryTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Flurry", "6MR", "Assets/ability/Ability_ghoulfrenzy.png", 5),
    flurry(dynamic_cast<Warrior*>(pchar)->get_flurry())
{
    QString base_str = "Increases your attack speed by %1% for your next 3 swings after dealing a melee critical strike.";
    initialize_rank_descriptions(base_str, 10, 5);
}

FlurryTalent::~FlurryTalent() = default;

void FlurryTalent::apply_rank_effect() {
    flurry->increase_talent_rank(flurry, name);
}

void FlurryTalent::remove_rank_effect() {
    flurry->decrease_talent_rank(flurry, name);
}
