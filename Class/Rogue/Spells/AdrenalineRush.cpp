#include "AdrenalineRush.h"

#include "AdrenalineRushBuff.h"
#include "CooldownControl.h"
#include "Rogue.h"

AdrenalineRush::AdrenalineRush(Rogue* rogue) :
    Spell("Adrenaline Rush", "Assets/spell/Spell_shadow_shadowworddominate.png", rogue, new CooldownControl(rogue, 300.0), RestrictedByGcd::Yes, ResourceType::Energy, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Adrenaline Rush", 1, DisabledAtZero::Yes)}),
    rogue(rogue),
    ar_buff(new AdrenalineRushBuff(rogue))
{
    this->enabled = false;
}

AdrenalineRush::~AdrenalineRush() {
    delete ar_buff;
    delete cooldown;
}

void AdrenalineRush::spell_effect() {
    ar_buff->apply_buff();
    rogue->exit_stealth();

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();
}

void AdrenalineRush::increase_talent_rank_effect(const QString&, const int) {
    ar_buff->enable_buff();
}

void AdrenalineRush::decrease_talent_rank_effect(const QString&, const int) {
    ar_buff->disable_buff();
}
