#include "CasterForm.h"

#include "CooldownControl.h"
#include "Druid.h"
#include "NoEffectSelfBuff.h"

CasterForm::CasterForm(Character* pchar) :
    Spell("Caster Form", "Assets/classes/Ui-charactercreate-classes_druid.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 0),
    druid(dynamic_cast<Druid*>(pchar)),
    buff(new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT, name))
{
    buff->enable_buff();
}

CasterForm::~CasterForm() {
    delete cooldown;
    delete buff;
}

SpellStatus CasterForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Caster)
        return SpellStatus::InCasterForm;

    return SpellStatus::Available;
}

void CasterForm::spell_effect() {
    druid->cancel_form();
}
