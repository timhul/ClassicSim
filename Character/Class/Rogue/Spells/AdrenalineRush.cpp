#include "AdrenalineRush.h"

#include "AdrenalineRushBuff.h"
#include "Rogue.h"

AdrenalineRush::AdrenalineRush(Character* pchar) :
    Spell("Adrenaline Rush", "Assets/spell/Spell_shadow_shadowworddominate.png", pchar, RestrictedByGcd::Yes, 300, ResourceType::Energy, 0),
    TalentRequirer(1, DisabledAtZero::Yes),
    rogue(dynamic_cast<Rogue*>(pchar)),
    ar_buff(new AdrenalineRushBuff(pchar))
{
    this->enabled = false;
}

AdrenalineRush::~AdrenalineRush() {
    delete ar_buff;
}

void AdrenalineRush::spell_effect() {
    ar_buff->apply_buff();
    rogue->exit_stealth();

    add_spell_cd_event();
    add_gcd_event();
}

void AdrenalineRush::increase_talent_rank_effect(const QString&) {
    ar_buff->enable_buff();
}

void AdrenalineRush::decrease_talent_rank_effect(const QString&) {
    ar_buff->disable_buff();
}
