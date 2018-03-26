
#include "BloodthirstTalent.h"
#include "Character.h"

BloodthirstTalent::BloodthirstTalent(Character *pchar) :
    Talent(pchar, "Bloodthirst", "7ML", "Assets/warrior/fury/tier7/Spell_nature_bloodlust.png", 1)
{
    QString base_str = "Instantly attack the target causing damage equal to 45% of your attack power. In addition, the next 5 successful melee attacks will restore 10 health. This effect lasts 8 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

BloodthirstTalent::~BloodthirstTalent() {

}

void BloodthirstTalent::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void BloodthirstTalent::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

QString BloodthirstTalent::get_requirement_string() const {
    QString req_string = "";
    if (parent != nullptr && !parent->is_maxed()) {
        req_string = "Requires 1 point in Death Wish\n";
    }

    return req_string + "Requires 30 points in Fury Talents";
}
