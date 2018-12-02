#include "AdrenalineRushTalent.h"

#include "AdrenalineRush.h"
#include "Rogue.h"
#include "RogueSpells.h"

AdrenalineRushTalent::AdrenalineRushTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Adrenaline Rush", "7ML", "Assets/spell/Spell_shadow_shadowworddominate.png", 1),
    adrenaline_rush(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_adrenaline_rush())
{
    QString base_str = "Increases your Energy regeneration rate by 100% for 15 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

void AdrenalineRushTalent::apply_rank_effect() {
    adrenaline_rush->increase_talent_rank(adrenaline_rush, name);
}

void AdrenalineRushTalent::remove_rank_effect() {
    adrenaline_rush->decrease_talent_rank(adrenaline_rush, name);
}
