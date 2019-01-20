
#include "MortalStrikeTalent.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "MortalStrike.h"

MortalStrikeTalent::MortalStrikeTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Mortal Strike", "7ML", "Assets/ability/Ability_warrior_savageblow.png", 1),
    mortal_strike(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_mortal_strike())
{
    QString base_str = "A vicious strike that deals weapon damage plus 85 and wounds the target, reducing the effectiveness of any healing by 50% for 10 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

MortalStrikeTalent::~MortalStrikeTalent() = default;

void MortalStrikeTalent::apply_rank_effect() {
    mortal_strike->increase_talent_rank(mortal_strike, name);
}

void MortalStrikeTalent::remove_rank_effect() {
    mortal_strike->decrease_talent_rank(mortal_strike, name);
}
