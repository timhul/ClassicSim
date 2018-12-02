
#include "BloodthirstTalent.h"
#include "Bloodthirst.h"
#include "Warrior.h"
#include "WarriorSpells.h"

BloodthirstTalent::BloodthirstTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Bloodthirst", "7ML", "Assets/warrior/fury/tier7/Spell_nature_bloodlust.png", 1),
    bloodthirst(dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells())->get_bloodthirst())
{
    QString base_str = "Instantly attack the target causing damage equal to 45% of your attack power. In addition, the next 5 successful melee attacks will restore 10 health. This effect lasts 8 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

BloodthirstTalent::~BloodthirstTalent() = default;

void BloodthirstTalent::apply_rank_effect() {
    bloodthirst->increase_talent_rank(bloodthirst, name);
}

void BloodthirstTalent::remove_rank_effect() {
    bloodthirst->decrease_talent_rank(bloodthirst, name);
}
