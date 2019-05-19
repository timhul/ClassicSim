#include "BladeFlurry.h"

#include "BladeFlurryBuff.h"
#include "CooldownControl.h"
#include "Rogue.h"

BladeFlurry::BladeFlurry(Character* pchar) :
    Spell("Blade Flurry", "Assets/ability/Ability_warrior_punishingblow.png", pchar, new CooldownControl(pchar, 120.0), RestrictedByGcd::Yes, ResourceType::Energy, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Blade Flurry", 1, DisabledAtZero::Yes)}),
    rogue(dynamic_cast<Rogue*>(pchar)),
    bf_buff(new BladeFlurryBuff(pchar))
{
    this->enabled = false;
}

BladeFlurry::~BladeFlurry() {
    delete bf_buff;
    delete cooldown;
}

void BladeFlurry::spell_effect() {
    bf_buff->apply_buff();
    rogue->exit_stealth();

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();
}

void BladeFlurry::increase_talent_rank_effect(const QString&, const int) {
    bf_buff->enable_buff();
}

void BladeFlurry::decrease_talent_rank_effect(const QString&, const int) {
    bf_buff->disable_buff();
}
