#include <QDebug>
#include <cmath>

#include "BattleShoutBuff.h"
#include "CharacterStats.h"
#include "Warrior.h"

BattleShoutBuff::BattleShoutBuff(Character* pchar):
    Buff(pchar, "Battle Shout", "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png",  120, 0),
    TalentRequirer(10, DisabledAtZero::No)
{
    spell_ranks = {15, 35, 55, 85, 130, 185, 232};
    rank_spell = 6;
    base_attack_power = spell_ranks[rank_spell];
    modified_by_talents_attack_power = base_attack_power;

    rank_booming_voice = 0;
    rank_imp_shout = 0;

    base_duration = duration;

    ranks_booming_voice = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    ranks_imp_shout = {1.0, 1.05, 1.10, 1.15, 1.20, 1.25};
}

void BattleShoutBuff::buff_effect_when_applied() {
    auto change = static_cast<int>(round(modified_by_talents_attack_power * ranks_imp_shout[rank_imp_shout]));
    pchar->get_stats()->increase_melee_ap(change);
}

void BattleShoutBuff::buff_effect_when_removed() {
    auto change = static_cast<int>(round(modified_by_talents_attack_power * ranks_imp_shout[rank_imp_shout]));
    pchar->get_stats()->decrease_melee_ap(change);
}

void BattleShoutBuff::increase_talent_rank_effect(const QString& talent_name) {
    if (talent_name == "Improved Battle Shout") {
        ++rank_imp_shout;
        modified_by_talents_attack_power = static_cast<int>(round(base_attack_power * ranks_imp_shout[rank_imp_shout]));
    }
    else if (talent_name == "Booming Voice") {
        ++rank_booming_voice;
        duration = static_cast<int>(round(base_duration * ranks_booming_voice[rank_booming_voice]));
    }
    else {
        qDebug() << name << "- Unknown talent" << talent_name;
        assert(false);
    }
}

void BattleShoutBuff::decrease_talent_rank_effect(const QString& talent_name) {
    if (talent_name == "Improved Battle Shout") {
        --rank_imp_shout;
        modified_by_talents_attack_power = static_cast<int>(round(base_attack_power * ranks_imp_shout[rank_imp_shout]));
    }
    else if (talent_name == "Booming Voice") {
        --rank_booming_voice;
        duration = static_cast<int>(round(base_duration * ranks_booming_voice[rank_booming_voice]));
    }
    else {
        qDebug() << name << "- Unknown talent" << talent_name;
        assert(false);
    }
}
