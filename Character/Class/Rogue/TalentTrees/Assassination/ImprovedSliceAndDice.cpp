#include "ImprovedSliceAndDice.h"

#include "SliceAndDice.h"
#include "Rogue.h"
#include "RogueSpells.h"

ImprovedSliceAndDice::ImprovedSliceAndDice(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Slice And Dice", "2RR", "Assets/ability/Ability_rogue_slicedice.png", 3),
    slice_and_dice(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_slice_and_dice())
{
    QString base_str = "Increases the duration of your Slice and Dice ability by %1%.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{15, 15}});
}

void ImprovedSliceAndDice::apply_rank_effect() {
    slice_and_dice->increase_talent_rank(slice_and_dice, name);
}

void ImprovedSliceAndDice::remove_rank_effect() {
    slice_and_dice->decrease_talent_rank(slice_and_dice, name);
}
