
#include "FlurryTalent.h"
#include "Flurry.h"
#include "Warrior.h"

FlurryTalent::FlurryTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Flurry", "6MR", "Assets/warrior/fury/tier6/Ability_ghoulfrenzy.png", 5)
{
    QString base_str = "Increases your attack speed by %1% for your next 3 swings after dealing a melee critical strike.";
    initialize_rank_descriptions(base_str, 10, 5);
}

FlurryTalent::~FlurryTalent() = default;

void FlurryTalent::apply_rank_effect() {
    if (curr_points == 1)
        dynamic_cast<Warrior*>(pchar)->get_flurry()->enable_buff();

    dynamic_cast<Warrior*>(pchar)->get_flurry()->increase_rank();
}

void FlurryTalent::remove_rank_effect() {
    if (curr_points == 0)
        dynamic_cast<Warrior*>(pchar)->get_flurry()->disable_buff();

    dynamic_cast<Warrior*>(pchar)->get_flurry()->decrease_rank();
}
