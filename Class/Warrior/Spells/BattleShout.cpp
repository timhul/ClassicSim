#include "BattleShout.h"

#include "BattleShoutBuff.h"
#include "CooldownControl.h"
#include "EnabledBuffs.h"
#include "Warrior.h"

BattleShout::BattleShout(Warrior* pchar, BattleShoutBuff* buff) :
    Spell("Battle Shout", "Assets/ability/Ability_warrior_battleshout.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 10),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Battle Shout", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Booming Voice", 5, DisabledAtZero::No)
                   }),
    buff(buff),
    spell_ranks({15, 35, 55, 85, 130, 185, 232}),
    ranks_booming_voice({1.0, 1.1, 1.2, 1.3, 1.4, 1.5}),
    ranks_imp_shout({1.0, 1.05, 1.10, 1.15, 1.20, 1.25})
{
    rank_spell = 6;
    base_attack_power = spell_ranks[rank_spell];
    modified_by_talents_attack_power = base_attack_power;

    base_duration = buff->duration;
    next_duration = buff->duration;
}

BattleShout::~BattleShout() {
    delete cooldown;
}

Buff* BattleShout::get_buff() const {
    return this->buff;
}

void BattleShout::spell_effect() {
    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();

    if (buff->is_active())
        buff->cancel_buff();

    buff->duration = next_duration;
    buff->attack_power = modified_by_talents_attack_power;
    buff->apply_buff();

    pchar->lose_rage(resource_cost);
}

void BattleShout::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Battle Shout") {
        modified_by_talents_attack_power = static_cast<unsigned>(round(base_attack_power * ranks_imp_shout[curr]));
    }
    else if (talent_name == "Booming Voice") {
        next_duration = static_cast<int>(round(base_duration * ranks_booming_voice[curr]));
    }
}

void BattleShout::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Battle Shout") {
        modified_by_talents_attack_power = static_cast<unsigned>(round(base_attack_power * ranks_imp_shout[curr]));
    }
    else if (talent_name == "Booming Voice") {
        next_duration = static_cast<int>(round(base_duration * ranks_booming_voice[curr]));
    }
}
