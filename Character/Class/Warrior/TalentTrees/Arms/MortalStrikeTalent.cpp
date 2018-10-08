
#include "MortalStrikeTalent.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "MortalStrike.h"

MortalStrikeTalent::MortalStrikeTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Mortal Strike", "7ML", "Assets/warrior/arms/tier7/Ability_warrior_savageblow.png", 1)
{
    QString base_str = "A vicious strike that deals weapon damage plus 85 and wounds the target, reducing the effectiveness of any healing by 50% for 10 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

MortalStrikeTalent::~MortalStrikeTalent() = default;

void MortalStrikeTalent::apply_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_mortal_strike()->enable();
}

void MortalStrikeTalent::remove_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_mortal_strike()->disable();
}
