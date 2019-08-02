#include "CatForm.h"

#include "CooldownControl.h"
#include "Druid.h"
#include "NoEffectSelfBuff.h"

CatForm::CatForm(Character* pchar) :
    Spell("Cat Form", "Assets/spell/Spell_nature_ravenform.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 100),
    TalentRequirer({new TalentRequirerInfo("Natural Shapeshifter", 3, DisabledAtZero::No)}),
    druid(dynamic_cast<Druid*>(pchar)),
    buff(new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT)),
    base_resource_cost(resource_cost)
{
    buff->enable_buff();
}

CatForm::~CatForm() {
    delete cooldown;
    delete buff;
}

SpellStatus CatForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Cat)
        return SpellStatus::InCatForm;

    return druid->on_form_cooldown() ? SpellStatus::OnFormCooldown : SpellStatus::Available;
}

void CatForm::spell_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(resource_cost)));
    buff->apply_buff();
}

void CatForm::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Natural Shapeshifter")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}

void CatForm::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
