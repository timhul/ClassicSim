#include "BattleShoutBuff.h"

#include <cmath>

#include "CharacterStats.h"
#include "Warrior.h"

BattleShoutBuff::BattleShoutBuff(Character* pchar):
    Buff(pchar, "Battle Shout", "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png",  120, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Battle Shout", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Booming Voice", 5, DisabledAtZero::No)
                   })
{
    spell_ranks = {15, 35, 55, 85, 130, 185, 232};
    rank_spell = 6;
    base_attack_power = spell_ranks[rank_spell];
    modified_by_talents_attack_power = base_attack_power;

    base_duration = duration;

    ranks_booming_voice = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    ranks_imp_shout = {1.0, 1.05, 1.10, 1.15, 1.20, 1.25};
}

void BattleShoutBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_ap(modified_by_talents_attack_power);
}

void BattleShoutBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_ap(modified_by_talents_attack_power);
}

void BattleShoutBuff::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Battle Shout") {
        modified_by_talents_attack_power = static_cast<int>(round(base_attack_power * ranks_imp_shout[curr]));
    }
    else if (talent_name == "Booming Voice") {
        duration = static_cast<int>(round(base_duration * ranks_booming_voice[curr]));
    }
}

void BattleShoutBuff::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Battle Shout") {
        modified_by_talents_attack_power = static_cast<int>(round(base_attack_power * ranks_imp_shout[curr]));
    }
    else if (talent_name == "Booming Voice") {
        duration = static_cast<int>(round(base_duration * ranks_booming_voice[curr]));
    }
}
