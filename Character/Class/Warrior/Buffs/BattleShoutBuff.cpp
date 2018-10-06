
#include "BattleShoutBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"

void BattleShoutBuff::buff_effect_when_applied() {
    auto change = static_cast<int>(round(base_ap * ranks_imp_shout[rank_imp_shout]));
    pchar->get_stats()->increase_melee_ap(change);
}

void BattleShoutBuff::buff_effect_when_removed() {
    auto change = static_cast<int>(round(base_ap * ranks_imp_shout[rank_imp_shout]));
    pchar->get_stats()->decrease_melee_ap(change);
}

void BattleShoutBuff::increase_effect_via_booming_voice() {
    ++rank_booming_voice;
    duration = static_cast<int>(round(base_duration * ranks_booming_voice[rank_booming_voice]));
}

void BattleShoutBuff::decrease_effect_via_booming_voice() {
    --rank_booming_voice;
    assert(rank_booming_voice >= 0);
    duration = static_cast<int>(round(base_duration * ranks_booming_voice[rank_booming_voice]));
}

void BattleShoutBuff::increase_effect_via_imp_shout() {
    ++rank_imp_shout;
}

void BattleShoutBuff::decrease_effect_via_imp_shout() {
    --rank_imp_shout;
    assert(rank_imp_shout >= 0);
}
