#include "Combustion.h"

#include "CombustionBuff.h"
#include "CooldownControl.h"
#include "Mage.h"

Combustion::Combustion(Mage* pchar) :
    Spell("Combustion",
          "Assets/spell/Spell_fire_sealoffire.png",
          pchar,
          new CooldownControl(pchar, 180.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          0,
          0),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Combustion", 1, DisabledAtZero::Yes)}),
    buff(new CombustionBuff(pchar)) {
    enabled = false;
}

Combustion::~Combustion() {
    delete buff;
    delete cooldown;
}

void Combustion::use_charge() {
    if (!buff->is_active())
        return;

    buff->use_charge();

    if (!buff->is_active())
        cooldown->add_spell_cd_event();
}

void Combustion::stack_crit_chance() {
    buff->refresh_buff();
}

void Combustion::spell_effect() {
    buff->apply_buff();
}

SpellStatus Combustion::is_ready_spell_specific() const {
    return buff->is_active() ? SpellStatus::BuffInactive : SpellStatus::Available;
}

void Combustion::increase_talent_rank_effect(const QString&, const int) {
    buff->enable_buff();
}

void Combustion::decrease_talent_rank_effect(const QString&, const int) {
    buff->disable_buff();
}
