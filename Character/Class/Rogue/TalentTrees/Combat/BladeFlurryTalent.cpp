#include "BladeFlurryTalent.h"

#include "BladeFlurry.h"
#include "Rogue.h"
#include "RogueSpells.h"

BladeFlurryTalent::BladeFlurryTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Blade Flurry", "5ML", "Assets/ability/Ability_warrior_punishingblow.png", 1),
    blade_flurry(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_blade_flurry())
{
    QString base_str = "Increases your attack speed by 20%. In addition, attacks strike an additional nearby opponent. Lasts 15 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

void BladeFlurryTalent::apply_rank_effect() {
    blade_flurry->increase_talent_rank(blade_flurry, name);
}

void BladeFlurryTalent::remove_rank_effect() {
    blade_flurry->decrease_talent_rank(blade_flurry, name);
}
