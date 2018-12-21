#include "ImprovedExecute.h"

#include "Execute.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedExecute::ImprovedExecute(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Improved Execute", "4ML", "Assets/warrior/fury/tier4/Inv_sword_48.png", 2),
    execute(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_execute())
{
    QString base_str = "Reduces the rage cost of your Execute abillity by %1.";
    initialize_rank_descriptions(base_str, 2, 3);
}

ImprovedExecute::~ImprovedExecute() = default;

void ImprovedExecute::apply_rank_effect() {
    execute->increase_talent_rank(execute, name);
}

void ImprovedExecute::remove_rank_effect() {
    execute->decrease_talent_rank(execute, name);
}
