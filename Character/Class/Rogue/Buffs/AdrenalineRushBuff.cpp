#include "AdrenalineRushBuff.h"

#include "Energy.h"
#include "Rogue.h"

AdrenalineRushBuff::AdrenalineRushBuff(Character* pchar):
    Buff(pchar, "Adrenaline Rush", "Assets/spell/Spell_shadow_shadowworddominate.png", 15, 0),
    rogue(dynamic_cast<Rogue*>(pchar))
{}

AdrenalineRushBuff::~AdrenalineRushBuff() {
    if (is_enabled())
        disable_buff();
}

void AdrenalineRushBuff::buff_effect_when_applied() {
    rogue->get_energy()->increase_energy_per_tick();
}

void AdrenalineRushBuff::buff_effect_when_removed() {
    rogue->get_energy()->decrease_energy_per_tick();
}
