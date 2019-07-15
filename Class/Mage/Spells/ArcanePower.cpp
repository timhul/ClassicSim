#include "ArcanePower.h"

#include "ArcanePowerBuff.h"
#include "CooldownControl.h"
#include "Mage.h"

ArcanePower::ArcanePower(Mage* pchar) :
    Spell("Arcane Power", "Assets/spell/Spell_nature_lightning.png", pchar, new CooldownControl(pchar, 180.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Arcane Power", 1, DisabledAtZero::Yes)}),
    buff(new ArcanePowerBuff(pchar))
{
    enabled = false;
}

ArcanePower::~ArcanePower() {
    delete buff;
    delete cooldown;
}

void ArcanePower::spell_effect() {
    cooldown->add_gcd_event();
    cooldown->add_spell_cd_event();

    buff->apply_buff();
}

void ArcanePower::increase_talent_rank_effect(const QString&, const int) {
    buff->enable_buff();
}

void ArcanePower::decrease_talent_rank_effect(const QString&, const int) {
    buff->disable_buff();
}
