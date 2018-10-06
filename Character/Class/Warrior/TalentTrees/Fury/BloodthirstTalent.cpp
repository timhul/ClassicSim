
#include "BloodthirstTalent.h"
#include "Bloodthirst.h"
#include "Warrior.h"
#include "WarriorSpells.h"

BloodthirstTalent::BloodthirstTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Bloodthirst", "7ML", "Assets/warrior/fury/tier7/Spell_nature_bloodlust.png", 1)
{
    QString base_str = "Instantly attack the target causing damage equal to 45% of your attack power. In addition, the next 5 successful melee attacks will restore 10 health. This effect lasts 8 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

BloodthirstTalent::~BloodthirstTalent() = default;

void BloodthirstTalent::apply_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_bloodthirst()->increase_effect_via_talent();
}

void BloodthirstTalent::remove_rank_effect() {
    auto* warr = dynamic_cast<Warrior*>(pchar);
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_bloodthirst()->decrease_effect_via_talent();
}
