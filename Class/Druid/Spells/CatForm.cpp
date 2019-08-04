#include "CatForm.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CooldownControl.h"
#include "Druid.h"

CatForm::CatForm(Character* pchar, Buff* cat_form) :
    Spell("Cat Form", "Assets/ability/Ability_druid_catform.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 100),
    TalentRequirer({
                   new TalentRequirerInfo("Natural Shapeshifter", 3, DisabledAtZero::No),
                   new TalentRequirerInfo("Sharpened Claws", 3, DisabledAtZero::No),
                   }),
    druid(dynamic_cast<Druid*>(pchar)),
    buff(cat_form),
    base_resource_cost(resource_cost)
{
    buff->enable_buff();
}

CatForm::~CatForm() {
    delete cooldown;
}

SpellStatus CatForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Cat)
        return SpellStatus::InCatForm;

    return druid->on_form_cooldown() ? SpellStatus::OnFormCooldown : SpellStatus::Available;
}

void CatForm::spell_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(resource_cost)));
    druid->switch_to_form(DruidForm::Cat);
}

void CatForm::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Natural Shapeshifter")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}

void CatForm::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Natural Shapeshifter")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}
