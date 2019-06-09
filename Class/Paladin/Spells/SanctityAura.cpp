#include "SanctityAura.h"

#include "CooldownControl.h"
#include "Paladin.h"
#include "SanctityAuraBuff.h"

SanctityAura::SanctityAura(Paladin* pchar, SanctityAuraBuff* buff) :
    Spell("Sanctity Aura", "Assets/spell/Spell_holy_mindvision.png", pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Sanctity Aura", 1, DisabledAtZero::Yes)}),
    buff(buff)
{
    this->enabled = false;
}

SanctityAura::~SanctityAura() {
    delete cooldown;
}

void SanctityAura::spell_effect() {
    buff->apply_buff();
    cooldown->add_gcd_event();
}

void SanctityAura::increase_talent_rank_effect(const QString&, const int) {

}

void SanctityAura::decrease_talent_rank_effect(const QString&, const int) {

}
