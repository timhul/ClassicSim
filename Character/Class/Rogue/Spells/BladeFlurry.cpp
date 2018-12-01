#include "BladeFlurry.h"

#include "BladeFlurryBuff.h"
#include "Rogue.h"

BladeFlurry::BladeFlurry(Character* pchar) :
    Spell("Blade Flurry", "Assets/ability/Ability_warrior_punishingblow.png", pchar, RestrictedByGcd::Yes, 120, ResourceType::Energy, 0),
    TalentRequirer(1, DisabledAtZero::Yes),
    rogue(dynamic_cast<Rogue*>(pchar)),
    bf_buff(new BladeFlurryBuff(pchar))
{
    this->enabled = false;
}

BladeFlurry::~BladeFlurry() {
    delete bf_buff;
}

void BladeFlurry::spell_effect() {
    bf_buff->apply_buff();
    rogue->exit_stealth();

    add_spell_cd_event();
    add_gcd_event();
}

void BladeFlurry::increase_talent_rank_effect(const QString&) {
    bf_buff->enable_buff();
}

void BladeFlurry::decrease_talent_rank_effect(const QString&) {
    bf_buff->disable_buff();
}
