#include "SanctityAura.h"

#include "CooldownControl.h"
#include "Paladin.h"
#include "SanctityAuraBuff.h"

SanctityAura::SanctityAura(Paladin* pchar) :
    Spell("Sanctity Aura", "Assets/spell/Spell_holy_mindvision.png", pchar, RestrictedByGcd::Yes, 0, ResourceType::Mana, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Sanctity Aura", 1, DisabledAtZero::Yes)}),
    buff(new SanctityAuraBuff(pchar))
{
    this->enabled = false;
}

SanctityAura::~SanctityAura() {
    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
}

void SanctityAura::spell_effect() {
    buff->apply_buff();
    cooldown->add_gcd_event();
}

void SanctityAura::increase_talent_rank_effect(const QString&, const int) {
    buff->enable_buff();
}

void SanctityAura::decrease_talent_rank_effect(const QString&, const int) {
    buff->disable_buff();
}
