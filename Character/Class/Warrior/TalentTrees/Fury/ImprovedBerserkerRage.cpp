
#include "ImprovedBerserkerRage.h"
#include "BerserkerRage.h"
#include "Warrior.h"
#include "WarriorSpells.h"

ImprovedBerserkerRage::ImprovedBerserkerRage(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree,  "Improved Berserker Rage", "6LL", "Assets/spell/Spell_nature_ancestralguardian.png", 2),
    berserker_rage(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_berserker_rage())
{
    QString base_str = "The Berserker Rage ability will generate %1 rage when used.";
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<int, int>>{{5, 5}});
}

ImprovedBerserkerRage::~ImprovedBerserkerRage() = default;

void ImprovedBerserkerRage::apply_rank_effect() {
    berserker_rage->increase_talent_rank(berserker_rage, name);
}

void ImprovedBerserkerRage::remove_rank_effect() {
    berserker_rage->decrease_talent_rank(berserker_rage, name);
}
