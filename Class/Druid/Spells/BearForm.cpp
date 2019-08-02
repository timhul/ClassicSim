#include "BearForm.h"

#include "CooldownControl.h"
#include "Druid.h"
#include "NoEffectSelfBuff.h"

BearForm::BearForm(Character* pchar) :
    Spell("Bear Form", "Assets/ability/Ability_druid_demoralizingroar2.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 100),
    druid(dynamic_cast<Druid*>(pchar)),
    buff(new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT))
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
    buff->apply_buff();
}
