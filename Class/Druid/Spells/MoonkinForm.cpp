#include "MoonkinForm.h"

#include "CooldownControl.h"
#include "Druid.h"
#include "MoonkinFormBuff.h"
#include "NoEffectSelfBuff.h"

MoonkinForm::MoonkinForm(Character* pchar, MoonkinFormBuff* buff) :
    Spell("Moonkin Form", "Assets/spell/Spell_nature_forceofnature.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 100),
    TalentRequirer({new TalentRequirerInfo("Moonkin Form", 1, DisabledAtZero::Yes)}),
    druid(dynamic_cast<Druid*>(pchar)),
    buff(buff)
{
    enabled = false;
}

MoonkinForm::~MoonkinForm() {
    delete cooldown;
}

SpellStatus MoonkinForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Moonkin)
        return SpellStatus::InMoonkinForm;

    return druid->on_form_cooldown() ? SpellStatus::OnFormCooldown : SpellStatus::Available;
}

void MoonkinForm::spell_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(resource_cost)));
    buff->apply_buff();
}

void MoonkinForm::increase_talent_rank_effect(const QString&, const int) {

}

void MoonkinForm::decrease_talent_rank_effect(const QString&, const int) {

}
