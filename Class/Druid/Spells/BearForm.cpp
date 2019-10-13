#include "BearForm.h"

#include "CooldownControl.h"
#include "Druid.h"
#include "NoEffectSelfBuff.h"
#include <cmath>

BearForm::BearForm(Character* pchar) :
    Spell("Bear Form", "Assets/ability/Ability_racial_bearform.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 100),
    TalentRequirer({new TalentRequirerInfo("Natural Shapeshifter", 3, DisabledAtZero::No)}),
    druid(dynamic_cast<Druid*>(pchar)),
    buff(new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT, "Bear Form", icon, Hidden::No)),
    base_resource_cost(resource_cost)
{
    buff->enable_buff();
}

BearForm::~BearForm() {
    delete cooldown;
    delete buff;
}

SpellStatus BearForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Bear)
        return SpellStatus::InBearForm;

    return druid->on_form_cooldown() ? SpellStatus::OnFormCooldown : SpellStatus::Available;
}

void BearForm::spell_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(resource_cost)));
    druid->switch_to_form(DruidForm::Bear);
}

void BearForm::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Natural Shapeshifter")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}

void BearForm::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
