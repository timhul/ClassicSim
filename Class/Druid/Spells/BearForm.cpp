#include "BearForm.h"

#include <cmath>

#include "CooldownControl.h"
#include "Druid.h"
#include "NoEffectSelfBuff.h"

BearForm::BearForm(Druid* druid, Buff* bear_form) :
    Spell("Bear Form",
          "Assets/ability/Ability_racial_bearform.png",
          druid,
          new CooldownControl(druid, 0.0),
          RestrictedByGcd::No,
          ResourceType::Mana,
          100),
    TalentRequirer({
        new TalentRequirerInfo("Natural Shapeshifter", 3, DisabledAtZero::No),
        new TalentRequirerInfo("Sharpened Claws", 3, DisabledAtZero::No),
    }),
    druid(druid),
    buff(bear_form),
    base_resource_cost(resource_cost) {
    buff->enable_buff();
}

BearForm::~BearForm() {
    delete cooldown;
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
